/*
 * 4. Для заданного натурального числа N вывести в столбик все простые числа меньшие N.
 * Простое число – это натуральное число, имеющее ровно два различных натуральных делителя,
 * то есть простое число делится нацело только на самого себя и единицу. Является ли число простым оформить как функцию
 */

#include <iostream>
using namespace std;

int main() {
    int N, simple_test(int i);

    cout << "N = ";
    cin >> N;

    int i = 2;
    cout << "Простые числа, меньшие " << N << ": ";
    while(i < N) {
        if(simple_test(i)) {
            cout << i << " ";
        }
        i++;
    }
    cout << "\n";

}
int simple_test(int i) {
    for (int j = 2; j * j <= i; j++) {
        if (i % j == 0) {
            return false;
        }
    }
    return true;
}
