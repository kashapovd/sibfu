#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <fstream>

struct ab {
    char a;
    char b;
} chars;

int main() {
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666);

    if (msgid < 0) {
        std::cout << "Bad message queue allocation" << std::endl;
        return -1;
    }

    std::cout << "Enter a: ";
    std::cin >> chars.a;
    std::cout << "Enter b: ";
    std::cin >> chars.b;

    auto ret = msgsnd(msgid, &chars, sizeof (ab), IPC_NOWAIT);
    if (ret < 0) {
        std::cout << "Error sending symbols to queue" << std::endl;
        return -1;
    } else {
        std::cout << "Symbols to substitute was sended! Don't forget message ID: " << msgid << std::endl;
    }
    return 0;
}
