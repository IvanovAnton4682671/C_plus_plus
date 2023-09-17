/*#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

void print_block(int n, char c)
{
	mtx.lock();
	for (int i = 0; i < n; i++)
		cout << c;
	cout << endl;
	mtx.unlock();
}

int main()
{
	setlocale(LC_ALL, "rus");

	thread th1(print_block, 40, '+');
	thread th2(print_block, 40, '-');
	th1.join();
	th2.join();

	system("pause");
	return 0;
}*/

/*#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	int count, num;
	#pragma omp parallel
	{
		count = omp_get_num_threads();
		num = omp_get_thread_num();
		if (num == 0)
			cout << "Всего нитей: " << count << "." << endl;
		else cout << "Нить №" << num << "." << endl;
	}

	system("pause");
	return 0;
}*/

/*#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	int s = 0, i, n;
	#pragma omp parallel private (i, n) reduction(+:s)
	{
		n = omp_get_thread_num();
		#pragma omp for
		for (i = 1; i < 10; i++)
		{
			s += i;
			cout << "Нить №" << n << " сложила элементы с номером " << i << "." << endl;
		}
		cout << "Результат нити №" << omp_get_thread_num() << " = " << s << "." << endl;
	}
	cout << "Общая сумма = " << s << "." << endl;

	system("pause");
	return 0;
}*/

#include <iostream>
#include <omp.h>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n = 50000;
int i, num;
double t1, t2;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	int a[n], b[n], c[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % (n + 1);
		b[i] = rand() % (n + 1);
	}
	#pragma omp parallel num_threads(4) shared(a, b, c) private (i, num)
	{
		t1 = omp_get_wtime();
		num = omp_get_thread_num();
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			c[i] = a[i] + b[i];
			cout << c[i] << " ";
		}
		t2 = omp_get_wtime();
	}
	cout << endl;
	cout << "Затраченное время = " << t2 - t1 << " секунд." << endl;

	system("pause");
	return 0;
}