#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Person
{
	char name[25];
	int math;
	int diskretka;
	int algebra;
	int proga;
	int dolg;
	char faculty[25];
}B;

int answer;
long size_pred;
int main() {
	ifstream fR;
	ofstream fA;
	setlocale(LC_ALL, "Rus");
	string nameR = "Request.bin";
	cout << "Сервер начал свою работу. Можете начинать работу." << endl;

	fR.open(nameR, ios::binary);
	//открытие файла REQUEST
	fR.seekg(0, ios::end);
	size_pred = fR.tellg();
	//стартовая позиция сервера в файле REQUEST
	fR.close();

	// начальные установки
	fR.open(nameR, ios::binary);
	//открытие файла REQUEST
	fR.seekg(0, ios::end);
	size_pred = fR.tellg();
	//стартовая позиция сервера в файле REQUEST
	fR.close();

	// начало работы сервера
	while (true)
	{

		fR.open(nameR, ios::binary);
		//открытие файла REQUEST
		fR.seekg(0, ios::end);
		//переход в конец файла REQUEST
		// есть новые запросы от клиентов? 
		while (size_pred >= fR.tellg())
		{
			Sleep(100); fR.seekg(0, ios::end);

		}
		cout << "На сервер поступил новый запрос." << endl;
		// получен новый запрос 
		fR.seekg(size_pred, ios::beg);
		//переход к началу полученного запроса
		fR.read((char*)&B, sizeof(B));
		//считывание данных клиента
		size_pred = fR.tellg();
		// на конец обработанных данных
		fR.close();




		if (B.math == 2 || B.diskretka == 2 || B.algebra == 2 || B.proga == 2) {
			answer = 0;
			if (B.math == 2)
				answer--;
			if (B.diskretka == 2)
				answer--;
			if (B.algebra == 2)
				answer--;
			if (B.proga == 2)
				answer--;
		}
		else {
			if (B.math == 3 || B.diskretka == 3 || B.algebra == 3 || B.proga == 3)
				answer = 2;
			else if (B.math == 5 && B.diskretka == 5 && B.algebra == 5 && B.proga == 5)
				answer = 4;
			else
				answer = 3;
		}

		// передача ответа клиенту
		string nameA = B.faculty;
		fA.open(nameA + ".bin", ios::binary | ios::app);
		//открытие файла ANSWER
		fA.write((char*)&answer, sizeof(answer));
		//запись ответа клиенту
		fA.close();
	}
}