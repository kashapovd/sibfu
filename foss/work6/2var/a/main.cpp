#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define PROCESS_NUM 4

int msgid;

using M=std::vector<std::vector<int>>;
using row=std::vector<int>;

int &elemByFlatIndex(M &m, int fi) {
    return m[fi/m.size()][fi%m.size()];
}

int maxFIdxFromPart(M &m, int begin, int end) {
    int maxi = begin;
    while (begin!=end) {
        auto celem = std::abs(elemByFlatIndex(m, ++begin));
        auto cmax = std::abs(elemByFlatIndex(m, maxi));
        if(celem > cmax)
            maxi = begin;
    }
    return maxi;
}

void findMaxByProc(int i, M &m) {
    int part = (m.size()*m.size())/PROCESS_NUM;
    int begin = i*(part);
    int end;
    if (i != PROCESS_NUM-1)
        end = begin+part-1;
    else
        end = m.size()*m.size()-1;

    int maxFIdx = maxFIdxFromPart(m, begin, end);
    msgsnd(msgid, &maxFIdx, sizeof (maxFIdx), IPC_NOWAIT);

}

int findMax(M &m) {
    for (int i=0; i < PROCESS_NUM; i++) {
        if(fork()==0) {
            findMaxByProc(i, m);
            exit(0);
        }
        wait(NULL);
    }
    std::vector<int> maxIdxs;
    for (int i=0; i < PROCESS_NUM; i++) {

        int buf = 0;

        msgrcv(msgid, &buf, sizeof (buf), 0, 0);
        maxIdxs.push_back(buf);
    }

    int maxi = maxIdxs[0];
    for(const auto &it:maxIdxs) {
        int cmax = std::abs(elemByFlatIndex(m, maxi));
        int celem = std::abs(elemByFlatIndex(m, it));
        if (celem > cmax)
            maxi = it;
    }
    return maxi;
}

M matrixLoad(std::ifstream &ist) {
    int size;
    ist >> size;
    M v;
    for (int i = 0; i < size; i++) {
        auto *r = new row;
        v.push_back(*r);
        for (int j = 0; j < size; j++) {
            int buf;
            ist >> buf;
            v[i].push_back(buf);
        }
    }
    return v;
}

int main()
{
    std::ifstream ist;
    ist.open("matrix");
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 0;
    }
    auto m = matrixLoad(ist);

    msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666);
    int fidx = findMax(m);

    std::cout << "max num: " << elemByFlatIndex(m, fidx) << " at x:" << fidx%m.size() << " y: " << fidx/m.size() << std::endl;
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
