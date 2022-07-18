#include <iostream>
#include <string.h>
using namespace std;

#define SIZE_STR 100
#define SIZE_DEL 10

void rstrip(char *s, const char *chars) {
    int str_len = int(strlen(s));
    int chars_len = int(strlen(chars));
    int j = str_len;

    for(int i=0; i<str_len; i++) {
        for(int k=0; k<chars_len; k++){
            int current_len = j;
            while(s[j-1] == chars[k]) {
                j--;
            }
            if(j < current_len) {
                s[j] = '\0';
            }
        }
    }

    for(int i=0; i<str_len; i++) {
        for(int k=0; k<chars_len; k++) {
            int m = 0;
            while(s[0+m] == chars[k]) {
                m++;
            }
            if(m != 0){
                for(int i = 0; i< str_len; i++) {
                    s[i]=s[i+m];
            }
            s[j-m] = '\0';
            }
        }
    }
}

int main() {
    char s[SIZE_STR], del[SIZE_DEL];

    cout << "Введите что-нибудь: ";
    cin.getline(s, SIZE_STR);
    cout << "Какие символы удалить?: ";
    cin.getline(del, SIZE_DEL);

    rstrip(s, del);

    cout << "итоговая строка: " << s << "\n";
}
