#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

int kol = 0;

string KNF(int &n, string &s)
{
	int i_1 = rand() % n + 1; //кол-во скобок
	for (int i = 1; i <= i_1; i++)
	{
		s += "(";
		int j_1 = rand() % n + 1; //кол-во переменных в скобке
		for (int j = 1; j <= j_1; j++)
		{
			int symbol_o = rand() % 2;
			if (symbol_o == 1) s += "~";
			s += "x";
			int nomer = rand() % n + 1;
			s += to_string(nomer);
			s += "|";
		}
		s.pop_back();
		s += ")&";
	}
	s.pop_back();
	return s;
}

string getP(string s, int& i) {
	string str = "";
	while (i < s.length()) {
		if (s[i] == '(' || s[i] == ')' || s[i] == '|' || s[i] == '&') {
			break;
		}
		str += s[i];
		i++;
	}
	return str;
}

int getJ(string s, int i) {
	for (; i < s.length(); i++) {
		if (s[i] == ')') {
			return i;
		}
	}
	return i;
}

void f(string s) {
	int n = s.length();
	int i = 0;
	while (i < n) {
		if (s[i] != '(' && s[i] != ')' && s[i] != '|' && s[i] != '&') {
			string p1 = getP(s, i);
			int j = getJ(s, i);
			while (j < n) {
				if (s[j] != '(' && s[j] != ')' && s[j] != '|' && s[j] != '&') {
					string p2 = getP(s, j);
					cout << p1 << " " << p2 << endl;
				}
				j++;
			}
			cout << endl;
		}
		i++;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	for (int i = 5; i <= 50; i += 5)
	{
		int n = i;
		string s;
		KNF(n, s);
		cout << "Ваша случайная строка КНФ: " << s << endl;
		f(s);
		cout << endl << endl;
	}

	system("pause");
}