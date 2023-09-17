#include<iostream>
#include<string>

using namespace std;

string s = "ldskjsdgdsgjsdlkgjsdkgjsdgkjsdglkjsdfhdsjfhsdkflhsdjghsdjgsldkghsdgjsdghsdjghsdklgjsdkjghsdkhsdjhsdkgjhsdlghsdkjfhdsfhsdghdsghsjdkghsdlkghsdkjghdsjghdsjghdshgsdjghsdghjksdhgdshfjkdshgjksdhgkjsdhgsdjkhgsdjg";
string arr[206];
int a = 0;

void ArrayString()
{
	for (int i = 0; i < 206; i++)
		arr[i] = "0";
}

bool SearchMiniString(string s1)
{
	for (int i = 0; i < 206; i++)
		if (arr[i] == s1)
			return true;
	return false;
}

string MiniString(int i)
{
	string s2 = "";
	for (int j = 0; j < 3; j++)
		s2 += s[i + j];
	return s2;
}

void KolMiniString()
{
	string s3;
	for (int i = 0; i < s.length() - 2; i++)
	{
		s3 = MiniString(i);
		if (SearchMiniString(s3) == true)
			continue;
		int kol = 1;
		for (int j = i + 1; j < s.length() - 2; j++)
		{
			string s4 = MiniString(j);
			if (s3 == s4)
			{
				kol++;
				arr[a] = s4;
				a++;
			}
		}
		if (kol > 1)
			cout << "Подстрока " << s3 << " встречается " << kol << " раз(а)." << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	cout << "Ваша строка: " << s << endl;
	ArrayString();
	KolMiniString();

	system("pause");
}