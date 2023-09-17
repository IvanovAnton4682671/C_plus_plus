#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;

SOCKET client;
enum Packet {
    Pack,
    Test
};

DWORD WINAPI ClientThread(LPVOID sock)
{ //функция потока для принятия сообщений
    SOCKET connection = ((SOCKET*)sock)[0];
    Packet packet;

    while (1)
    { //получения пакетов от сервера
        recv(connection, (char*)&packet, sizeof(Packet), NULL);
        Sleep(1000);
        if (packet == Pack)
        {
            int messageSize;
            recv(connection, (char*)&messageSize, sizeof(int), NULL); //размер пакета
            char* message = new char[messageSize + 1]; //резервирование буффера       
            message[messageSize] = '\0';

            recv(connection, message, messageSize, NULL); //прием данных пакета
            cout << message << endl;
            delete[] message;
        }
        else
        {
            if (packet == Test) //прием сигнального пакета от сервера
                cout << "Это тестовое сообщение.\n";
            else
            {
                cout << "Unrecognized packet: " << packet << endl;
                break;
            }
        }
    }
    closesocket(client);
    return 0;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    WSAData wsaData;
    WORD Ver = MAKEWORD(2, 1);
    if (WSAStartup(Ver, &wsaData) != 0)
    {
        cout << "Error" << endl;
        return 1;
    }

    //определение параметров сервера
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(666);
    addr.sin_family = AF_INET;
    client = socket(AF_INET, SOCK_STREAM, NULL);

    if (connect(client, (SOCKADDR*)&addr, sizeof(addr)) != 0) //соединение с сервером
    {
        cout << "Error: failed connect to server.\n";
        return 1;
    }
    cout << "Вы подключились.\n";

    while (true)
    {
        cout << "Никнейм: "; //создание имени
        string username;
        cin >> username;
        send(client, (char*)&username[0], 1024, NULL);

        char* response = new char[1024];
        recv(client, response, 1024, NULL);
        string stringResponse = response;
        if (stringResponse == "OK")
            break;
        else
            cout << response << "\n";
    }

    CreateThread(NULL, NULL, ClientThread, &client, NULL, NULL); //создаем дочерний поток для приема сообщений от сервера

    string message;
    while (true)
    { //отправка данных серверу в основной поток
        getline(cin, message);
        int messageSize = message.size();
        Packet packettype = Pack; //передача информационного пакета
        send(client, (char*)&packettype, sizeof(Packet), NULL);
        send(client, (char*)&messageSize, sizeof(int), NULL);
        send(client, (char*)&message[0], messageSize, NULL);
        if (message == "/exit")
        {
            cout << "До свидания!\n";
            break;
        }
        if (message == "/private")
        {
            cout << "Вы вошли в приватный канал. Введите никнейм друга: (для выхода введите '/private-off') ";
            string friendUsername;
            cin >> friendUsername;
            send(client, (char*)&friendUsername[0], 1024, NULL);
        }
        Sleep(1000);
    }
    closesocket(client);
    return 0;
}