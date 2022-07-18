#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float x;
    int decimal;
    cout << "x = ";
    cin >> x;

    x = abs(x);
    x = x - (int)x;
    x = int(x * 10 + 0.04);
    decimal = x;

    cout << "decimal = " << x << "\n";
}
