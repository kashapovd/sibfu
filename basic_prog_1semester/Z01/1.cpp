#include <iostream>
using namespace std;

int main()
{
    int a;
    int b;

    cout << "a равно ";
    cin >> a;
    cout << "b = ";
    cin >> b;

    a = a - b;
    b = b + a;
    a = b - a;

    cout << "a = " << a << "; b = " << b << "\n";
}
