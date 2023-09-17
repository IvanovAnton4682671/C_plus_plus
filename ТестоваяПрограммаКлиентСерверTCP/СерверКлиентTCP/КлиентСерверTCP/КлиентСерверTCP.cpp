//Клиент TCP

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <string>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma warning (disable: 4996)

using namespace std;

#define SERVER_HOST "localhost"
#define SERVER_PORT 1111
#define CLIENT_PORT 1112
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
	hostent* hp;

	SOCKADDR_IN client, server;
	int sizeofaddr = sizeof(client);
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = 0;
	client.sin_port = htons(CLIENT_PORT);

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);
	bind(Connection, (SOCKADDR*)&client, sizeof(client));
	hp = gethostbyname(SERVER_HOST);
	server.sin_port = htons(SERVER_PORT);
	server.sin_family = AF_INET;
	((unsigned long*)&server.sin_addr)[0] = ((unsigned long**)hp->h_addr_list)[0][0];
	connect(Connection, (SOCKADDR*)&server, sizeof(server));

	string msg;

	do
	{
		sizeofaddr = recv(Connection, (char*)&buffer2, BUFFER_SIZE, 0);
		buffer2[sizeofaddr] = 0;
		cout << buffer2 << endl;
		getline(cin, msg);
		int msg_size = msg.size();
		send(Connection, (char*)&msg[0], msg_size, 0);
	}
	while (msg != "Bye.");

	cout << "Вы отключились от сервера." << endl;
	cin.get();
	closesocket(Connection);

	return 0;
}