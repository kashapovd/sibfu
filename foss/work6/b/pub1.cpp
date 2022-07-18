#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <fstream>

#define STRLEN 100
char str[STRLEN];

int main() {
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666);

    if (msgid < 0) {
        std::cout << "Bad message queue allocation" << std::endl;
        return -1;
    }

    std::cout << "Enter string: ";
    std::cin >> str;

    auto ret = msgsnd(msgid, &str, sizeof (char)*STRLEN, IPC_NOWAIT);
    if (ret < 0) {
        std::cout << "Error sending string to queue" << std::endl;
    } else {
        std::cout << "String was sended! Don't forget message ID: " << msgid << std::endl;
    }
    return 0;
}
