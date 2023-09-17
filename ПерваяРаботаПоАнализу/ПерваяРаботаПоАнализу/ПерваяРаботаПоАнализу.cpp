#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	//int n;
	int kolopobsh = 0;
	int srzn = 0;
	cout << "Введите колличество элементов массива:" << endl;
	//cin >> n;
	//for (int i1 = 0; i1 < 1000; i1++)
	//{
	for (int n = 10; n < 101; n += 10)
	{
		int kolop = 0;
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
		{
			//arr[i] = rand() % 100 + 1;
			//arr[i] = i;
			//arr[i] = n - i;
		}
		cout << "Ваш массив:" << endl;
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n - 1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					int a = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = a;
					kolop += 5;
				}
				kolop += 2;
			}
		}
		cout << endl;
		cout << "Отсортированный массив:" << endl;
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << endl;
		cout << "Колличество операций - " << kolop << endl;
		cout << endl;
		kolopobsh += kolop;
	}
	//}
	srzn = kolopobsh / 1000;
	cout << "Среднее колличество операций для 1000 запусков - " << srzn << endl;
	system("pause");
}