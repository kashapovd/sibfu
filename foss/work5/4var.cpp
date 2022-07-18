#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

using M=std::vector<std::vector<int>>;
using row=std::vector<int>;

struct matrixData
{
    double avg;
} *mD;
sembuf spp = {0, 1, 0};
sembuf smm = {0, -1, 0};
int semid;

int findSpecialByCol(M &m, int &c) {
    int sum=0;
    int max = m[0][c];
    for (int i=0; i < m.size(); i++) {
        if (m[i][c] > max)
            max = m[i][c];
    }
    for (int i=0; i < m.size(); i++) {
        if (m[i][c] != max)
            sum += m[i][c];
    }

    return max > sum ? sum : 0;
}

void calcSpecialAvg(M &m) {

    for (int i=0; i < m.size(); i++) {
        if (fork() == 0) {
            semop(semid, &smm, 1);
            int special = findSpecialByCol(m, i);
            if (special !=0)
                mD->avg += double(special) / double(m.size());
            semop(semid, &spp, 1);
            exit(0);
        }
        wait(NULL);
    }

}

double getSpecialAvg() {
    return mD->avg;
}

static M matrixLoad(std::ifstream &ist) {
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
    ist.open("/home/yaroslav/repos/foss/work5/matrix");
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 0;
    }
    auto m = matrixLoad(ist);

    int shmid = shmget(IPC_PRIVATE, sizeof(matrixData), IPC_CREAT|0666);
    if (shmid == -1) {
        std::cout << "Bad memory allocation";
        return -1;
    }
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
    if (semid == -1) {
        std::cout << "Bad semaphore allocation";
        return -1;
    }
    semop(semid, &spp, 1);
    mD = (matrixData *)shmat(shmid,NULL,0);
    mD->avg = 0;

    calcSpecialAvg(m);

    std::cout << "average of special numbers: "<< getSpecialAvg() << "\n";
    return 0;
}