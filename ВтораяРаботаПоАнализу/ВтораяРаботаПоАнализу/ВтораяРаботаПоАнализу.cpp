//Практика - 2, Заглавная буква А                               //0001000
																//0010100
#include <iostream>                                             //0111110
#include <ctime>                                                //1000001
#include <cstdlib>

using namespace std;

struct tochka
{
	int x;
	int y;
};

void matrica(int** matr, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matr[i][j] = 0;
}

void image(int** matr, int n)
{
	tochka p1;
	p1.x = rand() % (n - 6) + 3;
	p1.y = rand() % (n - 3);
	matr[p1.y][p1.x] = 1;
	int lev = 0;
	for (int i = p1.x; i >= 0; i--)
			if (matr[i][p1.y] != 1)
				lev++;
	int prav = 0;
	for (int i = p1.x; i < n; i++)
			if (matr[i][p1.y] != 1)
				prav++;
	if (lev <= prav)
	{
		int p2 = rand() % lev;
		int i1 = p1.y;
		int j1 = p1.x;
		for (int k = p2; k >= 0; k--)
		{
			if (i1 < n && j1 < n)
				matr[i1][j1] = 1;
			i1++;
			j1++;
		}
		int i2 = p1.y;
		int j2 = p1.x;
		for (int k = p2; k >= 0; k--)
		{
			if (i2 < n && j2 < n)
				matr[i2][j2] = 1;
			i2++;
			j2--;
		}
		int sered = p1.y + (p2 / 2) + 1;
		int j_perv = 0;
		for (int j = 0; j < n; j++)
			if (matr[sered][j] == 1)
				j_perv = j;
		int j_vtor = 0;
		for (int j = (n-1); j >= 0; j--)
			if (matr[sered][j] == 1)
				j_vtor = j;
		for (int j = 0; j < n; j++)
			if (j < j_perv && j > j_vtor)
				matr[sered][j] = 1;
	}
	else
	{
		int p2 = rand() % prav;
		int i1 = p1.y;
		int j1 = p1.x;
		for (int k = p2; k >= 0; k--)
		{
			if (i1 < n && j1 < n)
				matr[i1][j1] = 1;
			i1++;
			j1++;
		}
		int i2 = p1.y;
		int j2 = p1.x;
		for (int k = p2; k >= 0; k--)
		{
			if (i2 < n && j2 < n)
				matr[i2][j2] = 1;
			i2++;
			j2--;
		}
		int sered = p1.y + (p2 / 2) + 1;
		int j_perv = 0;
		for (int j = 0; j < n; j++)
			if (matr[sered][j] == 1)
				j_perv = j;
		int j_vtor = 0;
		for (int j = (n - 1); j >= 0; j--)
			if (matr[sered][j] == 1)
				j_vtor = j;
		for (int j = 0; j < n; j++)
			if (j < j_perv && j > j_vtor)
				matr[sered][j] = 1;
	}
}

void print(int** matr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << matr[i][j] << "";
		cout << endl;
	}
	cout << endl; cout << endl; cout << endl;
}

void poisk(int** matr, int n)
{
	tochka point1, point2;
	int kolop = 0;
	point1.x = 0;
	point1.y = 0;
	point2.x = 0;
	point2.y = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matr[i][j] == 1)
			{
				point1.x = j;
				point1.y = i;
				kolop += 3;
			}
		}
	}
	for (int i = (n - 1); i >= 0; i--)
	{
		for (int j = (n - 1); j >= 0; j--)
		{
			if (matr[i][j] == 1)
			{
				point2.x = j;
				point2.y = i;
				kolop += 3;
			}
		}
	}
	if (point1.x == point2.x && point1.y == point2.y)
	{
		kolop += 2;
		cout << endl;
		cout << "Буквы нет." << endl;
		cout << "Колличество операций при поиске - " << kolop << endl;
		cout << endl << endl << endl;
	}
	else
	{
		cout << endl;
		cout << "Буква есть. Координаты: точка1 - " << point2.y << " " << point2.x << "; точка2 - " << point1.y << " " << point1.x << endl;
		cout << "Колличество операций при поиске - " << kolop << endl;
		cout << endl << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	for (int n = 10; n < 101; n += 10)
	{
		int** matr = new int* [n];
		for (int i = 0; i < n; i++)
			matr[i] = new int[n];
		matrica(matr, n);
		image(matr, n);
		print(matr, n);
		poisk(matr, n);
	}

	system("pause");
}