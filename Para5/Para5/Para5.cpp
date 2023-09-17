/*#include <stdio.h>
#include <mpi.h>

using namespace std;

int main(int* argc, char** argv)
{
	int numtasks, rank;

	MPI_Init(argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	printf("Hello MPI from process = %d, total number of processes: %d.\n", rank, numtasks);

	MPI_Finalize();
}*/

/*#include<stdio.h>
#include"mpi.h"
#include<iostream>

using namespace std;

int main(int* argc, char** argv)
{
	int a = 13, b;
	MPI_Status st;

	int numtasks, rank;

	MPI_Init(argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (rank == 0)
	{
		MPI_Send(&a, 1, MPI_INT, 3, 15, MPI_COMM_WORLD);
	}
	else if (rank == 3)
	{
		MPI_Recv(&b, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, &st);
		cout << rank << " " << b;
	}
	MPI_Finalize();
}*/

/*#include <math.h>
#include "mpi.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	int N = 100, k, rank, world_size, ibeg, iend;
	double ProcSum = 0.0;
	double TotalSum;
	double startwtime = 0.0, endwtime;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	cout << "Process " << rank << " of " << world_size << " Started" << endl;
	double x[100];
	if (rank == 0)
	{
		for (int i = 0; i < N; i++)
		{
			x[i] = i;
		}
		startwtime = MPI_Wtime();
	}
	if (world_size > N)
		world_size = N;
	MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	k = N / world_size;
	ibeg = k * rank;
	iend = k * (rank + 1);
	if (rank == world_size - 1)
		iend = N;
	for (int i = ibeg; i < iend; i++)
		ProcSum = ProcSum + x[i];
	if (rank == 0)
	{
		TotalSum = ProcSum;
		for (int i = 1; i < world_size; i++)
		{
			MPI_Recv(&ProcSum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
			endwtime = MPI_Wtime();
			cout << "Sum of process number " << i << " = " << ProcSum << endl;
			TotalSum += ProcSum;
		}
	}
	else MPI_Send(&ProcSum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		printf("\nTotal Sum = %10.2f", TotalSum);
		cout << " time is " << endwtime - startwtime << endl;
	}
	MPI_Finalize();
	return 0;
}*/

/*#include <iostream>
#include <ctime>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[])
{
	double start, stop;
	int *a, *b, *c, *buffer, *ans, i, j, k, l, size = 10, rank, numprocs, line;
	srand(time(NULL));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	line = size / numprocs;
	a = new int[size * size];
	b = new int[size * size];
	c = new int[size * size];
	buffer = new int[size * size];
	ans = new int[size * size];
	if (rank == 0)
	{
		start = MPI_Wtime();
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				a[i * size + j] = rand() % 100 + 1;
		cout << "A:" << endl;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
				cout << a[i * size + j] << " ";
			cout << endl;
		}
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				b[i * size + j] = rand() % 100 + 1;
		cout << "B:" << endl;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
				cout << b[i * size + j] << " ";
			cout << endl;
		}
		for (i = 1; i < numprocs; i++)
			MPI_Send(b, size * size, MPI_INT, i, 0, MPI_COMM_WORLD);
		for (l = 1; l < numprocs; l++)
			MPI_Send(a + (l - 1) * line * size, size * line, MPI_INT, l, 1, MPI_COMM_WORLD);
		for (k = 1; k < numprocs; k++)
		{
			MPI_Recv(ans, line * size, MPI_INT, k, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (i = 0; i < line; i++)
				for (j = 0; j < size; j++)
					c[((k - 1) * line + i) * size + j] = ans[i * size + j];
		}
		for (i = (numprocs - 1) * line; i < size; i++)
			for (j = 0; j < size; j++)
			{
				int temp = 0;
				for (k = 0; k < size; k++)
					temp += a[i * size + k] * b[k * size + j];
				c[i * size + j] = temp;
			}
		cout << "C:" << endl;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
				cout << c[i * size + j] << " ";
			cout << endl;
		}
		stop = MPI_Wtime();
		printf("rank:%d time:%lfs\n", rank, stop - start);
		delete [] a;
		delete [] b;
		delete [] c;
		delete [] buffer;
		delete [] ans;
	}
	else
	{
		MPI_Recv(b, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(buffer, size * line, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				int temp = 0;
				for (k = 0; k < size; k++)
					temp += buffer[i * size + k] * b[k * size + j];
				ans[i * size + j] = temp;
			}
		MPI_Send(ans, line * size, MPI_INT, 0, 3, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}*/

/*#include <iostream>
#include <mpi.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{

	int numtasks, rank, next, prev, buf[2], tag1 = 1, tag2 = 2;
	MPI_Request resq[4];
	MPI_Status stats[4];
	MPI_Init(&argc, &argv);
	setlocale(LC_ALL, "rus");
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	prev = rank - 1;
	next = rank + 1;
	if (rank == 0) prev = numtasks - 1;
	if (rank == (numtasks - 1)) next = 0;

	MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &resq[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &resq[1]);
	MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &resq[2]);
	cout << "Процесс " << prev << " передал процессу " << next << " данные " << rank << "." << endl;
	MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &resq[3]);
	cout << "Процесс " << prev << " передал процессу " << next << " данные " << rank << "." << endl;

	MPI_Waitall(4, resq, stats);
	cout << "Процесс " << prev << " получил от процесса  " << next << " данные " << buf[0] << "." << endl;
	cout << "Процесс " << prev << " получил от процесса " << next << " данные " << buf[1] << "." << endl;
	MPI_Finalize();
	return 0;
}*/

/*#include <iostream>
#include <mpi.h>
#include <stdio.h>
#define SIZE 4

using namespace std;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	int numtasks, rank, sendcount, recvcount, source;
	float sendbuf[SIZE][SIZE] = { {1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}, {9.0, 10.0, 11.0, 12.0}, {13.0, 14.0, 15.0, 16.0} };
	float recvbuf[SIZE];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	if (numtasks == SIZE)
	{
		source = 1;
		sendcount = SIZE;
		recvcount = SIZE;
		MPI_Scatter(sendbuf, sendcount, MPI_FLOAT, recvbuf, recvcount, MPI_FLOAT, source, MPI_COMM_WORLD);
		printf("Rank = %d. Results: %f %f %f %f\n", rank, recvbuf[0], recvbuf[1], recvbuf[2], recvbuf[3]);
	}
	else printf("Число процессов должно быть равно %d. \n", SIZE);
	MPI_Finalize();
}*/