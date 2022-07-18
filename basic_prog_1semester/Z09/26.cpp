#include <iostream>
#include <cmath>
using namespace std;

void print_arr(int *arr, int len) { // функция вывода массива
    cout << "arr = { ";
    for(int k=0; k<len; k++) {
        cout << arr[k] << " ";
    }
    cout << "}\n";
}

void fill_arr(int *arr, int len) { // функция заполнения массива arr
    srand(time(0)); // инициализация датчика случайных чисел таймером
    for(int i=0; i<len; i++) {
        arr[i] = rand()%10 * pow(-1, rand()%10); // заполнение массива
    }
    print_arr(arr, len);
}

bool comparison(int num1, int num2, bool even_greater) { // функция сравнения пары чисел
    if(num1 % 2 == 0 && abs(num2 % 2) == 1) { // абсолютное значение, потому что числа в массиве могут быть отрицательными
        return even_greater;
    }
    else if(abs(num1 % 2) == 1 && num2 % 2 == 0) {
        return !even_greater;
    }
    return num1 > num2;
}

void sort(int *arr, int len, bool even_greater) { // функция сортировки массива
    int tmp = 0;
    for(int i = 0; i < len-1; i++) {
        for(int j = 0; j < len-i-1; j++) {
            if(comparison(arr[j], arr[j + 1], even_greater)) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main() {
    int *arr, n;
    bool even_greater;

    cout << "n = ";
    cin >> n;
    cout << "even_greater(bool) = ";
    cin >> even_greater;

    arr = new int[n];

    cout << "исходный массив: ";
    fill_arr(arr, n);
    sort(arr, n, even_greater);
    cout << "итоговый массив: ";
    print_arr(arr, n);

    delete[] arr;
    arr = nullptr;
    return 0;
}
