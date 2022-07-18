#include <iostream>
#include <fstream>
using namespace std;

#define FILE_PATH "/home/yaroslav/cpp_project/basic_prog/FILES/"
#define FILE_NAME "z12_2.txt"

int **make2d(size_t nrows, size_t ncols) {
    int **arr;
    arr = new int*[nrows];
    for(size_t i=0; i<nrows; i++) {
        arr[i] = new int[ncols];
        for(size_t j=0; j<ncols; j++) {
            cout << "элемент " << i+1 << "," << j+1 << " = ";
            cin >> arr[i][j];
        }
    }
    return arr;
}

void fliplr(int **arr, size_t nrows, size_t ncols) {
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0, k=ncols-1; j<ncols; j++, k--) {
            if(j>=k) break;
            swap(arr[i][j], arr[i][k]);
        }
    }
}

void print_fliplr(const int *const *arr, size_t nrows, size_t ncols, ostream &ost, string file) {
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0; j<ncols; j++) {
            ost << arr[i][j] << " ";
        }
        ost << "\n";
    }
    cout << "\nЗапись в файл " << file << " завершена\n\n";
}

int main() {
    int **arr;
    size_t nrows, ncols;
    ofstream ost;
    string file = string(FILE_PATH) + string(FILE_NAME);

    ost.open(file);
    if(!ost.is_open()) {
        cerr << "Ошибка чтения файла\n";
        exit(0);
    }

    cout << "Введите nrows: ";
    cin >> nrows;
    cout << "Введите ncols: ";
    cin >> ncols;

    arr = make2d(nrows, ncols);
    fliplr(arr, nrows, ncols);
    print_fliplr(arr, nrows, ncols, ost, file);
    ost.close();
    
    delete [] arr; 
    arr = nullptr;
    return 0;
}
