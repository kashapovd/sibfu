// Кашапов Ярослав, 12 вариант, 100%

#include <iostream>
#include <algorithm>
#include <string>

#define _swap(a,b) a = a ^ b ^ (b = a)

void printPermutation(std::string);
std::string nextPremuatation(std::string, int i, int n);
int permNum(std::string);
int factor(int);
char genRandChar();

int main() {

//    int n;
//    std::cout << "Число символов в строке[n]: ";
//    std::cin >> n;

    //srand(time(0));
    std::string input_str = "123";
//    std::string input_str = "";
//    for (int c =0; c < n; c++) {
//        input_str.push_back(genRandChar());
//    }
//    std::cout << "Сгенерированная строка: " << input_str << std::endl;
    std::sort(input_str.begin(), input_str.end());
    std::cout << "Сортированная строка: " << input_str << std::endl;
    std::cout << "Всего перестановок: " << factor(input_str.length()) << "\n\n";
    printPermutation(input_str);
}



void printPermutation(std::string print_str) {
//    if (print_str == "") { // базовый случай рекурсии
//        std::cout << "конец." <<std::endl;
//        return;
//    }
    //std::cout << "[" << permNum(print_str) << "] " << print_str << "\n";
    //printPermutation(nextPremuatation(print_str));
    nextPremuatation(print_str, 0, print_str.length()-1);
}

std::string nextPremuatation(std::string str, int i, int n) { // поиск перестановок с возвратом

//    int maxP = str.length()-1;
//    while(str.at(maxP-1) >= str.at(maxP)) {
//        maxP--;
//        if (maxP == 0)
//            return ""; // последняя перестановкаs
//    }

//    int minE = str.length()-1;
//    while (str.at(minE) <= str.at(maxP-1)) {
//        minE--;
//    }

//    _swap(str.at(maxP-1), str.at(minE));
//    std::sort(str.begin()+maxP, str.end());
//    minE = str.length() - 1;
//    while (maxP < ) {

//    }

    int j;
    if (i == n) // базовый случай
        std::cout<< "[" << permNum(str) << "] " <<str<<std::endl;
    else {
        for (j = i; j <= n; j++)
        {
            _swap(str.at(i), str.at(j));
            nextPremuatation(str, i + 1, n);
            _swap(str.at(i), str.at(j));
       }
   }

    return str;
}

int permNum(std::string p) {
    int result = 0;
    for (int i = 0; i < (int)p.length(); i++) {
        int g = 0;
        for (int j = i+1; j < (int)p.length(); j++) {
            if (p.at(i) >= p.at(j))
                g++;
        }
        result+=g*(factor(p.length()-1-i));
    }
    return result;
}

int factor(int n) {
    int i = 1;
    for(int j = 1;j <= n; j++) {
        i=j*i;
    }
    return i;
}

char genRandChar() {
    char ch;
    if (rand() % 2)
        ch = static_cast<char>('A' + rand()%24);
    else
        ch = static_cast<char>('a' + rand()%24);
    return ch;
}
