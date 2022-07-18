#include <iostream>
#include <string.h>
using namespace std;

#define MAX_SIZE_STR 100
#define MAX_SIZE_SEP 10

char **make_charr(char **s_in, int n_str) {
    char str[MAX_SIZE_STR];
    for(int i = 0; i < n_str; i++) {
        cout << "Введите " << i << " строку: ";
        cin >> str;
        s_in[i] = new char[strlen(str)];
        strcpy(s_in[i], str);
    }
    return s_in;
}

size_t join(char *s_out, size_t len, const char *const *s_in, size_t n_in, const char *sep) {
    for(size_t i=0; i<n_in; i++) {
        strcat(s_out, s_in[i]);
        if(i == n_in - 1)
            continue;
        strcat(s_out, sep);
    }
    if(strlen(s_out) > len) {
        s_out[len] = '\0';
    }
    cout << "выходной массив: { " << s_out << " }\n";
    return strlen(s_out);
}

int main() {
    char **s_in, *s_out, separator[MAX_SIZE_SEP];
    int len, n_in, n_str;
    size_t len_out;
    
    s_out = new char[MAX_SIZE_STR];
    s_in = new char*[n_str];
    
    cout << "Введите разделитель: ";
    cin.getline(separator, MAX_SIZE_SEP);

    cout << "Введите количество строк в исходном массиве: ";
    cin >> n_str;
    
    s_in = make_charr(s_in, n_str);

    cout << "Введите количество строк в выходном массиве: ";
    cin >> n_in;

    cout << "Введите len: ";
    cin >> len;

    len_out = join(s_out, len, s_in, n_in, separator);
    cout << "Длина строки: " << len_out << endl;
    
    return 0;
}
