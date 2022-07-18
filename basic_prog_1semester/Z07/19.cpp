/*
 * Написать функцию void print_array(int arr[], int len), которая выводит на экран первые len элементов массива arr.
*/

#include <iostream>
using namespace std;

void print_array(int arr[], int len) { // функция отображения len элементов массива
    cout << "Первые len элементов в массиве: ";
    for(int k = 0; k < len ; k++) {
        cout << arr[k] << " ";
    }
    cout << endl;
}

int main() {
    int *array, n; // для создания динамического массива переменная array должна быть указателем
    cout << "размер массива = ";
    cin >> n;
    array = new int[n]; // динамическое создание массива

    for(int i = 0; i < n; i++) { // заполнение массива
        //cout << i << " элемент массива :";
        //cin >> array[i];
        array[i] = i;
    }

    print_array(array, n); // вызов функции отображения массива
    return 0;
}


