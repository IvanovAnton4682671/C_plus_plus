//Программа-клиент

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
} A;

void main()
{
	setlocale(LC_ALL, "rus");
	const char* nameR = "REQUEST.bin";
	const char* nameA = "ANSWER.bin";
	ofstream f_REQ;
	ifstream f_ANS;
	long pred_size;
	int answer;
	cout << "Клиент работает нормально." << endl;
	while (true)
	{
		int kol2 = 0;
		cout << "Введите данные: фамилия студента и оценки по 4-ём экзаменам (матанализ, дискретка, основы программирования, алгебра):" << endl;
		cin >> A.name;
		cin >> A.mat;
		if (A.mat == 2) kol2++;
		cin >> A.discret;
		if (A.discret == 2) kol2++;
		cin >> A.op;
		if (A.op == 2) kol2++;
		cin >> A.alg;
		if (A.alg == 2) kol2++;
		f_REQ.open(nameR, ios::app | ios::binary);
		f_REQ.write((char*)&A, sizeof(A));
		f_REQ.close();
		f_ANS.open(nameA, ios::binary);
		f_ANS.seekg(0, ios::end);
		pred_size = f_ANS.tellg();
		while (pred_size >= f_ANS.tellg())
		{
			Sleep(100);
			f_ANS.seekg(0, ios::end);
		}
		f_ANS.seekg(pred_size, ios::beg);
		f_ANS.read((char*)&answer, sizeof(answer));
		f_ANS.close();
		switch (answer)
		{
		case 0: {cout << "У вас есть долги. Их: " << kol2 << endl; break; }
		case 1: {cout << "К сожалению, вы без стипендии (0р)." << endl; break; }
		case 2: {cout << "У вас стипендия обычная (5000р)." << endl; break; }
		case 3: {cout << "У вас стипендия повышенная (10000р)." << endl; break; }
		}
	}
}