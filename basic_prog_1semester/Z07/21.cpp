/*
 * Написать функцию int splice_array(int arr1[], int arr2[], int len, int arr_out[]),
 * которая соединяет массивы arr1[], arr2[] размера len путём чередования элементов (arr1[0], arr2[0], arr1[1], arr2[1], ...)
 * и помещает результат в arr_out[]. Функция должна возвращать размер получившегося массива.
*/

#include <iostream>
using namespace std;

void fill_arr(int arr1[], int arr2[], int len) { // функция заполнения массива
    srand(static_cast<unsigned int>((time(0)))); // инициализация датчика случайных чисел
    for(int i = 0; i < len; i++) {
        arr1[i] = 1; // элемент массива равен последней цифре случайного числа
        arr2[i] = 2; // элемент массива равен предпоследней цифре случайного числа
    }
}

int splice_array(int arr1[], int arr2[], int len, int arr_out[]) { // функция соединения массива
    for(int c = 0, j = 0; c < 2*len; c+=2, j++) {
        arr_out[c] = arr1[j];
        arr_out[c+1] = arr2[j];
    }
    return 2*len;
}

void shw_out(int arr_out[], int size) { // функция отображения массива
    cout << "arr_out[] = { ";
    for(int m = 0; m < size; m++) {
        cout << arr_out[m] << " ";
    }
    cout << "}\n";
}

int main() {
    int *arr1, *arr2, *arr_out, n, size_out;

    cout << "n = ";
    cin >> n;
    arr1 = new int[n]; // инициализация массива arr1
    arr2 = new int[n]; // инициализация массива arr2

    fill_arr(arr1, arr2, n); // вызов функции заполнения массивов arr1 и arr2

    arr_out = new int[n*2]; // инициализация массива arr_out

    size_out = splice_array(arr1, arr2, n, arr_out); // получение значения размера массива из функции
    shw_out(arr_out, size_out); // вызов функции вывода итогового массива

    cout << "размер массива arr_out = " << size_out << endl;
}
