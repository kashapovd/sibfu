#include <iostream>
using namespace std;

int main() {
    int N;
    double x, P = 1, power = 1;

    cout << "N = ";
    cin >> N;
    cout << "x = ";
    cin >> x;

    for(int i = 1; i <= N; i++) {
        power *= x;
        P *= (2 * power);
    }
    cout << "P = " << P << endl;
}
