//server
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define PORT 999

struct Person {
	int height;//рост
	int weight;//вес
}B;

double IMT(double h, double w) {
	return (w / ((h / 100) * (h / 100)));
}

string F(double imt) {
	string s;
	if (imt < 16) {
		s = "Выраженный дефицит массы тела";
		return s;
	}
	else if (imt < 18.5) {
		s = "Недостаточная (дефицит) масса тела";
		return s;
	}
	else if (imt < 25) {
		s = "Норма";
		return s;
	}
	else if (imt < 30) {
		s = "Избыточная масса тела (предожирение)";
		return s;
	}
	else if (imt < 35) {
		s = "Ожирение первой степени";
		return s;
	}
	else if (imt < 40) {
		s = "Ожирение второй степени";
		return s;
	}
	else if (imt > 40) {
		s = "Ожирение третьей степени (морбидное)";
		return s;
	}
	else {
		return "xp";
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0])) //инициализация в библиотеке.1)версия в библиотеке 2)структура для записи
	{
		cout << "Error WSAStartup \n" << WSAGetLastError(); // Ошибка!
		return -1;
	}
	SOCKET Lsock = socket(AF_INET, SOCK_DGRAM, 0);
	if (Lsock == INVALID_SOCKET)
	{
		cout << "SOCKET() ERROR: " << WSAGetLastError() << "\n";
		WSACleanup();
		return -1;
	}
	sockaddr_in Laddr; //структуры
	Lsock = socket(AF_INET, SOCK_DGRAM, 0);//создание слушащего сокета сервера.1)Домен 2)Потоковый режим 3)TCP
	Laddr.sin_family = AF_INET;
	Laddr.sin_addr.s_addr = INADDR_ANY;
	Laddr.sin_port = htons(PORT);
	if (bind(Lsock, (sockaddr*)&Laddr, sizeof(Laddr)))
	{
		cout << "BIND ERROR: " << WSAGetLastError();
		closesocket(Lsock);
		WSACleanup();
		return -1;
	}
	while (1) {

		sockaddr_in Caddr;
		int Caddr_size = sizeof(Caddr);
		int bsize = recvfrom(Lsock, &buff[0], sizeof(buff) - 1, 0, (sockaddr*)&Caddr, &Caddr_size);//получил
		if (bsize == SOCKET_ERROR)  cout << "recform error: " << WSAGetLastError();
		hostent* hst;
		hst = gethostbyaddr((char*)&Caddr.sin_addr, 4, AF_INET);
		cout << "NEW DATAGRAM!\n" << ((hst) ? hst->h_name : "Unkown host") << "\n" << inet_ntoa(Caddr.sin_addr) << "\n" << ntohs(Caddr.sin_port) << '\n';
		int bsize2 = recvfrom(Lsock, (char*)&B, sizeof(buff) - 1, 0, (sockaddr*)&Caddr, &Caddr_size);
		if (bsize2 == SOCKET_ERROR)  cout << "recform2 error: " << WSAGetLastError();
		string s;
		double imt1 = IMT(B.height, B.weight);
		s = to_string(imt1);
		//sendto(Lsock, (char*)&B, sizeof(B), 0, (sockaddr*)&Caddr, sizeof(Caddr));
		s += "\n";
		s += F(imt1);
		sendto(Lsock, &s[0], s.size(), 0, (sockaddr*)&Caddr, sizeof(Caddr));
	}
	system("pause");
	return 0;
}