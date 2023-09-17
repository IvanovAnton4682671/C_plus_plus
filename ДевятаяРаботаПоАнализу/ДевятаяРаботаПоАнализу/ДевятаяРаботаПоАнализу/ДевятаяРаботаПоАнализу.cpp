#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

int kolop = 0;

void G1g(int** m, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i <= j)
				m[i][j] = rand() % 2;
			else
				m[i][j] = -1;
		}
}

void Dopolnenie(int** m, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (m[i][j] == -1)
				m[i][j] = m[j][i];
}

void MenMest(int** m, int a1, int a2, int n)
{
	for (int i = 0; i < n; i++)
	{
		int nomer = m[a1][i];
		m[a1][i] = m[a2][i];
		m[a2][i] = nomer;
	}
}

void G2g(int** m2, int n)
{
	int r = rand() % (n);
	for (int i = 0; i < r; i++)
	{
		int a1 = rand() % (n - 1);
		int a2 = rand() % (n - 1);
		if (a1 == a2)
		{
			if (a1 == (n - 1))
				a2--;
			else
				a2++;
		}
		MenMest(m2, a1, a2, n);
	}
}

bool Poisk(int** m, int** m2, int n)
{
	int kol = 0;
	kolop++;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int b = 0;
			kolop++;
			for (int v = 0; v < n; v++)
			{
				if (m[i][j] == m2[i][j])
					b++;
				kolop += 3;
			}
			if (b == n)
			{
				kol++;
				kolop += 2;
				break;
			}
		}
	kolop++;
	if (kol == n)
		return true;
	return false;
}

void G2Poln(int** m, int** m2, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			m2[i][j] = m[i][j];
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	for (int i = 1; i < 21; i++)
	{
		int n = i;
		cout << "Кол-во вершин в графе - " << n << endl;
		int** G1 = new int* [n];
		for (int i = 0; i < n; i++)
			G1[i] = new int[n];
		int** G2 = new int* [n];
		for (int i = 0; i < n; i++)
			G2[i] = new int[n];
		G1g(G1, n);
		Dopolnenie(G1, n);
		G2Poln(G1, G2, n);
		G2g(G2, n);
		bool f = Poisk(G1, G2, n);
		if (f == true)
			cout << "Ваши графы изоморфны" << endl;
		else
			cout << "Ваши графы не изоморфны" << endl;
		cout << "Кол-во операций - " << kolop << endl << endl;
		kolop = 0;
	}

	system("pause");
}