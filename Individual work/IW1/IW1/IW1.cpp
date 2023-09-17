#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int i, j;
double t1, t2;

void counting_sort(int* a, int* b, int n, int k)
{
	#pragma omp parallel num_threads(4) //shared(a, b) private(i, j)
	{
		#pragma omp for
		for (int i = 0; i < k; i++)
		{
			//#pragma omp atomic
			b[i] = 0;
		}
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			//#pragma omp atomic
			b[a[i]] = b[a[i]] + 1;
		}
		int i = 0;
		#pragma omp for
		for (int j = 0; j < k; j++)
		{
			//#pragma omp while
			while (b[j] != 0)
			{
				//#pragma omp atomic
				a[i] = j;
				//#pragma omp atomic
				b[j]--;
				//#pragma omp atomic
				i++;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	cout << "Эта программа выполняет сортировку целых чисел методом подсчёта." << endl;
	cout << "Пожалуйста, вводите корректные данные (пример: миллион значений в диапазоне от 0 до 1000)." << endl;
	cout << "Укажите кол-во сортируемых чисел: ";
	int n;
	cin >> n;
	cout << "Укажите, какой диапазон значений будет охватывать все ваши числа (от 0 до ...): ";
	int k;
	cin >> k;
	int* a = new int[n];
	cout << "Ваши числа:" << endl;
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % (k + 1);
		//cout << a[i] << " ";
	}
	int* b = new int[k];
	cout << endl;
	t1 = omp_get_wtime();
	counting_sort(a, b, n, k);
	t2 = omp_get_wtime();
	/*cout << "Отсортированные числа:" << endl;
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";*/
	cout << endl;
	cout << "Затраченное время: " << t2 - t1 << " секунд." << endl;

	cout << endl;
	system("pause");
	return 0;
}