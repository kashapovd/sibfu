#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double f(double x), a, b, s;
    int scale, u = 0;

    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "s = ";
    cin >>  s;
    cout << "scale = ";
    cin >> scale;

    int c = 0;
    for(double i = a; i <= b; i+=s){
        for (int v = 0; v <= scale * f(i); v++) {
            cout.width(2+v);
            c++;
        }
        cout << "$(" << a+s*u << ", " << f(i) << ", " << c << ")" << "\n";
        u++;
    }
    //cout << "c = " << c << endl;
}

double f(double x) {
    static const double pi = acos(-1);
    return sin(pi * x) * sin (pi * x);
}
