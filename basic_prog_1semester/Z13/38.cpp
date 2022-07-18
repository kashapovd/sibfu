#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#define FILE_PATH "/home/yaroslav/cpp_project/basic_prog/FILES/"
#define FILE_NAME_IN "for_Z13_2"
#define FILE_NAME_OUT "Z13_2"

#define MAX_LINES 10
#define MAX_SYMB_STR 100

const string file_in = string(FILE_PATH) + string(FILE_NAME_IN);
const string file_out = string(FILE_PATH) + string(FILE_NAME_OUT);

void rev_lines(istream &ist, ostream &ost) {
    int n_lines = 0;
    char lines[MAX_LINES][MAX_SYMB_STR];

    while(ist.getline(lines[n_lines], MAX_SYMB_STR)) {
        n_lines++;
    }
    for(int i = n_lines-1; i>=0; i--) {
        strcat(lines[i], "\n");
        ost << lines[i];
    }
    cout << "Запись в файл завершена\n";
}

int main() {
    ofstream ost;
    ifstream ist;

    ost.open(file_out);
    ist.open(file_in);
    if(!ost.is_open() || !ist.is_open()) {
        cout << "Ошибка открытия/создания файлов";
        exit(0);
    }

    rev_lines(ist, ost);
    ost.close();
    ist.close();
    return 0;
}
