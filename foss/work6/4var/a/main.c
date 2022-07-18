#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define PROCESS_NUM 2

int msgid;

char c;
struct cn {
    char c;
    uint n;
};

std::vector<cn> dict;

int sendMsg(std::string str, int i) {
    char c = str[i];
    int ret = msgsnd(msgid, &c, sizeof (char), IPC_NOWAIT);
    if (ret == -1)
        sendMsg(str, i);
    return ret;
}

void calcChars(std::string &str) {

    for(int i=0; i < str.size(); i++){
        if (fork() == 0) {
            exit(sendMsg(str, i));
        }
        wait(NULL);
    }

    for(int i=0; i < str.size(); i++){

        msgrcv(msgid, &c, sizeof (char), 0, 0);
        bool isFounded = false;
        for (int j=0; j < dict.size(); j++) {
            if (dict[j].c == c) {
                dict[j].n++;
                isFounded = true;
                break;
            }
        }
        if(!isFounded) {
            cn charn{c, 1};
            dict.push_back(charn);
        }
    }

}

int main()
{
    std::string str;
    std::cout << "Enter string: ";
    std::getline(std::cin, str);

    msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666) ;

    calcChars(str);
    fflush(stdout);
    for (const auto &it : dict) {
        std::cout << "\"" << it.c << "\"" <<": " << it.n << "\n";
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
