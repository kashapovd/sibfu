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

#define STACK_SIZE (1024 * 1024)

using M=std::vector<std::vector<int>>;
using row=std::vector<int>;
char **stacks;
uint *par;
M m1, m2, mm;
int semid;
sembuf spp = {0, 1, 0};
sembuf smm = {0, -1, 0};

M load(std::ifstream &ist) {
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

M loadMatrix(std::string path) {
    std::ifstream ist;
    ist.open(path);
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        return (M)0;
    }
    return load(ist);
}


static int mulByThread(void *i) {
    auto idx = *(uint *)i;
    int row = idx/m1.size();
    int col = idx%m1.size();
    for (int k=0; k < m1.size(); k++) {
        mm[row][col] += m1[row][k]*m2[k][col];
    }
    return 0;
}

M mult() {
    std::vector<std::vector<int>> multMatrix(m1.size(), std::vector<int>(m1.size(), 0));
    mm = std::move(multMatrix);

    stacks = new char*[m1.size()];

    par = new uint[m1.size()*m1.size()];
    for (int i=0; i<m1.size()*m1.size(); i++) {
        char *stackTop;
        par[i] = (uint)i;
        stacks[i] = new char[STACK_SIZE];
        stackTop = stacks[i] + STACK_SIZE;
        auto pid = clone(mulByThread, (void *)stackTop, CLONE_VM|CLONE_VFORK, (void *)(&par[i]));
    }
    return mm;
}

void print(M &m, std::ostream &ost) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m.size(); j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
    semop(semid, &spp, 1);

    m1 = loadMatrix("/home/yaroslav/repos/foss/work8/b/matrix1");
    m2 = loadMatrix("/home/yaroslav/repos/foss/work8/b/matrix2");
    mult();

    std::cout << "First matrix:\n";
    print(m1, std::cout);
    std::cout << "Second matrix:\n";
    print(m2, std::cout);
    std::cout << "Resul matrix:\n";
    print(mm, std::cout);

    semctl(semid, 1, IPC_RMID);
    return 0;
}
