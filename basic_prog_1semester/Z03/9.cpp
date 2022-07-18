/*
 * 9. Даны действительные числа a, b, c. Если a больше 0,5, вывести большее из чисел b, c.
 * Иначе вывести меньшее из чисел b, c. Вычисление оформить как функцию float min_or_max(float a, float b, float c).
 */

#include <iostream>
using namespace std;

int main() {
    float a, b, c;
    float min_or_max(float a, float b, float c);

    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;

    cout << min_or_max(a, b, c) << endl;
}

float min_or_max(float x, float y, float z) {
    if ( x > 0.5 ) {
        return max(y, z);
    }
    else return min(y, z);
}
