/*
 * 8. Определить расстояние d между двумя точками на числовой плоскости с координатами (x1, y1), (x2, y2).
 * Вычисление расстояния оформить как функцию float dist(float x1, float y1, float x2, float y2).
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float x1, x2, y1, y2;
    float dist(float x1, float x2, float y1, float y2);

    cout << "x1 = ";
    cin >> x1;
    cout << "y1 = ";
    cin >> y1;
    cout << "x2 = ";
    cin >> x2;
    cout << "y2 = ";
    cin >> y2;

    cout.precision(3);
    cout << "Расстояние между точками = " << dist(x1, x2, y1, y2) << endl;
}

float dist(float x1, float x2, float y1, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
