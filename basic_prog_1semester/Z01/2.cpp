#include <iostream>
#include <math.h>
using namespace std;


int main()
{
    int num_seats = 25;
    int num_buses;
    int num_free_seats;
    int num_people;

    cout << "num_people = ";
    cin >> num_people;

    num_buses = ceil( float(num_people) / num_seats );
    num_free_seats = num_buses * num_seats - num_people;

    cout << "numer of buses = " << num_buses << "\nnumber of free seats = "
              << num_free_seats << "\n";
    return 0;
}
