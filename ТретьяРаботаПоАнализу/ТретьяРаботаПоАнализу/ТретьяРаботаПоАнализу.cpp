//3-е практическое задание (в log основание 2)

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

int kolop = 0;

void HoarFastSort(int* arr, int first, int last)
{
	int i = first;
	int j = last;
	double tmp, x = arr[(first + last) / 2];
	kolop += 3;
	do
	{
		while (arr[i] < x)
		{
			i++;
			kolop++;
		}
		while (arr[j] > x)
		{
			j--;
			kolop++;
		}
		if (i <= j)
		{
			if (i < j)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				kolop += 3;
			}
			i++;
			j--;
			kolop += 2;
		}
		kolop++;
	} while (i <= j);
	if (i < last)
		HoarFastSort(arr, i, last);
	if (first < j)
		HoarFastSort(arr, first, j);
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	for (int n = 100; n < 1001; n += 100)
	{
		for (int n1 = 0; n1 < 1000; n1++)
		{
			int* arr = new int[n];
			for (int i = 0; i < n; i++)
				arr[i] = rand() % 101;
			//cout << "Ваш массив:" << endl;
			//cout << endl;
			//for (int i = 0; i < n; i++)
			//	cout << arr[i] << " ";
			HoarFastSort(arr, 0, n - 1);
			//cout << endl << endl;
			//cout << "Ваш отсортированный массив:" << endl << endl;
			//for (int i = 0; i < n; i++)
			//	cout << arr[i] << " ";
			//cout << endl << endl;
			//cout << "Колличество операций при сортировке: " << kolop << "." << endl;
			//cout << endl;
		}
		cout << "Среднее колличество операций после 1000 запусков (" << n << "): " << kolop / 1000 << "." << endl;
		kolop = 0;
	}

	return 0;
}