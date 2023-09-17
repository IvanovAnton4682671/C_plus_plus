/*9. В трехмерном пространстве задано множество материальных точек. Каждая из точек с максимальной массой исчезает, теряя десятую часть своей массы и раздавая оставшуюся массу поровну всем остальным,
более «легким» точкам. Определить суммарную массу множества материальных точек в тот момент, когда все оставшиеся в нем точки имеют одинаковую массу.*/

/*Программа должна работать так: ищем точку с максимальной массой; отнимаем от этой массы 10% (чтобы найти 10% - умножаем число на 0.1); оставшуюся массу делим на кол-во оставшихся точек,
и раздаём эти части массы им; повторяем эти действия, пока не останутся точки с одинаковой массой; считаем сумму их масс и выводим в качестве ответа.*/

/*Особенности, которые дожны учитываться: если есть только точки с одинаковой массой - считаем сумму (это ответ); если есть 1 точка с максимальной массой, а другие - с другой,
то выполняем действия по умолчанию; если есть несколько точек с максимальной массой, а другие - с другой, то выполняем обычные операции, но исключаем из них другие точки с максимальной массой.*/

#include <iostream>
using namespace std;
struct list
{
	list*pred;
	list*next;
	float ves;
	int ox;
	int oy;
	int oz;
};
void tochki(list*P, list*H, list*P1, float &znmn)
{
	P = H;
	bool f = true;
	while (P != NULL)
	{
		if (P->ves != P->next->ves)
		{
			f = false;
			break;
		}
		else
			P = P->next;
	}
	P = H;
	if (f == false)
	{
		P1 = H;
		float maxves = -1;
		while (P != NULL)                          //ищем значение максимального веса
		{
			if (P->ves > maxves)
				maxves = P->ves;
			P = P->next;
		}
		P = H;
		while (P != NULL)                          //ищем точку со значением максимального веса
		{
			if (P->ves == maxves)
				break;
			else
				P = P->next;
		}
		float desprves = P->ves * 0.1;
		float ostves = P->ves - desprves;
		int kolt = 0;
		while (P1 != NULL)                         //ищем ко-во точек, чей вес ниже максимального (им будем раздавать массу)
		{
			if (P1->ves < maxves)
				kolt++;
			P1 = P1->next;
		}
		P1 = H;
		while (P1 != NULL)
		{
			if (P1->ves < maxves)
				P1->ves = P1->ves + (ostves / kolt);
			P1 = P1->next;
		}
		P1 = H;
		if (P != NULL)
		{
			if (P->pred == NULL)
			{
				list*l = P;
				P = P->next;
				P->pred = NULL;
				delete l;
				P = H;
				while (P != NULL)
				{
					cout << "Вес точки - " << P->ves << ";" << " ко-та по X - " << P->ox << ";" << " ко-та по Y - " << P->oy << ";" << " ко-та по Z - " << P->oz << "." << endl;
					P = P->next;
				}
				cout << endl;
				tochki(P, H, P1, znmn);
			}
			if (P->next == NULL)
			{
				list*l = P;
				P->pred->next = NULL;
				delete l;
				P = H;
				while (P != NULL)
				{
					cout << "Вес точки - " << P->ves << ";" << " ко-та по X - " << P->ox << ";" << " ко-та по Y - " << P->oy << ";" << " ко-та по Z - " << P->oz << "." << endl;
					P = P->next;
				}
				cout << endl;
				tochki(P, H, P1, znmn);
			}
			if (P->pred != NULL && P->next != NULL)
			{
				list*l = P;
				P->pred->next = P->next;
				P->next->pred = P->pred;
				delete l;
				P = H;
				while (P != NULL)
				{
					cout << "Вес точки - " << P->ves << ";" << " ко-та по X - " << P->ox << ";" << " ко-та по Y - " << P->oy << ";" << " ко-та по Z - " << P->oz << "." << endl;
					P = P->next;
				}
				cout << endl;
				tochki(P, H, P1, znmn);
			}
		}
	}
	else
	{
		P = H;
		while (P != NULL)
		{
			znmn += P->ves;
			P = P->next;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	list*p;
	list*p1;
	int n;
	cout << "Введите количество точек:" << endl;
	cout << endl;
	cin >> n;
	float t;
	int x1, y1, z1;
	cout << endl;
	cout << "Введите ваши точки (вес, координаты по X, Y, Z):" << endl;
	cout << endl;
	cin >> t >> x1 >> y1 >> z1;
	list*h = new list;
	h->ves = t;
	h->ox = x1;
	h->oy = y1;
	h->oz = z1;
	h->pred = NULL;
	h->next = NULL;
	p = h;
	for (int i = 1; i < n; i++)
	{
		cin >> t >> x1 >> y1 >> z1;
		list*q = new list;
		q->ves = t;
		q->ox = x1;
		q->oy = y1;
		q->oz = z1;
		q->pred = p;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	p = h;
	cout << endl;
	cout << "Ваше введённое множество точек:" << endl;
	cout << endl;
	while (p != NULL)
	{
		cout << "Вес точки - " << p->ves << ";" << " ко-та по X - " << p->ox << ";" << " ко-та по Y - " << p->oy << ";" << " ко-та по Z - " << p->oz << "." << endl;
		p = p->next;
	}
	cout << endl;
	p = h;
	p1 = h;
	float znmn = 0;
	tochki(p, h, p1, znmn);
	cout << "Ответ: масса множества, в котором все точки имеют одинаковую массу - " << znmn << "." << endl;
	cout << endl;
	system("pause");
}