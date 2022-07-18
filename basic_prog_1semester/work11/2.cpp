// Кашапов Ярослав, 12вар., 100%

#include <iostream>
#include <string.h>
using namespace std;

#define MAX_SIZE_STR 100

void transform(char *str, size_t len) {
    // поиск повторяющихся элементов и их замена на что-либо отличное от буквы
    for(size_t i=0; i<len; i++) {
        for(size_t k=i+1; k<len; k++) {
            if(str[i] == str[k]) {
                str[k] = '0';
            }
        }
    }
    // удаление всего, что не буква
    int count_letter = 0;
    for(size_t i=0; i<len; i++) {
        if(isalpha(str[i])) {
            count_letter++;
            str[count_letter-1] = str[i];
        }
    }
    str[count_letter] = '\0';
}

int main() {
    char str[MAX_SIZE_STR];
    cout << "Введите строку: ";
    cin >> str;

    transform(str, strlen(str)+1);

    cout << str;
    return 0;
}
