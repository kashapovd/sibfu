//Кашапов Ярослав, 12 вариант, 100%

#include <iostream>
#include <cmath>
using namespace std;

double sum_series(double x, double e) {
    double current = 0, previos = 0, S, p;
    int j = 1, n = 1;
    S = M_PI/2;
    p = x;
    do {
        previos = current;
        current = p / j;
        //cout << "curr = " << current << "  prev = " << previos <<endl;
        n*=-1;
        p*=x*x;
        j+=2;
        S+=current*n;

    } while(abs(current - previos) > e);
    return S;
}

int main() {
    double x, e, S, arcctg;

    cout << "x = ";
    cin >> x;
    if(abs(x) >= 1) {
        cout << "error: |x| < 1\n";
        return 1;
    }
    cout << "точность вычислений = ";
    cin >> e;

    S = sum_series(x, e);
    arcctg = (M_PI/2) - atan(x);

    cout << "сумма_ряда(S): " << S << "\narcctg(x):" << arcctg << "\nS-arcctg(x): " << S-arcctg << endl;
}
