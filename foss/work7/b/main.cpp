#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define PROCESS_NUM 2

class bitArray
{
public:
    bitArray(std::string &istr, std::ostream &ost) {
        std::stringstream ss(istr);
        load(ss);
        std::cout << "loaded " << dnumbers.size() << " numbers\n";
        print(ost);
        msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666);
    };
    ~bitArray() {
        msgctl(msgid, IPC_RMID, NULL);
    }

    void sumByProc(int &p) {
        int part = (dnumbers.size())/PROCESS_NUM;
        int begin = p*(part);
        int end;
        int sum = 0;

        if (p != PROCESS_NUM-1)
            end = begin+part;
        else
            end = dnumbers.size();

        while (begin!=end) 
            sum+=dnumbers[begin++];

        m.mdata = sum;
        msgsnd(msgid, &m, sizeof (message), 0);
    }

    uint calcSum() {
        uint sum=0;
        for (int i=0; i < PROCESS_NUM; i++) {
            int pid = fork();
            struct sigaction act;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            act.sa_handler = action;
            sigaction(SIGUSR1,& act,0);
            
            if (pid > 0) {
                sleep(0.2);
                std::cout << "Invoke child PID " << pid << "\n";
                kill(pid, SIGUSR1);
                pause();
            } else {
                pause();
                std::cout << "\tChild PID " << getpid() << " invoked \n";
                sumByProc(i);
                kill(getppid(), SIGUSR1);
                std::cout << "\tChild PID " << getpid() << " done \n";
                exit(0);
            }
        }
        for (int i=0; i < PROCESS_NUM; i++) {
            msgrcv(msgid, &m, sizeof (message), 0, 0);
            sum+=m.mdata;
        }
        return sum;
    }

    void print(std::ostream &ost) {
        for (const auto &it : dnumbers) {
            ost << it << " ";
        }
        ost << std::endl;
    }


private:
    int msgid;
    std::vector<uint> dnumbers;

    struct message {
        int mdata;
    } m;
    
    static void action(int dummy) {
        std::cout << "\tProcess " << getpid() << " cached signal\n";
        sleep(1);
    }

    void load(std::stringstream &isst) {
        std::vector<std::string> a;
        std::vector<uint> numbers;
        std::string buf;
        uint bitsNumber = 0;
        while (isst >> buf) {
            if (buf.size() > bitsNumber)
                bitsNumber = buf.size();
            a.push_back(buf);
        }  
        uint _sum=0;
        for (const auto &it : a) {
            std::bitset<32> binNum(it);
            dnumbers.push_back(binNum.to_ulong());
        }
    }
};

int main()
{
    std::string bitstr("101 011 1 0 1010101 1110010 1000001 10 10101010");
    bitArray *a = new bitArray(bitstr, std::cout);
    std::cout << "Master-process have PID " << getpid() << "\n";
    
    fflush(stdout);
    auto s = a->calcSum();
    std::cout << "sum of bit numbers: " << s << std::endl;
    delete a;
    return 0;
}
