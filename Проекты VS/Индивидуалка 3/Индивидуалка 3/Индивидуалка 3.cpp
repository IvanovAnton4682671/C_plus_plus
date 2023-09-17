//Дано дерево двоичного поиска. Если все элементы дерева кратны 3, то заменить все элементы с нечётным количеством цифр их квадратами.
#include <iostream>
using namespace std;
struct tree
{
	int info;
	tree*l;
	tree*r;
};
void add(tree*t, int x)
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
void print(tree*t)
{
	if (t != NULL)
	{
		print(t->l);
		cout << t->info << " ";
		print(t->r);
	}
}
int proverka(tree*t, int &f)
{
	if (t != NULL)
	{
		if (t->info % 3 != 0)
			f = 0;
		proverka(t->l, f);
		proverka(t->r, f);
	}
	return f;
}
void zamena(tree*t)
{
	if (t != NULL)
	{
		int a = 0, x = t->info;
		while (x != 0)
		{
			x /= 10;
			a++;
		}
		if (a % 2 != 0)
			t->info = t->info*t->info;
		zamena(t->l);
		zamena(t->r);
	}
}
int main ()
{
	setlocale (LC_ALL, "rus");
	int n, x;
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
	int f = 1;
	proverka(root, f);
	if (f == 1)
		cout << "Все элементы дерева кратны 3." << endl;
	else
		cout << "Не все элементы дерева кратны 3." << endl;
	if (f == 1)
	{
		zamena(root);
		cout << endl;
		cout << "Ваше изменённое дерево:" << endl;
		print(root);
		cout << endl;
	}
	system("pause");
}