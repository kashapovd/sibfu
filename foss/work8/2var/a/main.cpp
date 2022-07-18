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

#define THREADS_NUMBER 2
#define STACK_SIZE (1024 * 1024)

using M=std::vector<std::vector<int>>;
using row=std::vector<int>;

struct matrixData
{
    M m;
    int max;
    int min;
} mD;
char *stacks;

int getSumMaxMin() {
    return mD.max+mD.min;
}

int calcMaxByThread(void *s) {
    mD.max = mD.m[0][0];
    for (int i=0; i < mD.m.size(); i++)
        if (mD.m[i][i] > mD.max)
            mD.max = mD.m[i][i];
    return 0;
}

int calcMinByThread(void *s) {
    mD.min = mD.m[0][mD.m.size()-1];
    for (int i=0; i < mD.m.size(); i++) {
        if (mD.m[i][mD.m.size()-i-1] < mD.min)
            mD.min = mD.m[i][mD.m.size()-i-1];
    }
    return 0;
}

void calcMaxMin() {
    stacks = new char[THREADS_NUMBER*STACK_SIZE];
    clone(calcMaxByThread, (void *)(stacks+STACK_SIZE), CLONE_VM|CLONE_VFORK, nullptr);
    clone(calcMinByThread, (void *)(stacks+STACK_SIZE*THREADS_NUMBER), CLONE_VM|CLONE_VFORK, nullptr);
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

void print(std::ostream &ost) {
    for(int i=0; i<mD.m.size(); i++) {
        for(int j=0; j<mD.m.size(); j++) {
            ost << mD.m[i][j] << " ";
        }
        ost << "\n";
    }
}

int main()
{
    std::ifstream ist;
    ist.open("matrix");
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 0;
    }
    mD.m = matrixLoad(ist);

    calcMaxMin();
    auto sum = getSumMaxMin();
    print(std::cout);
    std::cout << "\n";
    std::cout << "max: " << mD.max << " min: " << mD.min << "\n";
    std::cout << "sum of max from main diag and min from invdiag: "<< sum << "\n";
    std::cout << "\n";
    mD.m[mD.m.size()/2][mD.m.size()/2] = sum;
    print(std::cout);

    return 0;
}
