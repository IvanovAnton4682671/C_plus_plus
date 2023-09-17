#include <iostream>
using namespace std;
struct list
{
	int info;
	list*next;
	list*pred;
};
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
bool f(int x)
{
	int a = 0;
	for (int i = 1; i < x; i++)
		if (x % i == 0)
			a += i;
	if (a == x)
		return true;
	else
		return false;
}
/*int main()
{
	setlocale (LC_ALL, "rus");
	int x, n, s = 0;
	cout << "Введите количество элементов списка:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка:" << endl;
	cin >> x;
	list*p;
	list*h = new list;
	h->info = x;
	h->next = NULL;
	p = h;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка:" << endl;
		cin >> x;
		list*q = new list;
		q->info = x;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = h;
	cout << endl;
	cout << "Ваш список:" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	while (p != NULL)
	{
		s += p->info;
		p = p->next;
	}
	p = h;
	cout << endl;
	cout << "Сумма элементов списка - " << s << endl;
	system("pause");
}*/
/*int main ()
{
	setlocale (LC_ALL, "rus");
	int x, n, kol = 0;
	cout << "Введите количество элементов списка:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка:" << endl;
	cin >> x;
	list*p;
	list*h = new list;
	h->info = x;
	h->next = NULL;
	p = h;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка:" << endl;
		cin >> x;
		list*q = new list;
		q->info = x;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = h;
	cout << endl;
	cout << "Ваш список:" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	while (p->next != NULL)
	{
		if (p->info == p->next->info)
			kol++;
		p = p->next;
	}
	p = h;
	cout << "Количество пар стоящих рядом одинаковых чисел - " << kol << endl;
	system("pause");
}*/
/*int main ()
{
	setlocale(LC_ALL, "rus");
	int x, n;
	cout << "Введите количество элементов списка:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка:" << endl;
	cin >> x;
	list*p;
	list*h = new list;
	h->info = x;
	h->next = NULL;
	p = h;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка:" << endl;
		cin >> x;
		list*q = new list;
		q->info = x;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = h;
	cout << endl;
	cout << "Ваш список:" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	while (p->next != NULL)
	{
		if (prost(p->next->info) == true)
		{
			list*r = p->next;
			p->next = p->next->next;
			delete r;
		}
		else
			p = p->next;
	}
	if (prost(h->info) == true)
		h = h->next;
	p = h;
	cout << endl;
	cout << "Ваш изменённый список список (где удалены все простые элементы):" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	system("pause");
}*/
/*int main ()
{
	setlocale(LC_ALL, "rus");
	int x, n;
	cout << "Введите количество элементов списка:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка:" << endl;
	cin >> x;
	list*p;
	list*h = new list;
	h->info = x;
	h->next = NULL;
	p = h;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка:" << endl;
		cin >> x;
		list*q = new list;
		q->info = x;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = h;
	cout << endl;
	cout << "Ваш список:" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	int max;
	max = h->info;
	while (p != NULL)
	{
		if (p->info > max)
			max = p->info;
		p = p->next;
	}
	p = h;
	while (p != NULL)
	{
		if (p->info > 0)
		{
			list*q = new list;
			q->next = p->next;
			q->info = max;
			p->next = q;
			p = q;
		}
		p = p->next;
	}
	p = h;
	cout << endl;
	cout << "Ваш изменённый список список (где после положительных элементов вставленны новые со значением максимального):" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	system("pause");
}*/
/*int main ()
{
	setlocale(LC_ALL, "rus");
	int x, n;
	cout << "Введите количество элементов списка:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка:" << endl;
	cin >> x;
	list*p;
	list*h = new list;
	h->info = x;
	h->next = NULL;
	p = h;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка:" << endl;
		cin >> x;
		list*q = new list;
		q->info = x;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = h;
	cout << endl;
	cout << "Ваш список:" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	list*p1;
	list*h1 = new list;
	h1->next = NULL;
	p1 = h1;
	while (p != NULL)
	{
		if (f(p->info) == true)
		{
			list*q1 = new list;
			q1->info = p->info;
			q1->next = NULL;
			p1->next = q1;
			p1 = q1;
		}
		p = p->next;
	}
	h1 = h1->next;
	p = h1;
	cout << endl;
	cout << "Ваш новый список (который состоит из совершенных элементов первого списка):" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	system("pause");
}*/
/*int main ()
{
	setlocale (LC_ALL, "rus");
	int x, n, sum = 0;
	cout << "Введите количество элементов списка:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите голову списка:" << endl;
	cin >> x;
	list*p;
	list*h = new list;
	h->info = x;
	h->pred = NULL;
	h->next = NULL;
	p = h;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент списка:" << endl;
		cin >> x;
		list*q = new list;
		q->info = x;
		q->pred = p;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = h;
	cout << endl;
	cout << "Ваш список:" << endl;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
	p = h;
	while (p != NULL)
	{
		if (p->info > 0)
			sum += p->info;
		p = p->next;
	}
	p = h;
	cout << endl;
	cout << "Сумма положительных элементов списка - " << sum << endl;
	system("pause");
}*/