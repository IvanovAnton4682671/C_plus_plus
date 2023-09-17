//Сервер TCP

#include <winsock2.h>
#include <iostream>
#include <string>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

#define SERVER_PORT 1111
#define BUFFER_SIZE 64

int main()
{
	setlocale(LC_ALL, "rus");

	char buffer1[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buffer1[0]))
	{
		cout << " !!! ERROR WSAStartup !!! " << WSAGetLastError();
		return -1;
	}

	char buffer2[BUFFER_SIZE] = { 0 };

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = 0;
	addr.sin_port = htons(SERVER_PORT);

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	string msg_out, msg_in;

	SOCKET newConnection;

	while (1)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		cout << "Подключился новый пользователь." << endl;
		msg_out = "Вы подключились к серверу.";

		while (1)
		{
			send(newConnection, (char*)&msg_out[0], msg_out.size(), 0);
			sizeofaddr = recv(newConnection, (char*)&buffer2, BUFFER_SIZE, 0);
			buffer2[sizeofaddr] = 0;
			msg_in = (string)buffer2;
			cout << msg_in << endl;
			if (msg_in == "Bye.")
				break;
			getline(cin, msg_out);
		}

		cout << "Пользователь отключился." << endl;
		closesocket(newConnection);
	}

	return 0;
}