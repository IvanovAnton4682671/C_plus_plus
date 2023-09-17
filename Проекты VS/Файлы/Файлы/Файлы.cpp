//ifstream - берём из файла
//ofstream - записываем в файл
#include <iostream>
#include <fstream>
using namespace std;
/*int main ()
{
	setlocale (LC_ALL, "rus");
	ifstream f1;
	f1.open("D:/Проекты VS/f1.txt");
	if (f1.is_open())
	{
		int s = 0;
		while (!f1.eof())
		{
			int x;
			f1 >> x;
			if (x % 10 != 5)
				s += x;
		}
		cout << "Сумма элементов файла, не оканчивающихся на 5 - " << s << endl;
	}
	else
		cout << "ОШИБКА: файл f1 не открыт." << endl;
	f1.close();
	system("pause");
}*/
/*int main ()
{
	setlocale (LC_ALL, "rus");
	ifstream f1;
	ofstream f2;
	f1.open("D:/Проекты VS/f1.txt");
	f2.open("D:/Проекты VS/f2.txt");
	if (f1.is_open())
	{
		if (f2.is_open())
		{
			int x;
			while (!f1.eof())
			{
				f1 >> x;
				if (x % 2 == 0)
					f2 << x << " ";
			}
		}
		else
			cout << "ОШИБКА: файл f2 не открыт." << endl;
	}
	else
		cout << "ОШИБКА: файл f1 не открты." << endl;
	f1.close();
	f2.close();
	system("pause");
}*/