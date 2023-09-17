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
} B;

int answer;
long size_pred;

int main()
{
	string fackult;
	int kol2 = 0;
	ifstream fR;
	ofstream fFACKULT;
	setlocale(LC_ALL, "rus");
	const char* nameR = "REQUEST.bin";
	string nameA = fackult + ".bin";
	cout << "Сервер работает. Можете работать с клиентом." << endl;
	fR.open(nameR, ios::binary);
	fR.seekg(0, ios::end);
	size_pred = fR.tellg();
	fR.close();
	while (true)
	{
		fR.open(nameR, ios::binary);
		fR.seekg(0, ios::end);
		while (size_pred >= fR.tellg())
		{
			Sleep(100);
			fR.seekg(0, ios::end);
		}
		cout << "На сервер поступил новый запрос" << endl;
		fR.seekg(size_pred, ios::beg);
		fR.read((char*)&B, sizeof(B));
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
		fFACKULT.open(nameA, ios::binary | ios::app);
		fFACKULT.write((char*)&answer, sizeof(answer));
		fFACKULT.close();
	}
}