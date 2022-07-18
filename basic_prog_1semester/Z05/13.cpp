#include <iostream>
using namespace std;

int main() {
    int N;
    double ai(int i), S = 0;

    cout << "N = ";
    cin >> N;

    for(int i = 1; i <= N; i++) {
        S += ai(i);
    }

    cout << S << endl;
}

double ai(int i) {
    return static_cast<double>(i) / (i + 1);
}
