/*9. В трехмерном пространстве задано множество материальных точек. Каждая из точек с максимальной массой исчезает, теряя десятую часть своей массы и раздавая оставшуюся массу поровну всем остальным,
более «легким» точкам. Определить суммарную массу множества материальных точек в тот момент, когда все оставшиеся в нем точки имеют одинаковую массу.*/

/*Программа должна работать так: ищем точку с максимальной массой; отнимаем от этой массы 10% (чтобы найти 10% - умножаем число на 0.1); оставшуюся массу делим на кол-во оставшихся точек,
и раздаём эти части массы им; повторяем эти действия, пока не останутся точки с одинаковой массой; считаем сумму их масс и выводим в качестве ответа.*/

/*Особенности, которые дожны учитываться: если есть только точки с одинаковой массой - считаем сумму (это ответ); если есть 1 точка с максимальной массой, а другие - с другой,
то выполняем действия по умолчанию; если есть несколько точек с максимальной массой, а другие - с другой, то выполняем обычные операции, но исключаем из них другие точки с максимальной массой.*/

#include <iostream>
#include <vector>
using namespace std;
struct prostranstvo
{
	float ves;
	int ox;
	int oy;
	int oz;
};
void mv(vector <prostranstvo> t, float &maxves)                                          //функция, которая находит максимальную массу среди всех точек
{
	for (int i = 0; i < t.size(); i++)
		if (t[i].ves > maxves)
			maxves = t[i].ves;
}
void nt(vector <prostranstvo> t, float &maxves)                                          //функция, которая находит элемент, делает все манипуляции с весом, и удаляет его
{
	for (vector <prostranstvo>::iterator it = t.begin(); it != t.end();)
	{
		if (it->ves == maxves)
		{
			float nyjves = it->ves;
			float desves = it->ves * 0.1;
			float ostves = nyjves - desves;
			int kol = 0;
			for (int i = 0; i < t.size(); i++)
				if (t[i].ves < maxves)
					kol++;
			for (int i = 0; i < t.size(); i++)
				if (t[i].ves < maxves)
					t[i].ves += ostves / kol;
			t.erase(it);
			for (int i = 0; i < t.size(); i++)
				cout << "Вес точки - " << t[i].ves << "; ко-та по X - " << t[i].ox << "; ко-та по Y - " << t[i].oy << "; ко-та по Z - " << t[i].oz << "." << endl;
			break;

		}
		else
			it++;
	}
}
int main()
{
	setlocale(LC_ALL, "rus");
	vector <prostranstvo> t;
	int n;
	cout << "Введите количество точек:" << endl;
	cout << endl;
	cin >> n;
	cout << endl;
	cout << "Введите точки (вес, координаты по X, Y, Z):" << endl;
	cout << endl;
	prostranstvo x;
	for (int i = 0; i < n; i++)
	{
		cin >> x.ves >> x.ox >> x.oy >> x.oz;
		t.push_back(x);
	}
	cout << endl;
	cout << "Введённые точки:" << endl;
	cout << endl;
	for (int i = 0; i < t.size(); i++)
		cout << "Вес точки - " << t[i].ves << "; ко-та по X - " << t[i].ox << "; ко-та по Y - " << t[i].oy << "; ко-та по Z - " << t[i].oz << "." << endl;
	cout << endl;
	
}