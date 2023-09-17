//Дан файл целых чисел. Найти количество квадратов чётных чисел среди компонент файла.
#include <iostream>
#include <fstream>
using namespace std;
int main ()
{
	setlocale (LC_ALL, "rus");
	int col = 0;
	ifstream f;
	f.open("D:/Проекты VS/f1.txt");
	if (f.is_open())
	{
		while (!f.eof())
		{
			int x;
			f >> x;
			if (x == sqrt(x)*sqrt(x) && x % 2 == 0)
				col++;
		}
		cout << "Количество квадратов чётных чисел - " << col << endl;
	}
	else
		cout << "ОШИБКА: файл f1 не открылся." << endl;
	f.close();
	system("pause");
}