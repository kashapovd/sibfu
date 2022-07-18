// Кашапов Ярослав, 12вар., 100%

#include <iostream>
#include <fstream>
using namespace std;

#define FILE_PATH "urpath"
#define FILE_NAME "work13.txt"
string const file = string(FILE_PATH) + string(FILE_NAME);

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

void fwrite(int *const *arr, size_t size, ostream &fout, string file) {
    for(size_t i=0; i<size; i++) {
        for(size_t j=0; j<size; j++) {
            fout << arr[i][j] << " ";
        }
        fout << "\n";
    }
    cout << "\nЗапись в файл " << file << " завершена\n\n";
}

void fread(string file_name) {
    ifstream fin;
    string line;
    fin.open(file_name);
    if(!fin.is_open()) {
        cerr << "Ошибка открытия файла\n";
        exit(0);
    }
    cout << "Содержимое файла:\n";
    while(getline(fin, line)) {
        cout << line << "\n";
    }
    fin.close();
    cout << "\nЧтение из файла завершено\n";
}

int main() {
    int **arr;
    size_t n;
    ofstream fout;

    cout << "Введите размерность матрицы N x N; N = ";
    cin >> n;

    arr = make2d(n);
    fout.open(file);
    if(!fout.is_open()) {
        cerr <<  "Ошибка открытия файла\n";
        exit(0);
    }
    fwrite(arr, n, fout, file);
    fout.close();
    fread(file);

    delete [] arr;
    arr = nullptr;
    return 0;
}
