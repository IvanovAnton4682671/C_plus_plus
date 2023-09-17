//Дан двунаправленный список целых чисел. Получить однонаправленный список, содержащий все элементы исходного, порядковые номера которых являются простыми числами, а значения не являются простыми.
#include<iostream>
using namespace std;
struct list
{
	int info;
	list*pred;
	list*next;
	int nomer;
};
void print(list*p)
{
	while (p != NULL)
	{
		cout << p->nomer << " " << p->info << endl;
		p = p->next;
	}
}
bool prost(int x)
{
	int a = 0;
	for (int i = 1; i <= x; i++)
		if (x % i == 0)
			a++;
	if (a == 2)
		return true;
	else
		return false;
}
int main ()
{
	setlocale (LC_ALL, "rus");
	int n, x, nom = 1;
	cout << "Введите количество элементов списка 1:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка 1:" << endl;
	cin >> x;
	list*p1;
	list*h1 = new list;
	h1->info = x;
	h1->pred = NULL;
	h1->next = NULL;
	h1->nomer = nom;
	p1 = h1;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка 1:" << endl;
		cin >> x;
		nom++;
		list*q = new list;
		q->info = x;
		q->pred = p1;
		q->next = NULL;
		p1->next = q;
		q->nomer = nom;
		p1 = q;
	}
	p1 = h1;
	cout << endl;
	cout << "Ваш список 1:" << endl;
	print(p1);
	cout << endl;
	p1 = h1;
	list*p2;
	list*h2 = new list;
	h2->info = 0;
	h2->next = NULL;
	p2 = h2;
	while (p1 != NULL)
	{
		if (prost(p1->nomer) == true && prost(p1->info) == false)
		{
			list*q2 = new list;
			q2->nomer = p1->nomer;
			q2->info = p1->info;
			q2->next = NULL;
			p2->next = q2;
			p2 = q2;
		}
		p1 = p1->next;
	}
	p2 = h2;
	h2 = h2->next;
	p2 = h2;
	cout << "Сформированный список 2:" << endl;
	print(p2);
	cout << endl;
	p2 = h2;
	system("pause");
}