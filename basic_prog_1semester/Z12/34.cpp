#include <iostream>
#include <fstream>
using namespace std;

#define FILE_PATH "/home/yaroslav/cpp_project/basic_prog/FILES/"
#define FILE_NAME "z12_1.txt"

int **make2d(size_t nrows, size_t ncols) {
    srand(time(NULL));
    int **arr;
    arr = new int*[nrows];
    for(size_t i=0; i<nrows; i++) {
        arr[i] = new int[ncols];
        for(size_t j=0; j<ncols; j++) {
            arr[i][j] = rand()%10;
        }
    }
    return arr;
}

void print2d(const int *const *arr, size_t nrows, size_t ncols, ofstream &ost, string file) {
    for(size_t i=0; i<nrows; i++) {
        for(size_t j=0; j<ncols; j++) {
            ost << arr[i][j] << " ";
        }
        ost << "\n";
    }
    cout << "\nЗапись в файл " << file << " завершена\n\n";
}

int main() {
    size_t ncols, nrows;
    int **arr;
    ofstream ost;
    string file = string(FILE_PATH) + string(FILE_NAME);
    ost.open(file);
    if(!ost.is_open()) {
        cerr << "Ошибка открытия файла\n";
        exit(0);
    }

    cout << "nrows = ";
    cin >> nrows;
    cout << "ncols = ";
    cin >> ncols;

    arr = make2d(nrows, ncols);
    print2d(arr, nrows, ncols, ost, file);
    ost.close();
    
    delete [] arr;
    arr = nullptr;
    return 0;
}
