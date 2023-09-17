#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <fstream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

int Get_Random(int a, int b)
{
	random_device random;
	mt19937 generator(random());
	uniform_int_distribution<> r(a, b);
	int num = r(generator);
	return num;
}

void Gen_Pos_In_File(int n, string name)
{
	srand(time(NULL));

	double* mas = new double[n];
	for (int i = 0; i < n; i++)
		mas[i] = (Get_Random(1, 100)) * 1.1;

	ofstream file;
	file.open(name);
	for (int i = 0; i < n; i++)
		file << mas[i] << " ";
	file.close();
}

void Gen_Res_File(int n, string name3, string nameRes)
{
	double* mas = new double[n];
	
	ifstream file;
	string line;
	file.open(name3);
	if (file.is_open())
		while (!file.eof())
			for (int i = 0; i < n; i++)
				file >> mas[i];
	file.close();

	sort(mas, mas + n);

	ofstream fileRes;
	fileRes.open(nameRes);
	for (int i = 0; i < n; i++)
		fileRes << mas[i] << " ";
	fileRes.close();
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");

	int n = Get_Random(1, 100);
	string* mas = new string[n];

	for (int i = 0; i < n; i++)
	{
		string name1 = "File" + to_string(i + 1);
		string name2 = ".txt";
		string name = name1 + name2;
		Gen_Pos_In_File(n, name);
		mas[i] = name;
	}

	int numtasks, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (n % 4 == 0)
	{
		for (int i = (rank * (n / numtasks)); i < ((n / numtasks) * (rank + 1)); i++)
		{
			string name3 = mas[i];
			name3.erase(name3.length() - 4);
			string name4 = "_res.txt";
			string nameRes = name3 + name4;
			Gen_Res_File(n, mas[i], nameRes);
		}
	}
	else
	{
		if (rank == (numtasks - 1))
			for (int i = (rank * (n / numtasks)); i < ((n / numtasks) * (rank + 1)) + 1; i++)
			{
				string name3 = mas[i];
				name3.erase(name3.length() - 4);
				string name4 = "_res.txt";
				string nameRes = name3 + name4;
				Gen_Res_File(n, mas[i], nameRes);
			}
		else
			for (int i = (rank * (n / numtasks)); i < ((n / numtasks) * (rank + 1)); i++)
			{
				string name3 = mas[i];
				name3.erase(name3.length() - 4);
				string name4 = "_res.txt";
				string nameRes = name3 + name4;
				Gen_Res_File(n, mas[i], nameRes);
			}
	}

	MPI_Finalize();
	return 0;
	system("pause");
}

/*#include<mpi.h>
#include<iostream>
#include<ctime>
#include<string>
#include <stdio.h>
#include <fstream>


using namespace std;

void  printMatrix(double** Mat, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << Mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void matrixTranspose(double** Mat, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int t = Mat[i][j];
			Mat[i][j] = Mat[j][i];
			Mat[j][i] = t;

		}
	}
}

void copyMat(double** Mat, double** MatDef, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			MatDef[i][j] = Mat[i][j];
		}
	}
}

void summaMat(double** Mat, double** MatDef, double** MatRes, int n) {


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			MatRes[i][j] = (MatDef[i][j] + Mat[i][j]);
			MatRes[i][j] /= 2;
		}
	}
}
int main(int argc, char** argv) {

	ifstream fileOpen("1.txt");
	string stroka;
	double** Mat;
	double** MatDef;

	int numtasks, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (fileOpen.is_open())
	{
		fileOpen >> stroka;
		int n = stoi(stroka);
		Mat = new double* [n];
		MatDef = new double* [n];
		double** ResMat = new double* [n];


		for (int i = (rank * (n / numtasks)); i < ((n / numtasks) * (rank + 1)); i++)
		{
			Mat[i] = new double[n];
			MatDef[i] = new double[n];
			ResMat[i] = new double[n];
		}

		for (int i = (rank * (n / numtasks)); i < ((n / numtasks) * (rank + 1)); i++)
		{
			for (int j = (rank * (n / numtasks)); j < ((n / numtasks) * (rank + 1)); j++)
			{
				fileOpen >> stroka;
				Mat[i][j] = stod(stroka);
			}
		}

		copyMat(Mat, MatDef, n);

		matrixTranspose(Mat, n);
		printMatrix(Mat, n);
		printMatrix(MatDef, n);
		
		summaMat(Mat, MatDef, ResMat, n);
		printMatrix(ResMat, n);
	}

	MPI_Finalize();
	return 0;
	system("pause");
}*/

/*#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>

using namespace std;

void printMatrix(double** A, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

void transpose(double** A, int n) {
	double t;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			t = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = t;
		}
	}
}


int main(int argc, char** argv) {
	ifstream fileOpen("f.txt");
	string line;
	double** A;
	int numtasks, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	if (fileOpen.is_open()) {
		fileOpen >> line;
		int n = stoi(line);
		A = new double* [n];
		for (int i = (rank * (n / numtasks)); i < ((n / numtasks) * (rank + 1)); i++) {
			A[i] = new double[n];
		}
		for (int i = (rank * (n / numtasks)); i < ((n / numtasks) * (rank + 1)); i++) {
			for (int j = (rank * (n / numtasks)); j < ((n / numtasks) * (rank + 1)); j++) {
				fileOpen >> line;
				A[i][j] = stod(line);
			}
		}
		transpose(A, n);
		printMatrix(A, n);
	}
	else {
		cout << "not file" << endl;
	}
	fileOpen.close();
	MPI_Finalize();
	return 0;
	system("pause");
}*/