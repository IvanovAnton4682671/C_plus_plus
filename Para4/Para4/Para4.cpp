/*#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	for (int j = 0; j < 50; j++)
	{
		int n = 100000, i;
		double sum = 0.0, pi, h, x;
		h = 1.0 / (double)n;
		#pragma omp parallel private (i, x) shared (h, n, sum) num_threads(4)
		{
			double l_sum = 0.0;
			#pragma omp for
			for (i = 1; i <= n; i++)
			{
				x = h * ((double)i - 0.5);
				l_sum += (4.0 / (1.0 + (x * x)));
			}
			#pragma omp atomic
			sum += l_sum;
		}
		pi = h * sum;
		cout << "Число П = " << pi << "." << endl;
	}

	system("pause");
	return 0;
}*/

#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	int n = 100000, i;
	double sum = 0.0, tr, h1, h2, x;

	system("pause");
	return 0;
}