/*
 * 11. Дано целое число s. Вывести диагональную линию из символов «*» из левого верхнего угла в области из s строк и s столбцов.
 * Вывод линии оформить как функцию void print_diag(int s).
 */

#include <iostream>
using namespace std;

int main() {
    int s;
    void print_diag(int n);

    cout << "s = ";
    cin >> s;

    print_diag(s);
}

void print_diag(int s) {
    for(int i = 1; i <= s; i++) {
        cout.width(1+i);
        cout << "*\n";
    }
}

