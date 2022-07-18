#include <iostream>
using namespace std;

void fill_arr(int *arr, int len) { // функция заполнения массива
    srand(static_cast<unsigned int>((time(0)))); // инициализация датчика случайных чисел
    for(int i = 0; i < len; i++) { // заполнение массива случайными числами
        arr[i] = rand()%10;
    }
}

int count_equal(int *arr, int len, int x) { // функция поиска количества чисел, равных x
    int count = 0;
    for(int k = 0; k < len; k++) { // подсчёт количества чисел, равных х
        if(arr[k] == x) count++; // count - переменная-счётчик
    }
    return count;
}

void shw_out(int *arr, int len) { // функция отображения массива arr с количеством элементов, равных len
    cout << "arr[] = { ";
    for(int m = 0; m < len; m++) {
        cout << arr[m] << " ";
    }
    cout << "}";
    cout << endl;
}

int main() {
    int *arr, n, x; // для создания динамического массива переменная arr должна быть указателем

    cout << "n = ";
    cin >> n;
    arr = new int[n]; // динамическое создание массива
    fill_arr(arr, n); // вызов функции заполенения массива

    cout << "x = ";
    cin >> x;

    shw_out(arr, n); // вызов функции отображения массива
    cout << "count(x) = " << count_equal(arr, n, x) << endl; // вывод количество чисел массива, равных х
    return 0;
}
