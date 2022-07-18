#include <iostream>
#include <cmath>
using namespace std;

void print_arr(float *arr, int len) { // функция вывода массива
    cout << " = { ";
    for(int k=0; k<len; k++) {
        cout << arr[k] << " ";
    }
    cout << "}\n";
}

void fill_arr(float *arr, int len) { // функция заполнения массива arr
    srand(time(0)); // инициализация датчика случайных чисел таймером
    for(int i=0; i<len; i++) {
        arr[i] = rand()%10 * pow((-1), rand()%10) + rand()%10*0.1; // заполнение массива
    }
    print_arr(arr, len);
}

void sort_arr(float arr[], int len, float x) {
    float tmp = 0;
    for(int i=0; i<len-1; i++) {
        for(int j=0; j<len-1; j++) {
            if(abs(arr[j] - x) > abs(arr[j+1] - x)) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main() {
    float *arr, *dist, x;
    int n;

    cout << "len = ";
    cin >> n;
    cout << "x = ";
    cin >> x;

    arr = new float[n];

    cout << "исходный массив: arr";
    fill_arr(arr, n); // заполнение массива

    sort_arr(arr, n, x); // сортировка массива

    cout << "итоговый массив: arr";
    print_arr(arr, n); // вывод массива

    dist = new float[n];
    cout << "массив модулей разности: dist";
    for(int i=0; i<n; i++) {
        dist[i] = abs(arr[i] - x);
    }
    print_arr(dist, n);

    delete[] arr;
    arr = nullptr;
    return 0;
}
