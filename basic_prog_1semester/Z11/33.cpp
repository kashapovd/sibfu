#include <iostream>
#include <algorithm>
using namespace std;

int **make2d(size_t size) {
    int **arr;
    arr = new int*[size];
    for(size_t k=0; k<size; k++) {
        arr[k] = new int[size];
    }
    for(size_t i=0; i<size; i++) {
        for(size_t j=0; j<size; j++) {
            cout << "элемент " << i+1 << "," << j+1 << " = ";
            cin >> arr[i][j];
        }
    }
    return arr;
}

void print2d(int **arr, size_t size) {
    for(size_t i=0; i<size; i++) {
        for(size_t j=0; j<size; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void transponse(int **arr, size_t size) {
    for(size_t i=0; i<size; i++) {
        for(size_t j=0; j<i; j++) {
            swap(arr[j][i], arr[i][j]);
        }
    }
}

int main() {
    size_t size;
    int **arr;

    cout << "Введите порядок матрицы: ";
    cin >> size;

    arr = make2d(size);
    cout << "исходный массив:\n\n";
    print2d(arr, size);
    transponse(arr, size);
    cout << "итоговый массив:\n\n";
    print2d(arr, size);
    
    delete [] arr;
    arr = nullptr;
    return 0;
}
