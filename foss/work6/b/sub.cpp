#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <fstream>
#include <algorithm>

#define STRLEN 100

struct ab {
    char a;
    char b;
} chars;

char str[STRLEN];

int main() {

    int strmsgid;
    int charsmsgid;
    std::cout << "Enter string message id: ";
    std::cin >> strmsgid;
    std::cout << "Enter chars message id: ";
    std::cin >> charsmsgid;

    int ret = msgrcv(strmsgid, &str, sizeof(char)*STRLEN, 0, 0);
    if (ret < 0) {
        std::cout << "Error reading string from queue" << std::endl;
        return -1;
    }

    ret = msgrcv(charsmsgid, &chars, sizeof(ab), 0, 0);
    if (ret < 0) {
        std::cout << "Error reading string from queue" << std::endl;
        return -1;
    }
    std::string stdstr(str);
    std::replace(stdstr.begin(),stdstr.end(),chars.a, chars.b);

    std::cout << "Result string: " << stdstr << std::endl;
    return 0;
}
