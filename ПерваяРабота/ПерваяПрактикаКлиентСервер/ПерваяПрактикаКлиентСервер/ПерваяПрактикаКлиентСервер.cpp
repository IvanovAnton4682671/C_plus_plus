//Программа-сервер

#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

struct Person
{
	char name[25];
	int mat;
	int discret;
	int op;
	int alg;
}B;

int answer;
long size_pred;

int main()
{
	int kol2 = 0;
	ifstream fR;//создаём переменные для файлов нужных типов
	ofstream fA;
	setlocale(LC_ALL, "rus");
	const char* nameR = "REQUEST.bin";//указываем как они будут называться
	const char* nameA = "ANSWER.bin";
	cout << "Сервер работает. Можете работать с клиентом." << endl;
	fR.open(nameR, ios::binary);//открываем файл для чтения
	fR.seekg(0, ios::end);//ставим указатель на конец файла
	size_pred = fR.tellg();//вводим переменную для последнего значения байтов в этом файле (понадобится позже)
	fR.close();//закрываем файл
	while (true)
	{
		fR.open(nameR, ios::binary);//открываем
		fR.seekg(0, ios::end);//ставим указатель на конец файла
		while (size_pred >= fR.tellg())//сравниваем прошлое значение файла с текущим (так мы определяем появление новых данных - указатель на конец данных в файле сдвигается и становится больше)
		{
			Sleep(100);
			fR.seekg(0, ios::end);//читаем данные
		}
		cout << "На сервер поступил новый запрос" << endl;
		fR.seekg(size_pred, ios::beg);//читаем данные
		fR.read((char*)&B, sizeof(B));//связываем данные из файла со структурой
		size_pred = fR.tellg();
		fR.close();
		if (B.mat == 2 || B.discret == 2 || B.op == 2 || B.alg == 2)
		{
			if (B.mat == 2) kol2++;
			if (B.discret == 2) kol2++;
			if (B.op == 2) kol2++;
			if (B.alg == 2) kol2++;
			answer = 0;
		}
		else
		{
			if (B.mat == 3 || B.discret == 3 || B.op == 3 || B.alg == 3)
				answer = 1;
			else
				if (B.mat == 5 && B.discret == 5 && B.op == 5 && B.alg == 5)
					answer = 3;
				else
					answer = 2;
		}
		fA.open(nameA, ios::binary | ios::app);//открываем файл для ответа
		fA.write((char*)&answer, sizeof(answer));//пишем ответ
		fA.close();
	}
}