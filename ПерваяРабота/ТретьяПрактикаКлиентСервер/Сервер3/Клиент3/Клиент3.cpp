#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

// структура данных запроса клиента

struct Person
{
	char name[25];
	int math;
	int diskretka;
	int algebra;
	int proga;
	int dolg;
	char faculty[25];
} A;


void main() {
	setlocale(LC_ALL, "Rus");

	//const char* nameR = "REQUEST.bin";
	string nameR = "Request.bin";

	//файл для запросов клиентов
	//const char* nameA = "ANSWER.bin";
	//файл для ответов сервера
	ofstream f_REQ;
	ifstream f_ANS;
	long pred_size;
	int answer;

	cout << "Клиент начал свою работу. Можете начинать работу." << endl;
	cout << "Введите название вашего факультета: " << endl;
	cin >> A.faculty;
	string nameA = A.faculty;
	f_ANS.open(nameA + ".bin", ios::app, ios::binary);
	f_ANS.close();

	while (true)
	{
		// Получаем название файла и создаём файл с ответом для него


		// передача данных от клиента серверу
		cout << "Введите фамилию: " << endl;
		cin >> A.name;
		// получаем оценки по предметам
		cout << "Введите оценки по предметам" << endl;
		cout << "Алгебра: " << endl;
		cin >> A.algebra;
		cout << "Дискретка: " << endl;
		cin >> A.diskretka;
		cout << "Математический анализ: " << endl;
		cin >> A.math;
		cout << "Основы программирования: " << endl;
		cin >> A.proga;
		cout << "Ваше имя: " << A.name << endl;
		f_REQ.open(nameR, ios::app | ios::binary);
		//открытие файла REQUEST 
		f_REQ.write((char*)&A, sizeof(A));
		//запись запроса в файл REQUEST
		f_REQ.close();
		// поступил ответ от сервера?
		f_ANS.open(nameA + ".bin", ios::binary);
		//открытие файла ANSWER
		f_ANS.seekg(0, ios::end);
		//переход в конец файла ANSWER
		pred_size = f_ANS.tellg();
		while (pred_size >= f_ANS.tellg())
		{
			Sleep(100);
			// ждем и переходим в конец файла ANSWER
			f_ANS.seekg(0, ios::end);
		}
		// получение ответа от сервера	
		f_ANS.seekg(pred_size, ios::beg);
		// на начало нового ответа
		f_ANS.read((char*)&answer, sizeof(answer)); //считывание ответа
		f_ANS.close();


		// расшифровка ответа
		switch (answer) {
		case 2: {cout << "У вас отсутвует стипендия." << endl; break; }
		case 3: {cout << "У вас есть стипендия (5000 р.)." << endl; break; }
		case 4: {cout << "Поздравляем, у вас повышенная стипендия (10000 р.)." << endl; break; }
		case -1: {cout << "У вас задолженость по одному предмету." << endl; break; }
		case -2: {cout << "У вас задолженость по двум предметам." << endl; break; }
		case -3: {cout << "У вас задолженость по трём предметам." << endl; break; }
		case -4: {cout << "У вас задолженость по четырём предметам." << endl; break; }

		}
	}
}