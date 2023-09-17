#include<iostream>
#include<random>
#include<ctime>
#include<cstdlib>

using namespace std;

long kolop = 0;

void add(int* arr3, int n)
{
	int b = 10;
	int d = 0;
	for (int i = 0; i < n; i++)
	{
		arr3[i] += d;
		d = arr3[i] % b;
		arr3[i] /= b;
		kolop += 3;
	}
}

void mult(int* arr1, int* arr2, int* arr3, int n)
{
	int k = n / 2;
	if (n <= 64)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				arr3[i + j] += arr1[i] * arr2[j];
				kolop += 3;
			}
	}
	else
	{
		int* l = new int[k];
		for (int i = 0; i < k; i++)
			l[i] = 0;
		int* r = new int[k];
		for (int i = 0; i < k; i++)
			r[i] = 0;
		int* t = new int[n];
		for (int i = 0; i < n; i++)
			t[i] = 0;
		for (int i = 0; i < k; i++)
		{
			l[i] = arr1[i] + arr1[k + i];
			r[i] = arr2[i] + arr2[k + i];
			kolop += 4;
		}
		mult(l, r, t, k);
		mult(arr1, arr2, arr3, k);
		mult(arr1 + k, arr2 + k, arr3 + n, k);
		int* t1 = t, * t2 = t + k;
		kolop++;
		int* s1 = arr3, * s2 = arr3 + k, * s3 = arr3 + 2 * k, * s4 = arr3 + 3 * k;
		kolop += 5;
		for (int i = 0; i < k; i++)
		{
			int c1 = s2[i] + t1[i] - s1[i] - s3[i];
			int c2 = s3[i] + t2[i] - s2[i] - s4[i];
			arr3[k + i] = c1;
			arr3[n + i] = c2;
			kolop += 12;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	for (int n = 1024; n <= 16384; n += 1024)
	{
		int* chislo1 = new int[n];
		int* chislo2 = new int[n];
		int* arr1 = new int[n];
		int* arr2 = new int[n];
		int* arr3 = new int[n * 2];

		chislo1[0] = rand() % 9 + 1;
		for (int i = 1; i < n; i++)
			chislo1[i] = rand() % 10;
		chislo2[0] = rand() % 9 + 1;
		for (int i = 1; i < n; i++)
			chislo2[i] = rand() % 10;

		/*cout << "Ваши 2 числа размером " << n << " цифр(ы):" << endl << endl << endl;
		for (int i = 0; i < n; i++)
			cout << chislo1[i];
		cout << endl << endl << endl;
		for (int i = 0; i < n; i++)
			cout << chislo2[i];
		cout << endl << endl << endl;*/

		for (int i = 0; i < n; i++)
			arr1[i] = chislo1[n - 1 - i];
		for (int i = 0; i < n; i++)
			arr2[i] = chislo2[n - 1 - i];

		mult(arr1, arr2, arr3, n);
		add(arr3, n * 2);

		/*cout << "Результат умножения:" << endl << endl << endl;
		for (int i = 0; i < (n * 2); i++)
			cout << arr3[(n * 2) - 1 - i];
		cout << endl << endl << endl;*/

		cout << "Кол-во операций - " << kolop << "." << endl << endl << endl;
		kolop = 0;
	}

	return 0;
}