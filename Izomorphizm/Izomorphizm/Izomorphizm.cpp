#include <iostream>
#include <omp.h>
#include <ctime>


using namespace std;
bool f = true;

void creation1(int** g, int n) {//создание графа по матрице смежности, заполненой нулями и единицами
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g[i][j] = rand() % 2;
    }
}

/*void print(int** g, int n) {//вывод графа (матрицы смежности)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << g[i][j] << " ";
        cout << endl;
    }
}*/

void creation2(int** g1, int** g2, int n) {//создание второго, заведомо изоморфного графа
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g2[i][j] = g1[i][j];//сначала берём просто матрицу смежности первого, будем её менять
        int a; a = rand() % 2;
        int b; b = rand() % 2;
        //взяли два числа, которые будут номерами вершин
        while (a == b)
            b = rand() % n;//эти числа должны быть разными
        #pragma omp for
        for (int i = 0; i < n; i++) {//изменение двух элементов каждой строки по 1-ой матрице -> (изменённые) строки для 2-й матрицы
            g2[i][a] = g1[i][b];
            g2[i][b] = g1[i][a];
        }//здесь нет сортировки пузырьком, так как работаем с 2-мя разными матрицами
        int c;
        #pragma omp for
        for (int i = 0; i < n; i++) {//сортировка пузырьком, чтобы сделать обмен в одной и той же матрице, элементы разных строк сравниваются
            c = g2[a][i];
            g2[a][i] = g2[b][i];//идём по столбцам a и b, меняем элементы в строках
            g2[b][i] = c;
        }
    }
}

bool izomorfizm(int** g1, int** g2, int n) {
        int** g3 = new int* [n];
        for (int i = 0; i < n; i++) {
            g3[i] = new int[n];
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                //выше главной диагонали, чтобы не было одинаковых пар значений (пара: номер стр + номер ст-ца)
                //будут всевозможные замены
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < n; l++) {
                        g3[k][l] = g1[k][l];//пусть новый граф такой же, как и 1-ый
                    }
                }
                int a; a = i;
                int b; b = j;
                //запомнили номера, чтобы по ним переставлять элементы строк и столбцов
                for (int k = 0; k < n; k++) {//поменяли в строках
                    g3[k][a] = g1[k][b];
                    g3[k][b] = g1[k][a];
                }
                int c;
                for (int k = 0; k < n; k++) {//поменяли в столбцах
                    c = g3[a][k];
                    g3[a][k] = g3[b][k];
                    g3[b][k] = c;
                }
                for (int k = 0; k < n; k++)
                    for (int l = 0; l < n; l++)
                        if (g3[k][l] != g2[k][l]) {//если 2-й и 3-й графы точь в точь не совпадают, тогда 2-й не изоморфный 1-му (3-й граф представляет собой всевозможные графы, изоморфные 1-му)
                            f = false;
                        }
                if (f)
                    return true;//если графы 2 и 3 совпали, тогда 2-й изом. 1-му 
            }
        }
        return false;//если графы 2 и 3 не совпали, тогда 2-й не изом. 1-му
}


int main()
{
    double t1, t2;
    int  n;
    cin >> n;
    setlocale(LC_ALL, "rus");
    srand(time(0));
    int** g1 = new int* [n];
    for (int i = 0; i < n; i++)
        g1[i] = new int[n];
    t1 = omp_get_wtime();
    creation1(g1, n);
    int** g2 = new int* [n];
    for (int i = 0; i < n; i++)
        g2[i] = new int[n];
    creation2(g1, g2, n);
    bool d = izomorfizm(g1, g2, n);
    t2 = omp_get_wtime();
    if (d == true)
        cout << "Графы изоморфны" << endl;
    else
        cout << "Графы не изоморфны" << endl;
    cout << "Затрачено " << t2 - t1 << " сек" << endl;
    system("pause");
    return 0;
}