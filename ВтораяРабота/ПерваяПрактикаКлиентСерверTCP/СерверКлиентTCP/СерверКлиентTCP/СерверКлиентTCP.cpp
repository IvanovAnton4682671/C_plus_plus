//serv

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib")
using namespace std;

struct Person
{
	int height, weight;//рост, вес
	string IMT;
	//string text;
}B;

#define SRV_PORT 1234
#define BUF_SIZE 128
const string QUEST = "Who are you?\n";

double IMG(double h, double w) {
	return (w / ((h / 100) * (h / 100)));
}

string F(double img) {
	string s;
	if (img < 16) {
		s = "Выраженный дефицит массы тела";
		return s;
	}
	else {
		return "xp";
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
	{
		cout << "Error WSAStartup \n" << WSAGetLastError(); // Ошибка!
		return -1;
	}
	SOCKET s, s_new;
	int from_len;
	char buf[BUF_SIZE] = { 0 };
	sockaddr_in sin, from_sin;
	s = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SRV_PORT);
	bind(s, (sockaddr*)&sin, sizeof(sin));
	string msg, msg1;
	double imt;
	listen(s, 3);
	while (1) {
		from_len = sizeof(from_sin);
		s_new = accept(s, (sockaddr*)&from_sin, &from_len);
		cout << "new connected client! " << endl;
		while (1) {
			from_len = recv(s_new, (char*)&B, sizeof(B), 0);//читаем
			buf[from_len] = 0;
			if (B.height == -1) {
				break;
			}
			imt = IMG(B.height, B.weight);
			msg = to_string(imt);
			B.IMT = msg;
			//B.text = F(imt);
			send(s_new, (char*)&B, sizeof(B), 0); // отправил
		}
		cout << "client is lost";
		//closesocket(s_new);
	}
	return 0;
}