#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <numeric>
#include <cstdlib>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define STACK_SIZE (1024 * 1024)

char **stacks;
uint *par;
std::vector<std::list<int>> arrayOfLists;
std::vector<double> avgs;

std::vector<std::list<int>> load(std::ifstream &ist) {
    int nlist;
    ist >> nlist;

    std::vector<std::list<int>> v;
    for (int i = 0; i < nlist; i++) {
        int listsize;
        ist >> listsize;
        std::list<int> l;
        for (int j=0; j<listsize; j++) {
            int buf;
            ist >> buf;
            l.push_back(buf);
        }
        v.push_back(l);
    }
    return v;
}

std::vector<std::list<int>> loadLists(std::string path) {
    std::ifstream ist;
    ist.open(path);
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        exit(-1);
    }
    return load(ist);
}

void print(std::vector<std::list<int>> &al, std::ostream &ost) {
    for(int i=0; i<al.size(); i++) {
        auto list = al[i];
        ost << "list" << i+1 << ": ";
        for (const auto &it : list) {
            ost << it << " ";
        }
        ost << "\n";
    }
}

int calcAvgByThread(void *i) {
    auto idx =*(int*)i;
    auto list = arrayOfLists[idx];
    double avg = double(std::accumulate(list.begin(), list.end(), 0)) / double(list.size());
    avgs.at(idx) = avg;
    return 0;
}

void calcAvg() {
    stacks = new char*[arrayOfLists.size()];
    std::vector<double> a(arrayOfLists.size());
    avgs = std::move(a);
    par = new uint[arrayOfLists.size()];
    for (int i=0; i<arrayOfLists.size(); i++) {
        par[i] = i;
        char *stackTop;
        stacks[i] = new char[STACK_SIZE];
        stackTop = stacks[i] + STACK_SIZE;
        clone(calcAvgByThread, (void *)stackTop, CLONE_VM|CLONE_VFORK, (void *)(&par[i]));
    }
}

int main()
{
    arrayOfLists = loadLists("/home/yaroslav/study/foss/8/4var/b/lists");
    print(arrayOfLists, std::cout);

    calcAvg();

    for(int i=0; i<avgs.size(); i++)
        std::cout << "avg of list" << i+1 << ": " << avgs.at(i) << "\n";

    std::cout << "sum of avgs: " << double(std::accumulate(avgs.begin(), avgs.end(), 0)) << std::endl;
    return 0;
}
