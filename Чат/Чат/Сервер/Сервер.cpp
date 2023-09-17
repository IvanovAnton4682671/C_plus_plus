#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;

SOCKET clients[10]; //массив сокетов клиентов
char* username;

vector<char*> usernames(10); //имена всех пользователей

int clientsCounter = 0; //количество клиентов
enum Packet { Pack, Test }; //допустимые типы пакетов


int findIndexByUsername(char* username1)
{
    string str1, str2;
    str1 = username1;
    for (int i = 0; i < 10; i++)
    {
        if (usernames[i] != NULL)
        {
            str2 = usernames[i];
            if (str2 == str1)
                return i;
        }
    }
    return -1;
}



DWORD WINAPI ServerThread(LPVOID number)
{ //обработка потока клиента
    Packet packet;
    bool isPrivate = false;
    char* friendUsername = NULL;

    int index = ((int*)number)[0]; //индекс обрабатываемого сокета
    cout << "Номер сокета пользователя: " << index << endl;
    cout << "\n";

    SOCKET client = clients[index];

    //общение с клиентом
    while (true)
    {
        recv(client, (char*)&packet, sizeof(Packet), NULL); //получение информации от клиента

        //определение типа полученного пакета
        if (packet == Pack)
        {
            int messageSize;
            recv(client, (char*)&messageSize, sizeof(int), NULL); //определение размера пакета

            char* message = new char[messageSize + 1 + sizeof(username)]; //резервируем буффер нужного размера
            message[messageSize] = 0;
            recv(client, message, messageSize, NULL);  //получение пакета

            string responseMessage = message;



            if (responseMessage == "/exit")
            {
                cout << "Пользователь " << usernames[index] << " отключился.\n";
                break;
            }

            if (responseMessage == "/private")
            {
                friendUsername = new char[1024];
                recv(client, friendUsername, 1024, NULL);
                cout << "Никнейм друга: " << friendUsername << "\n";

                isPrivate = true;
            }

            if (responseMessage == "/private-off")
            {
                isPrivate = false;
            }

            if (responseMessage == "" || responseMessage.empty())
                continue;



            string response = usernames[index];
            response += ": ";
            response += message;
            cout << response << "\n";

            messageSize = response.size();

            //передаем сообщение другим участникам чата
            if (!isPrivate)
            { //если не приватный чат, то передаем всем участникам
                for (int i = 0; i < 10; i++)
                {
                    if (i == index || clients[i] == NULL)
                        continue;

                    Packet messageType = Pack;
                    send(clients[i], (char*)&messageType, sizeof(Packet), NULL); //передача типа
                    send(clients[i], (char*)&messageSize, sizeof(int), NULL); //передача размера
                    send(clients[i], (char*)&response[0], messageSize, NULL); //передача самого сообщения
                }
                delete[] message;
            }
            else
            { //если приватный, то находим индекс клиента по имени и передаем только ему
                Packet messageType = Pack;
                int i = findIndexByUsername(friendUsername);
                cout << "Номер друга: " << i << "\n";
                send(clients[i], (char*)&messageType, sizeof(Packet), NULL); //передача типа
                send(clients[i], (char*)&messageSize, sizeof(int), NULL); //передача размера
                send(clients[i], (char*)&response[0], messageSize, NULL); //передача самого сообщения 
            }
        }
        else //получен неопознанный пакет
        {
            cout << "Unrecognized packet: " << packet << endl; break;
        }
    }
    closesocket(client);
    usernames[index] = NULL; //клиент ушел, имя освобождено
    clientsCounter--;
    cout << "Количество пользователей: " << clientsCounter << "\n";
    return 0;
}

bool checkUsername(char* username, int index)
{ //проверка: занято ли имя
    string str1, str2;
    str1 = username;
    for (char* name : usernames)
    {
        if (name != NULL)
        {
            str2 = name;
            if (str1 == str2)
                return false;
        }
    }
    usernames[index] = username;
    return true;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    WSAData wsaData; //инициализация Winsock
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0)
    {
        cout << "Error" << endl; exit(1);
    }

    //сохраняем в слушающем сокете информацию о сервере
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(666);
    addr.sin_family = AF_INET;


    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, NULL);

    bind(listenSocket, (SOCKADDR*)&addr, sizeof(addr));
    listen(listenSocket, 10); //прослушивание и организация очереди из 10 клиентов

    SOCKET newConnection;

    for (int i = 0; i < 10; i++)
    {
        newConnection = accept(listenSocket, (SOCKADDR*)&addr, &sizeofaddr); //извлекаем запрос из очереди
        if (newConnection == 0)
        {
            cout << "Error #2\n";
        }
        else
        {
            cout << "\nПодключился новый пользователь.\n";
            string message;
            int messageSize;
            username = new char[1024];

            //получение имени и обработка
            while (true)
            {
                recv(newConnection, username, 1024, NULL);
                cout << "Никнейм: " << username << "\n";

                if (!checkUsername(username, i))
                {
                    message = "Этот никнейм занят, попробуйте другой.";
                    messageSize = message.size();
                    send(newConnection, (char*)&message[0], 1024, NULL);
                }
                else
                {
                    message = "OK";
                    messageSize = message.size();
                    send(newConnection, (char*)&message[0], 1024, NULL);

                    Sleep(1000);
                    break;
                }
            }
            Packet messageType = Pack;
            send(newConnection, (char*)&messageType, sizeof(Packet), NULL); //передаем тип
            send(newConnection, (char*)&messageSize, sizeof(int), NULL); //размер сообщения
            send(newConnection, (char*)&message[0], messageSize, NULL); //само сообщение

            clients[i] = newConnection; //сохраняем принятого клиента в массив участников чата
            clientsCounter++;
            cout << "Номер пользователя: " << clientsCounter << endl;

            CreateThread(NULL, NULL, ServerThread, &i, NULL, NULL); //создаем новый поток для обслуживания клиента
            Sleep(1000);


            Packet testpacket = Test; //передача клиенту сигнального сообщения
            cout << "Это тестовое сообщение.\n";
            send(newConnection, (char*)&testpacket, sizeof(Packet), NULL);

        }
    }
    return 0;
}