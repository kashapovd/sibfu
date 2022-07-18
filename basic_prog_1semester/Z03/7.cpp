/*
 * 7. Даны числа a, b, c, d, которые могут быть равны 0 или 1. Определить, какое число встречается чаще.
 * Алгоритм определения оформить как функцию int find_most_frequent(int a, int b, int c, int d).
 * Функция должна возвращать: 0, если 0 встречается чаще; 1, если 1 встречается чаще; -1, если 0 и 1 встречаются
 * одинаково часто.
 */

#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    int find_most_frequent(int a, int b, int c, int d);

    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    cout << "d = ";
    cin >> d;

    if (a < 0 || a > 1  || b < 0 || b > 1 || c < 0 || c > 1 || d < 0 || d > 1) {
        cout << "Введены некорректные данные" << endl;
        return 1;
    }

    cout << find_most_frequent(a, b, c, d) << endl;
    return 0;
}


int find_most_frequent(int a, int b, int c, int d) {
    int count1;
    count1 = a + b + c + d;
    if (count1 < 2) {
        return 0;
    }
    else if (count1 > 2) {
        return 1;
    }
    else return -1;
}
