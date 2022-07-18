#include <iostream>
#include <fstream>
using namespace std;

#define FILE_PATH "/home/yaroslav/cpp_project/basic_prog/FILES/"
#define FILE_NAME_IN "for_Z13_3"
#define FILE_NAME_OUT "Z13_3"
const string file_in = string(FILE_PATH) + string(FILE_NAME_IN);
const string file_out = string(FILE_PATH) + string(FILE_NAME_OUT);

void wrap_text(istream &ist, ostream &ost, int max_line_len) {
    char c;
    int count_c = 0;
    while(ist.get(c)) {
        if(count_c == max_line_len || c == '\n') {
            if(c != '\n') {
                ost << "\n";
            }
            count_c = 0;
        }
        ost << c;
        count_c++;
    }
    cout << "Запись в файл " << file_name << " завершена\n";
}

int main() {
    int len;
    ofstream out;
    ifstream in;

    in.open(file_in);
    out.open(file_out);
    if(!in.is_open() || !out.is_open()) {
        cout << "Ошибка создания/открытия файла";
        exit(0);
    }

    cout << "Максимальная длина строки: ";
    cin >> len;

    wrap_text(in, out, len);
    return 0;
}
