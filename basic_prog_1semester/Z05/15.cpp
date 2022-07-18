#include <iostream>
using namespace std;

int main() {
    int N, S = 0, si = -1;

    cout << "N = ";
    cin >> N;

    for(int i = 1; i <= N; i++) {
        S+=i*si;
        si*=-1;
    }
    cout << "S = " << S << endl;
}
