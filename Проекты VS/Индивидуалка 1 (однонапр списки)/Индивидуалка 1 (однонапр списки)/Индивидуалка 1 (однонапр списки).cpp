//Дано 2 однонаправленных списка целых чисел. Заменить все элементы с чётной суммой цифр из первого списка на наибольший элемент из второго списка.
#include <iostream>
using namespace std;
struct list
{
	int info;
	list*next;
};
void add(list*p, int x)
{
	while (p->next != NULL)
		p = p->next;
	list*q = new list;
	q->info = x;
	q->next = NULL;
	p->next = q;
}
void print(list*p)
{
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
}
bool chet(int x)
{
	int a = 0;
	while (x != 0)
	{
		a += x % 10;
		x /= 10;
	}
	if (a % 2 == 0)
		return true;
	else
		return false;
}
int main ()
{
	setlocale (LC_ALL, "rus");
	int n, x;
	cout << "Введите количество элементов списка 1:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка 1:" << endl;
	cin >> x;
	list*p1;
	list*h1 = new list;
	h1->info = x;
	h1->next = NULL;
	p1 = h1;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка 1:" << endl;
		cin >> x;
		add(p1, x);
	}
	p1 = h1;
	cout << endl;
	cout << "Ваш список 1:" << endl;
	print(p1);
	cout << endl;
	p1 = h1;
	cout << endl;
	cout << "Введите количество элементов списка 2:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка 2:" << endl;
	cin >> x;
	list*p2;
	list*h2 = new list;
	h2->info = x;
	h2->next = NULL;
	p2 = h2;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка 2:" << endl;
		cin >> x;
		add(p2, x);
	}
	p2 = h2;
	cout << endl;
	cout << "Ваш список 2:" << endl;
	print(p2);
	cout << endl;
	p2 = h2;
	int max2 = 0;
	while (p2 != NULL)
	{
		if (p2->info > max2)
			max2 = p2->info;
		p2 = p2->next;
	}
	p2 = h2;
	cout << endl;
	cout << "Максимальный элемент списка 2 - " << max2 << endl;
	while (p1 != NULL)
	{
		if (chet(p1->info) == true)
			p1->info = max2;
		p1 = p1->next;
	}
	p1 = h1;
	cout << endl;
	cout << "Ваш изменённый список 1:" << endl;
	print(p1);
	cout << endl;
	p1 = h1;
	system("pause");
}