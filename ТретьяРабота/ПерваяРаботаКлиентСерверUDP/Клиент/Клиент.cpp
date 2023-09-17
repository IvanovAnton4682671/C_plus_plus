//client
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// подавление предупреждений библиотеки winsock2
#include <winsock2.h>
#include <string>
#include <windows.h>
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable: 4996) // подавление предупреждения 4996
using namespace std;
#define PORT 999
#define SERVERADDR "127.0.0.1"//порт сервера

struct Person {
	int height;//рост
	int weight;//вес
}A;

bool findSymbol(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z') {
			return true;
		}
	}
	return false;
}

int main() {
	char buff[10 * 1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff)) {
		cout << "Error WSAStartup \n" << WSAGetLastError(); // Ошибка!
		return -1;
	}
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SOCKET ms = socket(AF_INET, SOCK_DGRAM, 0);//сокет клиента
	if (ms == INVALID_SOCKET) {
		cout << "SOCKET() ERROR: " << WSAGetLastError() << "\n";
		WSACleanup();
		return -1;
	}
	hostent* hst;
	sockaddr_in Daddr;
	Daddr.sin_family = AF_INET;
	Daddr.sin_port = htons(PORT);
	if (inet_addr(SERVERADDR))
		Daddr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else if (hst = gethostbyname(SERVERADDR))
		Daddr.sin_addr.s_addr = ((unsigned long**)hst->h_addr_list)[0][0];
	else {
		cout << "Unknown Host: " << WSAGetLastError() << "\n";
		closesocket(ms);
		WSACleanup();
		return -1;
	}

	while (1) {
		string s;
		cout << "Введите любой текст чтобы начать или bye чтобы выйти" << endl;
		cin >> s;
		if (s == "bye")
			break;
		sendto(ms, (char*)&s[0], s.size(), 0, (sockaddr*)&Daddr, sizeof(Daddr));

		sockaddr_in SRaddr;
		int SRaddr_size = sizeof(SRaddr);
		cout << "Введите рост: ";
		cin >> s;
		if (findSymbol(s)) {
			cout << "ошибка ввода.\nВводить нужно только числа!" << endl;
			continue;
		}
		A.height = stoi(s);
		cout << "Введите вес: ";
		cin >> s;
		if (findSymbol(s)) {
			cout << "ошибка ввода.\nВводить нужно только числа!" << endl;
			continue;
		}
		A.weight = stoi(s);

		sendto(ms, (char*)&A, sizeof(A), 0, (sockaddr*)&Daddr, sizeof(Daddr));//отправил
		int n = recvfrom(ms, buff, sizeof(buff), 0, (sockaddr*)&SRaddr, &SRaddr_size);//прочитал
		if (n == SOCKET_ERROR) {
			cout << "recform error: " << WSAGetLastError() << "\n";
			closesocket(ms);
			WSACleanup();
			return -1;
		}
		//cout << A.imt << endl;
		buff[n] = '\0';
		cout << buff << endl;
	}
	closesocket(ms);
	WSACleanup();
	system("pause");
	return 0;
}