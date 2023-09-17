#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	double t1 = omp_get_wtime();

	#pragma omp parallel num_threads(4)
	{
		cout << "Параллельная область 1 (поток № " << omp_get_thread_num() << ")" << endl;
	}

	cout << endl;
	double t2 = omp_get_wtime();
	cout << "Прошло времени: " << t2 - t1 << " секунд" << endl;

	cout << endl;
	cout << "------------------------------" << endl;
	cout << "------------------------------" << endl;
	cout << "------------------------------" << endl;
	cout << endl;

	double t3 = omp_get_wtime();

	omp_set_num_threads(4);
	#pragma omp parallel
	{
		cout << "Параллельная область 2 (поток № " << omp_get_thread_num() << ")" << endl;
	}

	cout << endl;
	double t4 = omp_get_wtime();
	cout << "Прошло времени: " << t4 - t3 << " секунд" << endl;

	system("pause");
	return 0;
}