#include <iostream>
#include <fstream>
using namespace std;

#define FILE_PATH "/home/yaroslav/cpp_project/basic_prog/FILES/"
#define FILE_NAME_IN "for_Z13_1"
#define FILE_NAME_OUT "Z13_1"
#define SIZE_SEP 10

const string file_in = string(FILE_PATH) + string(FILE_NAME_IN);
const string file_out = string(FILE_PATH) + string(FILE_NAME_OUT);

void join(const char *sep, istream &ist, ostream &ost) {
    string word;
    bool insert = true;
    while(ist >> word) {
        if(insert) insert = false;
        else ost << sep;
        ost << word;
    }

}

int main() {
    ofstream ost;
    ifstream ist;
    char sep[SIZE_SEP];

    ost.open(file_out);
    ist.open(file_in);
    if(!ost.is_open() || !ist.is_open()) {
        cout << "Ошибка открытия/создания файлов";
        exit(0);
    }

    cout << "Введите разделитель: ";
    cin.getline(sep, SIZE_SEP);

    join(sep, ist, ost);
    return 0;
}
