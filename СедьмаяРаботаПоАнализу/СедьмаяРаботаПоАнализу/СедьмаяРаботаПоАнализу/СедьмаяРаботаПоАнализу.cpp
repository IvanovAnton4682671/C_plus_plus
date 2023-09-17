/*#include<iostream>
#include<string>
#include<algorithm>
#include<random>
#include<ctime>
#include<cstdlib>

using namespace std;

char plys = '+', minys = '-', star = '*', slash = '/', lpar = '(', rpar = ')', symbol;
unsigned marker = 0;
string Source;
char stack[20]; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
unsigned sp = 0; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void NextSym()
{
	symbol = Source[marker];
	cout << symbol << endl;
	if (Source.size() > marker)
	{
		marker++;
		cout << symbol << endl;
	}
}

void Accept(char symbolexpected)
{
	if (symbol == symbolexpected)
	{
		NextSym();
		cout << symbol << endl;
	}
	else cout << "Ожидалось: " << symbolexpected << endl;
}

bool Letter()
{
	return (symbol >= 'a' && symbol <= 'z');
}

bool Digit()
{
	return (symbol >= '0' && symbol <= '9');
}

void Number()
{
	while (Digit())
	{
		NextSym();
		cout << symbol << endl;
	}
}

void Factor() //Функция "множитель"
{
	if (Letter())
	{
		NextSym();
		cout << symbol << endl;
	}
	else
		if (Digit())
		{
			Number();
			cout << symbol << endl;
		}
		else
			if (symbol == lpar)
			{
				NextSym();
				//Expression();
				Accept(rpar);
				cout << symbol << endl;
			}
}

void AddEnd() //Функция "слагаемое"
{
	if (Letter() || Digit() || (symbol == lpar))
	{
		Factor();
		cout << symbol << endl;
		while (symbol == star || symbol == slash)
		{
			NextSym();
			Factor();
			cout << symbol << endl;
		}
		cout << symbol << endl;
	}
	cout << symbol << endl;
}

void Expression() //Функция "выражение"
{
	char symTOstack; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (Letter() || Digit() || (symbol == lpar))
	{
		AddEnd();
		while (symbol == plys || symbol == minys)
		{
			symTOstack = symbol; //!!!!!!!!!!!!!!!!!!!!!!!!
			NextSym();
			AddEnd();
			stack[sp] = symTOstack; //!!!!!!!!!!!!!!!!!!!!
			sp++; //!!!!!!!!!!!!!!!!!!!!!!!!
			cout << symbol << endl;
		}
		cout << symbol << endl;
	}
	cout << symbol << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	char a, b, c;
	cin >> a >> b >> c;
	Source = "a+b+c";
	Expression();

	system("pause");
}*/










/*#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Структура данных для хранения узла бинарного дерева
struct Node
{
	char data;
	Node* left, * right;

	Node(char data)
	{
		this->data = data;
		this->left = this->right = nullptr;
	};

	Node(char data, Node* left, Node* right)
	{
		this->data = data;
		this->left = left;
		this->right = right;
	};
};

// Функция для проверки, является ли данный токен оператором
bool isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Печатаем постфиксное выражение для дерева выражений
void postorder(Node* root)
{
	if (root == nullptr) {
		return;
	}

	postorder(root->left);
	postorder(root->right);
	cout << root->data;
}

// Печатаем инфиксное выражение для дерева выражений
void inorder(Node* root)
{
	if (root == nullptr) {
		return;
	}

	// если текущий токен является оператором, вывести открывающую скобку
	if (isOperator(root->data)) {
		cout << "(";
	}

	inorder(root->left);
	cout << root->data;
	inorder(root->right);

	// если текущий токен является оператором, вывести закрывающую скобку
	if (isOperator(root->data)) {
		cout << ")";
	}
}

// Функция для построения дерева выражений из заданного постфиксного выражения
Node* construct(string postfix)
{
	// базовый вариант
	if (postfix.length() == 0) {
		return nullptr;
	}

	// создаем пустой stack для хранения указателей дерева
	stack<Node*> s;

	// обход постфиксного выражения
	for (char c : postfix)
	{
		// если текущий токен является оператором
		if (isOperator(c))
		{
			// извлекаем из stack два узла `x` и `y`
			Node* x = s.top();
			s.pop();

			Node* y = s.top();
			s.pop();

			// построить новое бинарное дерево, корнем которого является оператор, а
			// левый и правый дочерние элементы указывают на `y` и `x` соответственно
			Node* node = new Node(c, y, x);

			// поместить текущий узел в stack
			s.push(node);
		}

		// если текущий токен является операндом, создаем новый узел бинарного дерева
		// чей корень является операндом и помещаем его в stack
		else {
			s.push(new Node(c));
		}
	}

	// указатель на корень дерева выражений остается в stack
	return s.top();
}

int main()
{
	string postfix = "ab+cde+**";
	Node* root = construct(postfix);

	cout << "Postfix Expression: ";
	postorder(root);

	cout << "\nInfix Expression: ";
	inorder(root);

	return 0;
}*/









#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int i = 0;
bool lpar = false;
string arr[50];
int IndArr = 0;

string Expression(string s)
{
	string n = "";
	for (; i < s.size(); i++)
	{
		if (s[i] == ')' || s[i] == ' ')
		{
			lpar = false;
			break;
		}
		if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && lpar == false)
		{
			arr[IndArr] = n;
			IndArr++;
			arr[IndArr] = s[i];
			IndArr++;
			n = "";
			continue;
		}
		if (s[i] == '(')
		{
			lpar = true;
			i++;
			n = Expression(s);
			arr[IndArr] = n;
			IndArr++;
			arr[IndArr] = s[i];
			n = "";
			continue;
		}
		n += s[i];
	}
	return n;
}

int main()
{
	setlocale(LC_ALL, "rus");
	string s1;
	cout << "Введите выражение: ";
	cin >> s1;
	arr[IndArr] = Expression(s1);
	IndArr++;
	cout << "Дерево разбора этого выражения: " << endl;
	for (int j = 0; j < IndArr; j++)
		cout << arr[j] << endl;
	system("pause");
}