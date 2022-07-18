// Кашапов Ярослав, 12вар., 100%

#include <iostream>
#include <fstream>
using namespace std;

int **make2d(size_t size) {
    int **arr;
    arr = new int*[size];
    for(size_t i=0; i<size; i++) {
        arr[i] = new int[size];
        for(size_t j=0; j<size; j++) {
            // если выше главной диагонали:
            if(i<size-1 && j>i) {
                arr[i][j] = 0;
            }
            // если ниже главной диагонали:
            else if(i>0 && j<i){
                arr[i][j] = 2;
            }
            // если ни то, ни другое, т.е. сама главная диагональ
            else arr[i][j] = 1;
        }
    }
    return arr;
}

void print2d(int **arr, size_t n) {
    for(size_t i=0; i<n; i++) {
        for(size_t j=0; j<n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int **arr;
    size_t n;

    cout << "Введите размерность матрицы N x N; N = ";
    cin >> n;

    arr = make2d(n);
    cout << "итоговый массив:\n";
    print2d(arr, n);

    delete [] arr;
    arr = nullptr;
    return 0;
}
