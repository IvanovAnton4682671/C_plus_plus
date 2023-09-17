//Случайное хэширование
#include<iostream>
#include<string>
#include<random>
#include<ctime>
#include<cstdlib>

using namespace std;

struct HashTable //Структура хэш-таблицы ***** Работает правильно *****
{
	int number[2000];
	string stroka[2000];
	int hashcode[2000];
};

int Hash(string& s) //Хэш-функция ***** Работает правильно *****
{
	int N = 2000, Hash = 0, k = 0;
	while (s[k] != '\0')
	{
		Hash += s[k];
		k++;
	}
	Hash %= N;
	int r = rand() % 2000 + 1;
	Hash += r % N;
	return Hash;
}

string RandomString(string& s) //Функция-генератор случайных строк ***** Работает правильно *****
{
	char Symb[93] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
					 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '~', '`', '!', '@',
					 '"', '#', '№', '$', ';', '%', '^', ':', '&', '?', '*', '(', ')', '-', '_', '+', '=', '|', '/', '{', '[', ']', '}', ',', '<', '.', '>' };
	int k = rand() % 16 + 5;
	for (int i = 0; i < k; i++)
	{
		int symb = rand() % 93;
		s += Symb[symb];
	}
	return s;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	HashTable Table;

	for (double a = 0.05; a <= 0.95; a += 0.05) //2000 = 1.00 --> 0.05 = (2000 / 100) * 5 = 100
	{
		int kolkolliz = 0;

		for (int k = 0; k < 1000; k++)
		{
			int i = a * 2000;

			for (int j = 1; j <= i; j++) //Заполняем таблицу на величину "а"
			{
				string s;
				Table.number[j] = j;
				Table.stroka[j] = RandomString(s);
				Table.hashcode[j] = Hash(s);
				//cout << Table.number[j] << " " << Table.stroka[j] << " " << Table.hashcode[j] << endl;
			}

			string obj;
			string obj1 = RandomString(obj);
			int obj2 = Hash(obj1);
			//cout << endl << "Новый объект: " << obj1 << " " << obj2 << endl << endl;

			for (int j = 1; j <= i; j++) //Проверяем новый obj на коллизии
				if (obj2 == Table.hashcode[j])
					kolkolliz++;
			if (kolkolliz > 0)
				obj2 += 10000;
			//cout << "Колличество коллизий: " << kolkolliz << endl;
			// << i + 1 << " " << obj1 << " " << obj2 << endl;

			//cout << endl << endl << endl;
		}
		cout << "Среднее колличество коллизий для заполненности таблицы " << a << " : " << kolkolliz / 100 << endl << endl; //проверить
	}

	return 0;
}