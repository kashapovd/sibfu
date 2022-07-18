//Кашапов Ярослав, 12 вариант, 80%

#include <iostream>
using namespace std;

int main() {
    int n;
    double S;

    cout << "n = ";
    cin >> n;
    S = 0;
    for(int i = 1, j = 1; i <= n; i++, j+=2) {
        S+= static_cast<double>(j) / i;
    }
    cout << "Сумма ряда: " << S << endl;
}
