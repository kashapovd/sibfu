#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <unistd.h>
#include <sys/sem.h>

#define STACK_SIZE (1024 * 1024)

struct strings {
    std::vector<std::string> s1;
    std::vector<std::string> s2;
} strs;

char c;
int semid;
sembuf spp = {0, 1, 0};
sembuf smm = {0, -1, 0};

class taskString
{
public:
    taskString(std::string &str, char &ch) {
        std::stringstream ss(str);
        std::string buf;
        while (ss >> buf) {
            words.push_back(buf);
        }
        std::cout << "Loaded " << words.size() << " words\n";
        c = ch;
        stacks = new char*[words.size()];
        pids = new int[words.size()];

        semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
        semop(semid, &spp, 1);
    };

    ~taskString() {
        semctl(semid, 1, IPC_RMID);
    }

    void print(std::ostream &ost) {
        for(const auto &it : words)
            ost << it << " ";
        ost << std::endl;
    }

    static int makeStrings(void *param) {
        auto word = *(std::string*)param;
        semop(semid, &smm, 1);
        {
            std::size_t found = word.find(c);
            if(found != std::string::npos) {
                strs.s1.push_back(word);
            } else {
                strs.s2.push_back(word);
            }
        }
        semop(semid, &spp, 1);
        return 0;
    }

    void createThreads() {
        for (int i=0; i<words.size(); i++) {
            char *stackTop;
            stacks[i] = new char[STACK_SIZE];
            stackTop = stacks[i] + STACK_SIZE;
            pids[i] = clone(makeStrings, (void *)stackTop, CLONE_VM, (void *)(&words[i]));
            std::cout << "Created thread PID " << pids[i] << "\n";
        }
        sleep(1);
    }

private:
    std::vector<std::string> words;
    std::vector<std::string> s1,s2;
    char **stacks;
    pid_t *pids;
};

int main()
{
    std::string str = "Lorem ipsum dolor sit amet consectetur adipiscing elit sed do eiusmod";
    char ch = 'p';
    std::cout << "Initial string: " << str << "\n";

    taskString ts(str, ch);
    ts.createThreads();


    std::cout << "S1: ";
    for (int i=0; i < strs.s1.size(); i++) {
        std::cout << strs.s1[i] << " ";
    }
    std::cout << "\nS2: ";
    for (int i=0; i < strs.s2.size(); i++) {
        std::cout << strs.s2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
