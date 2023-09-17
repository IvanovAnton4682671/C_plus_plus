//Программа-сервер

#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

struct Person
{
	char name[25];
	int height;
	int weight;
}B;

int answer;
long size_pred;

int main ()
{
	setlocale (LC_ALL, "rus");
	ifstream fR;
	ofstream fA;
	const char* nameR = "REQUEST.bin";
	const char* nameA = "ANSWER.bin";
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
		fR.seekg(size_pred, ios::beg);
		fR.read((char*)&B, sizeof(B));
		size_pred = fR.tellg();
		fR.close();
		double IMT = B.weight / (0.01 * B.height) / (0.01 * B.height);
		if (18.5 <= IMT && IMT < 25)
			answer = 0;
		if (18.5 > IMT)
			answer = 1;
		if (IMT >= 25)
			answer = 2;
		fA.open(nameA, ios::binary | ios::app);
		fA.write((char*)&answer, sizeof(answer));
		fA.close();
	}
}