//Нет смысла делать потоков больше, чем ядер.
//Проект -> Свойства -> С/С++ -> Язык -> Поддержка Open MP -> Кликнуть справа по пустому полю, выбрать "Да", нажать "Применить", потом "Ок".

#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	cout << "Последовательная область" << endl;
	#pragma omp parallel num_threads(4)
	{
		cout << "Нить №" << omp_get_thread_num() << endl;
	}
	cout << "Последовательаня область" << endl;
}