//Для работы очереди нужны 4 операции: инициализировать очередь, добавить элемент в конец очереди, извлечь элемент из начала очереди, булевская операция "очередь не пуста" (проверка на пустоту).

struct queue
{
	int *q;
	int n;
	int k;
};

void init(queue &qu)
{
	qu.q = new int[100];
	qu.n = 0;
	qu.k = -1;
}

void push(queue &qu, int x)
{
	if (qu.k < 99)
	{
		qu.k++;
		qu.q[qu.k] = x;
	}
	else
		if (qu.n == 0)
			cout << "Очередь переполнена." << endl;
		else
		{
			for (int i = qu.n; i <= qu.k; i++)
				qu.q[i - qu.n] = qu.q[i];
			qu.k -= qu.n;
			qu.n = 0;
			qu.k++;
			qu.q[qu.k] = x;
		}
}

int pop(queue &qu)
{
	int x = -9999;
	if (qu.k >= qu.n)
	{
		x = qu.q[qu.n];
		qu.n++;
	}
	else
		cout << "Очередь пуста." << endl;
	return x;
}

bool notempty(queue &qu)
{
	return qu.k >= qu.n;
}