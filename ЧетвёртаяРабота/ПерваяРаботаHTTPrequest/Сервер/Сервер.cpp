#include <iostream>
#include <sstream>
#include <string>
// Для корректной работы freeaddrinfo в MinGW
#define _WIN32_WINNT 0x501
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define BUF_SIZE 1024

using std::cerr;

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	// Оформление окна
	cout << "\t НТТР-сервер\n";
	for (int i = 0; i < 30; i++)
		cout << "-";

	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws))
	{
		cerr << "Ошибка WSAStartup! \n" << WSAGetLastError();
		return -1;
	}

	// IP-адрес слушающего сокета сервера
	addrinfo* addr = NULL;
	// Шаблон для инициализации структуры адреса
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Инициализируем структуру, хранящую адрес сокета
	// Наш HTTP-сервер будет висеть на 8000-м порту localhost
	if (getaddrinfo("127.0.0.1", "8000", &hints, &addr))
	{
		cerr << "Ошибка getaddrinfo! \n" << WSAGetLastError();
		WSACleanup();
		return -1;
	}

	// Создаем слушающий сокет
	SOCKET listener = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (listener == INVALID_SOCKET)
	{
		cerr << "Ошибка socket! \n" << WSAGetLastError();
		WSACleanup();
		return -1;
	}

	// Привязываем слушающий сокет к IP-адресу сервера
	if (bind(listener, addr->ai_addr, addr->ai_addrlen) == SOCKET_ERROR)
	{
		cerr << "Ошибка bind! \n" << WSAGetLastError();
		closesocket(listener);
		freeaddrinfo(addr);
		WSACleanup();
		return -1;
	}

	// Инициализируем слушающий сокет
	if (listen(listener, SOMAXCONN) == SOCKET_ERROR)
	{
		cerr << "Ошибка bind! \n" << WSAGetLastError();
		closesocket(listener);
		freeaddrinfo(addr);
		WSACleanup();
		return -1;
	}

	char buf[BUF_SIZE] = {};
	SOCKET sClient;
	// Цикл приема сообщений
	while (true)
	{
		// Принимаем входящее соединение
		if ((sClient = accept(listener, NULL, NULL)) == INVALID_SOCKET)
		{
			cerr << "Ошибка accept! \n" << WSAGetLastError();
			closesocket(listener);
			freeaddrinfo(addr);
			WSACleanup();
			return -1;
		}
		int len = recv(sClient, (char*)buf, BUF_SIZE, 0);
		if (len == SOCKET_ERROR)
		{
			cerr << "Ошибка recv! \n" << WSAGetLastError();
			closesocket(sClient);
		}
		if (len == 0)
		{
			cout << "Соединение закрыто клиентом" << endl;
		}
		else
		{
			cout << "Присоединился новый клиент!\n";
			// Ставим метку конца строки в буфере запроса
			buf[len] = '\0';
			// Формируем ответ в формате HTML
			std::stringstream responseBody, response;
			// Тело ответа
			responseBody << "<title>Test C++ HTTP Server</title>\n"
						 << "<h1>Test page</h1>\n"
					     << "<p>This is body of the test page...</p>\n"
				         << "<h2>Request headers</h2>\n"
				         << "<pre>" << buf << "</pre>\n"
				         << "<em><small>Test C++ Http Server</small></em>\n";
			// Весь ответ
			response << "HTTP/1.1 200 OK\r\n"
				     << "Version: HTTP/1.1\r\n"
				     << "Content-Type: text/html; charset=utf-8\r\n"
				     << "Content-Length: " << responseBody.str().length()
				     << "\r\n\r\n" << responseBody.str();
			// Отправляем ответ клиенту
			if (send(sClient, response.str().c_str(),
				response.str().length(), 0) == SOCKET_ERROR)
			{
				cerr << "Ошибка send! \n" << WSAGetLastError();
			}
			// Закрываем соединение
			closesocket(sClient);
		}
	}
	closesocket(listener);
	freeaddrinfo(addr);
	WSACleanup();
	return 0;
}