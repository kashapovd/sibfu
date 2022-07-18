/*
 * Разработать, отладить, продемонстрировать и защитить преподавателю программу, которая для произвольного числа x, введенного
 * с клавиатуры, вычисляет значение y по следующей формуле:
 * y=f1(x)+f2(x), где f1(x) и f2(x) вычисляются по формулам из табл. 2 согласно вариантам.
 * Вычисление f1(x)f1(x) и f2(x) оформить как функции.
 * 12вар: f1 = 100/ (2x2+1); 	f2 = cbrt(50cosx^2)+2.13*105
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float f1(float x), f2(float x), y, x;

    cout << "x = ";
    cin >> x;

    y = f1(x) + f2(x);

    cout << "y = " << y << endl;
}

float f1(float x) {
    x = 100 / (2*x*x + 1);
    return x;
}

float f2(float x) {
    x = cbrt(50 * cos(x*x) + 2.13e5);
    return x;
}
