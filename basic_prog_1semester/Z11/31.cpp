#include <iostream>
using namespace std;

int **make2d(size_t nrows, size_t ncols, int val) {
    int **arr;
    arr = new int*[nrows];
    for(size_t k=0; k<nrows; k++) {
        arr[k] = new int[ncols];
    }
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0; j<ncols; j++) {
            arr[i][j] = val;
        }
    }
    return arr;
}

void print_arr(int **arr, size_t nrows, size_t ncols) {
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0; j<ncols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    size_t nrows, ncols;
    int val, **arr;

    cout << "number of rows = ";
    cin >> nrows;
    cout << "number of column = ";
    cin >> ncols;
    cout << "val = ";
    cin >> val;

    arr = make2d(nrows, ncols, val);
    print_arr(arr, nrows, ncols);
    
    delete [] arr;
    arr = nullptr;
    return 0;
}
