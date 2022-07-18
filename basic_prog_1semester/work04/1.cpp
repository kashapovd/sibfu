/*
 * Разработать, отладить, продемонстрировать и защитить преподавателю программу, которая для произвольного числа x, введенного
 * с клавиатуры , вычисляет значение y по следующей формуле:
 * y={f1(x), если x≥0
 *   {f1(x)+f2(x), если x<0, где f1(x) и f2(x) вычисляются по формулам из табл. 1
 * согласно вариантам. Вычисление f1(x) и f2(x) оформить как функции.
 * 12вар: f1 = 90cosx; f2 = 2x+12.3*10^4
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float f1(float x), f2(float x2), x, y;

    cout << "x = ";
    cin >> x;

    if (x < 0) {
        y = f1(x) + f2(x);
    }
    else y = f1(x);

    cout << "y = " << y << endl;
}

float f1(float x) {
    x = 90 * cos(x);
    return x;
}

float f2(float x) {
    x = 2 * x + 12.3e4;
    return x;
}
