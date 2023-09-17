//Для работы стэка нужны 4 операции: инициализировать стэк, добавить элемент в стэк, извлечь элемент из стэка, булевская операция "стэк не пуст" (проверка на пустоту).

struct stack
{
	int *s;
	int top;
};

void init(stack &st)
{
	st.s = new int[100];
	st.top = -1;
}

void push(stack &st, int x)
{
	if (st.top < 99)
	{
		st.top++;
		st.s[st.top] = x;
	}
	else
		cout << "Стэк переполнен." << endl;
}

int pop(stack &st)
{
	int x = -9999;
	if (st.top > -1)
	{
		x = st.s[st.top];
		st.top--;
	}
	else
		cout << "Стэк пуст." << endl;
	return x;
}

bool notempty(stack &st)
{
	return st.top > -1;
}