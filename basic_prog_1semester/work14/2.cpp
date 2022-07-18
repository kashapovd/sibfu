// Кашапов Ярослав, 12вар., 100%

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#define MAX_SIZE 255

void last_dir(ostream &out, istream &in, string file_out) {
    char str[MAX_SIZE];
    while(in.getline(str, MAX_SIZE)) {
        int count_slash = 0;
        int len = static_cast<int>(strlen(str));
        for(int i = len; i >= 0; i--) {
            if(str[i] == '/') {
                count_slash++;
                if(i == 0 && count_slash == 1) {
                    out << '/' << "\n";
                    break;
                }
                if(count_slash == 2) {
                    for(int j = i+1; str[j] != '/'; j++) {
                        out << str[j];
                    }
                    out << "\n";
                    break;
                }
            }
        }
    }
    cout << "Запись в файл " << file_out << " завершена\n";
}

int main() {
    string file_out;
    string file_in;
    ofstream out;
    ifstream in;

    cout << "Введите абсолютный путь к исходному файлу: ";
    cin >> file_in;
    in.open(file_in);
    if(!in.is_open()) {
        cerr << "Ошибка открытия файла\n";
        exit(0);
    }
    cout << "Введите абсолютный путь к итоговому файлу: ";
    cin >> file_out;
    out.open(file_out);
    if(!out.is_open()) {
        cerr << "Ошибка создания/открытия файла";
        exit(0);
    }

    last_dir(out, in, file_out);
    return 0;
}
