#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef double db;
typedef long long ll;
// Вывод системы уравнений
vector<vector<db>> a;
vector<db> y, x;
bool gauss(ll n)
{
    db max;
    ll k, index;
    const db eps = 0.0000001;
    //x = new double[n];
    k = 0;
    while (k < n)
    {
        // Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (ll i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        if (max < eps)
        {
            // нет ненулевых диагональных элементов
            cout << "Решение получить невозможно из-за нулевого столбца ";
            cout << index << " матрицы A" << endl;
            return 0;
        }
        for (ll j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        for (ll i = k; i < n; i++)   // Нормализуем
        {
            double temp = a[i][k];
            if (abs(temp) < eps) 
                continue; 
            for (int j = k; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  
                continue; 
            for (ll j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    for (k = n - 1; k >= 0; k--) //обратный ходд
    {
        x[k] = y[k];
        for(ll i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return 1;
}
int main()
{

    setlocale(LC_ALL, "Russian");
    ifstream in; in.open("in.txt");
    ll n;
    in >> n;
    a = vector<vector<db>>(n, vector<db>(n));
    y = vector<db>(n);
    x = vector<db>(n);
    
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < n; j++)
            in >> a[i][j];
    for (ll i = 0; i < n; i++)
        in >> y[i];
    if(gauss(n))
        for (ll i = 0; i < n; i++)

            cout << "x" << i << "=" << x[i] << endl;
    return 0;
}