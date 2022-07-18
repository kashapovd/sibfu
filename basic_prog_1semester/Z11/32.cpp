#include <iostream>
using namespace std;

int **make2d(size_t nrows, size_t ncols) {
    int **arr;
    arr = new int*[nrows];
    for(size_t k=0; k<nrows; k++) {
        arr[k] = new int[ncols];
    }
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0; j<ncols; j++) {
            cout << "элемент " << i+1 << "," << j+1 << " = ";
            cin >> arr[i][j];
        }
    }
    return arr;
}

void print2d(int **arr, size_t nrows, size_t ncols) {
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0; j<ncols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void fliplr(int **arr, size_t nrows, size_t ncols) {
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0, k=ncols-1; j<ncols; j++, k--) {
            if(j>=k) break;
            swap(arr[i][j], arr[i][k]);
        }
    }

}

int main() {
    size_t nrows, ncols;
    int **arr;
    cout << "Введите nrows: ";
    cin >> nrows;
    cout << "Введите ncols: ";
    cin >> ncols;

    arr = make2d(nrows, ncols);
    cout << "исходный массив:\n\n";
    print2d(arr, nrows, ncols);
    fliplr(arr, nrows, ncols);
    cout << "итоговый массив:\n\n";
    print2d(arr, nrows, ncols);
    
    delete [] arr;
    arr = nullptr;
    return 0;
}
