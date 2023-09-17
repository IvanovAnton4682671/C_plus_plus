//client

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// подавление предупреждений библиотеки winsock2
#include <winsock2.h>
#include <string>
#include <windows.h>

#include <string>
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996) // подавление предупреждения 4996
using namespace std;

struct Person
{
	int height, weight;//рост, вес
	string IMT;
	//string text;
}A;

bool findSymbol(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z') {
			return true;
		}
	}
	return false;
}

#define SRV_HOST "localhost"
#define SRV_PORT 1234
#define CLNT_PORT 1235
#define BUF_SIZE 128
char TXT_ANSW[] = "I am your student\n";
int main() {
	setlocale(LC_ALL, "rus");
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
		cout << "Error WSAStartup \n" << WSAGetLastError(); // Ошибка!
		return -1;
	}
	SOCKET s;
	int from_len; char buf[BUF_SIZE] = { 0 }; hostent* hp;
	sockaddr_in clnt_sin, srv_sin;
	s = socket(AF_INET, SOCK_STREAM, 0);
	clnt_sin.sin_family = AF_INET;
	clnt_sin.sin_addr.s_addr = 0;
	clnt_sin.sin_port = htons(CLNT_PORT);
	bind(s, (sockaddr*)&clnt_sin, sizeof(clnt_sin));
	hp = gethostbyname(SRV_HOST);
	srv_sin.sin_port = htons(SRV_PORT);
	srv_sin.sin_family = AF_INET;
	((unsigned long*)&srv_sin.sin_addr)[0] =
		((unsigned long**)hp->h_addr_list)[0][0];
	connect(s, (sockaddr*)&srv_sin, sizeof(srv_sin));
	string mst = "";
	do {
		cout << "Введите рост: ";
		cin >> mst;
		if (findSymbol(mst)) {
			if (mst == "bye") {
				A.height = -1;
				send(s, (char*)&A, sizeof(A), 0);
				break;
			}
			else
				cout << "ошибка ввода.\nВводить нужно только числа" << endl;
			continue;
		}
		else {
			A.height = stoi(mst);
		}
		cout << "Введите вес: ";
		cin >> mst;
		if (findSymbol(mst)) {
			if (mst == "bye")
				break;
			else
				cout << "ошибка ввода.\nВводить нужно только числа" << endl;
			continue;
		}
		else {
			A.weight = stoi(mst);
		}
		A.IMT = "0";
		//A.text = "0";
		send(s, (char*)&A, sizeof(A), 0);//отправил структуру
		from_len = recv(s, (char*)&A, sizeof(A), 0);
		buf[from_len] = 0;

		cout << "Ваш ИМТ = " << A.IMT << endl;
		//cout << A.text << endl;
	} while (mst != "bye");
	cout << "exit to infinity" << endl;
	cin.get(); closesocket(s);
	return 0;
}