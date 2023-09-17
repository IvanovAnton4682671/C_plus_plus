#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib")
using namespace std;
#define SRV_PORT 1234
#define BUF_SIZE 64

int IMG2(double h, double w)
{
	if (18.5 <= (w / ((h / 100) * (h / 100))) && (w / ((h / 100) * (h / 100))) < 25)
		return 0;
	if ((w / ((h / 100) * (h / 100))) < 18.5)
		return 1;
	if ((w / ((h / 100) * (h / 100))) > 25)
		return 2;
}

int main()
{
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
	string msg, msg1, msg2;
	double height, weight;//рост, вес
	double img;
	int k = 0;
	listen(s, 3);
	while (1)
	{
		from_len = sizeof(from_sin);
		s_new = accept(s, (sockaddr*)&from_sin, &from_len);
		cout << "Подключился новый пациент." << endl;
		while (1)
		{
			if (k == 0)
			{
				msg = "Введите свой рост:";
			}
			else if (k == 1)
			{
				msg = "Введите свой вес:";
			}
			else
			{
				k = 0;
				img = IMG2(height, weight);
				if (img == 0)
					msg = "У вас норма веса.";
				if (img == 1)
					msg = "У вас недостаток веса.";
				if (img == 2)
					msg == "У вас избыток веса.";
			}
			send(s_new, (char*)&msg[0], msg.size(), 0);
			from_len = recv(s_new, (char*)buf, BUF_SIZE, 0);
			buf[from_len] = 0;
			msg1 = (string)buf;
			if (k == 0)
			{
				k++;
				height = stoi(msg1);
			}
			else if (k == 1)
			{
				k++;
				weight = stoi(msg1);
			}
			if (msg1 == "Пока.") break;
		}
		cout << "Пациент отключился.";
		closesocket(s_new);
	}
	return 0;
}