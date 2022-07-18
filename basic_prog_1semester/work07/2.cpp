//Кашапов Ярослав, 12 вариант, 100%

#include <iostream>
#include <cmath>
using namespace std;

double fx(double x) {
    return x * sin(3 * x) - 1;
}

bool min_check(double k, double h) { // функция проверки на наличие локального минимума функции в точке i
    double min;
    min = fx(k);
    for(double i = k - h; i <= k + h; i+=2*h) {
        if(fx(i) < min) {
            min = fx(i);
        }
        cout << fx(i) << " ";
    }
    cout << "     ";
    if(min == fx(k)) {
        return true;
    }
    return false;
}

void tab_func(double a, double b, double h) { // функция табулирования
    for(double i = a; i <= b; i+=h) {
        if(min_check(i, h)) { // вызов функции, которая проверяет, является ли i точкой локального минимума
            cout << "* f(" << i << ") = " << fx(i) << endl; // если i - точка локального минимума, тогда вывести с "*"
        }
        else { // если i не точка локального минимума, то просто вывести результат табулирования
            cout << "  f(" << i << ") = " << fx(i) << endl;
        }
    }
}

int main() {
    double a, b, h;

    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "h = ";
    cin >> h;

    cout.setf(ios_base::fixed);
    tab_func(a, b, h); // вызов функции табулирования на отрезке [a; b] с шагом h
}
