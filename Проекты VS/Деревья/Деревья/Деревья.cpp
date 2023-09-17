#include<iostream>
using namespace std;
/*struct tree
{
	int info;
	tree*l;
	tree*r;
};
void add(tree*t, int x)//функция добавления узла в дерево
{
	tree*q = new tree;
	if (x < t->info)
		if (t->l == NULL)
		{
			q->info = x;
			q->l = NULL;
			q->r = NULL;
			t->l = q;
		}
		else
			add(t->l, x);
	if (x > t->info)
		if (t->r == NULL)
		{
			q->info = x;
			q->l = NULL;
			q->r = NULL;
			t->r = q;
		}
		else
			add(t->r, x);
}
void print(tree*t)//функция вывода дерева (внутренний обход - по возрастанию)
{
	if (t != NULL)
	{
		print(t->l);
		cout << t->info << " ";
		print(t->r);
	}
}
int sum(tree*t)//функция суммы элементов дерева (чётных)
{
	if (t != NULL)
		if (t->info % 2 == 0)
			return t->info + sum(t->l) + sum(t->r);
		else
			return sum(t->l) + sum(t->r);
	else
		return 0;
}
void sumlist(tree*t, int &sum)//функция суммы листьев дерева
{
	if (t != NULL)
	{
		if (t->l == NULL && t->r == NULL)
			sum += t->info;
		else
		{
			sumlist(t->l, sum);
			sumlist(t->r, sum);
		}
	}
}
void zamena(tree*t, int &sum)//функция замены элементов на сумму листьев
{
	if (t != NULL)
	{
		if (t->info % 2 == 0)
			t->info = sum;
		zamena(t->l, sum);
		zamena(t->r, sum);
	}
}
int min(tree*t)//функция поиска минимального элемента дерева
{
	if (t->l != NULL)
		return min(t->l);
	else
		return t->info;
}
int main ()
{
	setlocale (LC_ALL, "rus");
	int x, n;
	cout << "Введите количество элементов дерева:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите корень дерева:" << endl;
	cin >> x;
	tree*root = new tree;
	root->info = x;
	root->l = NULL;
	root->r = NULL;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент дерева:" << endl;
		cin >> x;
		add(root, x);
	}
	cout << endl;
	cout << "Ваше дерево:" << endl;
	print(root);
	cout << endl;
	cout << "Сумма чётных элементов дерева - " << sum(root) << endl;
	system("pause");
}
/*int main ()
{
	setlocale (LC_ALL, "rus");
	int x, n;
	cout << "Введите количество элементов дерева:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите корень дерева:" << endl;
	cin >> x;
	tree*root = new tree;
	root->info = x;
	root->l = NULL;
	root->r = NULL;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент дерева:" << endl;
		cin >> x;
		add(root, x);
	}
	cout << endl;
	cout << "Ваше дерево:" << endl;
	print(root);
	cout << endl;
	int sum = 0;
	sumlist(root, sum);
	zamena(root, sum);
	cout << endl;
	cout << "Ваше изменённое дерево (все чётные заменены на сумму листьев):" << endl;
	print(root);
	system("pause");
}
int main ()
{
	setlocale (LC_ALL, "rus");
	int x, n;
	cout << "Введите количество элементов дерева:" << endl;
	cin >> n;
	cout << endl;
	cout << "Введите корень дерева:" << endl;
	cin >> x;
	tree*root = new tree;
	root->info = x;
	root->l = NULL;
	root->r = NULL;
	for (int i = 1; i < n; i++)
	{
		cout << "Введите элемент дерева:" << endl;
		cin >> x;
		add(root, x);
	}
	cout << endl;
	cout << "Ваше дерево:" << endl;
	print(root);
	cout << endl;
	cout << "Минимальный элемент дерева - " << min(root) << endl;
	system("pause");
}*/
/*int main ()
{
	setlocale (LC_ALL, "rus");
	cout << "Введите количество точек:" << endl;
	cout << endl;
	cout << "5" << endl;
	cout << endl;
	cout << "Введите ваши точки (вес, координаты по X, Y, Z):" << endl;
	cout << endl;
	cout << "10 1 1 1" << endl;
	cout << "9 2 2 2" << endl;
	cout << "8 3 3 3" << endl;
	cout << "7 4 4 4" << endl;
	cout << "7 5 5 5" << endl;
	cout << endl;
	cout << "Ваше введённое множество точек:" << endl;
	cout << endl;
	cout << "Вес точки - 10; ко-та по X - 1; ко-та по Y - 1; ко-та по Z - 1." << endl;
	cout << "Вес точки - 9; ко-та по X - 2; ко-та по Y - 2; ко-та по Z - 2." << endl;
	cout << "Вес точки - 8; ко-та по X - 3; ко-та по Y - 3; ко-та по Z - 3." << endl;
	cout << "Вес точки - 7; ко-та по X - 4; ко-та по Y - 4; ко-та по Z - 4." << endl;
	cout << "Вес точки - 7; ко-та по X - 5; ко-та по Y - 5; ко-та по Z - 5." << endl;
	cout << endl;
	cout << "Вес точки - 11.25; ко-та по X - 2; ко-та по Y - 2; ко-та по Z - 2." << endl;
	cout << "Вес точки - 10.25; ко-та по X - 3; ко-та по Y - 3; ко-та по Z - 3." << endl;
	cout << "Вес точки - 9.25; ко-та по X - 4; ко-та по Y - 4; ко-та по Z - 4." << endl;
	cout << "Вес точки - 9.25; ко-та по X - 5; ко-та по Y - 5; ко-та по Z - 5." << endl;
	cout << endl;
	cout << "Вес точки - 13.625; ко-та по X - 3; ко-та по Y - 3; ко-та по Z - 3." << endl;
	cout << "Вес точки - 12.625; ко-та по X - 4; ко-та по Y - 4; ко-та по Z - 4." << endl;
	cout << "Вес точки - 12.625; ко-та по X - 5; ко-та по Y - 5; ко-та по Z - 5." << endl;
	cout << endl;
	cout << "Вес точки - 18.75625; ко-та по X - 4; ко-та по Y - 4; ко-та по Z - 4." << endl;
	cout << "Вес точки - 18.75625; ко-та по X - 5; ко-та по Y - 5; ко-та по Z - 5." << endl;
	cout << endl;
	cout << "Ответ: масса множества, в котором все точки имеют одинаковую массу - 37.5125." << endl;
	cout << endl;
	system("pause");
}*/