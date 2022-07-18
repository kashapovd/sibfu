/*
  Протабулировать функцию f(x)=5x+2 на отрезке [a;b] с шагом s. Вычисление f(x) оформить как функцию double f(double x).
  Результат вывести в виде горизонтальной таблицы из двух строк:
  - x, ширина поля — 15 символов, точность (precision) — 3 знака, формат записи числа — фиксированный (ios_base::fixed).
  - f(x), ширина поля — 15 символов, точность — 5 знаков, формат записи числа — научный (ios_base::scientific).
  */
#include <iostream>
using namespace std;

int main() {
    double f(double f), a, b, s;

    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "s = ";
    cin >>  s;

    for(double i = a; i <= b; i+=s) {
        cout.width(15);
        cout.precision(3);
        cout.setf(ios_base::fixed);
        cout << i << " ";
    }
    cout.unsetf(ios_base::fixed);
    cout << "\n";
    for(double j = a; j <= b; j+=s) {
        cout.width(15);
        cout.precision(5);
        cout.setf(ios_base::scientific);
        cout << f(j);
    }
    cout << endl;
}

double f(double x) {
    return 5 * x + 2;
}
