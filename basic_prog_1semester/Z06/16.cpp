/*
  Протабулировать функцию f(x)=2x^2−3x+1 на отрезке [a;b] с шагом s. Вычисление f(x) оформить как функцию double f(double x).
  Результат вывести в виде вертикальной таблицы из двух столбцов:
  - x, ширина поля — 10 символов, формат записи числа — фиксированный (ios_base::fixed).
  - f(x), ширина поля — 15 символов, формат записи числа — научный (ios_base::scientific).
  */
#include <iostream>
using namespace std;

int main() {
    double f(double q), a, b, s;

    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "s = ";
    cin >>  s;

    for(double  i = a; i <= b; i+=s) {
        cout.width(20);
        cout.setf(ios_base::fixed);
        cout << i << "  ";
        cout.unsetf(ios_base::fixed);
        cout.setf(ios_base::scientific);
        cout << f(i) << "\n";
        cout.unsetf(ios_base::scientific);
    }
}

double f(double x) {
    return 2 * x*x - 3 * x + 1;
}
