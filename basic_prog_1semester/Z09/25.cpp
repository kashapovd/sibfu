#include <iostream>
#include <cmath>
using namespace std;

void print_arr(float *arr, int len) { // функция вывода массива
    cout << "arr = { ";
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

void sort_arr(float arr[], int len, bool asc) { // функция сортировки массива
    float tmp = 0;
    for(int i=0; i<len-1; i++) {
        for(int j = 0; j<len-1; j++) {
            if((asc && arr[j] > arr[j+1]) || (!asc && arr[j] < arr[j+1])) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main() {
    float *arr;
    int n;
    bool asc;

    cout << "len = ";
    cin >> n;
    cout << "Как сортировать массив?\n(1 - по возрастанию, 0 - по убыванию): ";
    cin >> asc;
    if(asc) cout << "Вы выбрали сортировку по возрастанию\n";
    else cout << "Вы выбрали сортировку по убыванию\n";

    arr = new float[n];

    cout << "исходный массив: ";
    fill_arr(arr, n); // заполнение массива
    sort_arr(arr, n, asc); // сортировка массива
    cout << "итоговый массив: ";
    print_arr(arr, n); // вывод массива

    delete[] arr;
    arr = nullptr;
    return 0;
}
