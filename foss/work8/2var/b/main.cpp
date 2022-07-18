#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <list>
#include <tuple>
#include <cstdlib>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define STACK_SIZE (1024 * 1024)

char **stacks;
uint *par;
std::vector<std::tuple<bool, std::list<int>>> arrayOfLists;

std::vector<std::tuple<bool, std::list<int>>> load(std::ifstream &ist) {
    int nlist;
    ist >> nlist;

    std::vector<std::tuple<bool, std::list<int>>> v;
    for (int i = 0; i < nlist; i++) {
        int listsize;
        ist >> listsize;
        std::list<int> l;
        for (int j=0; j<listsize; j++) {
            int buf;
            ist >> buf;
            l.push_back(buf);
        }
        auto t = std::make_tuple(false, l);
        v.push_back(t);
    }
    return v;
}

std::vector<std::tuple<bool, std::list<int>>> loadLists(std::string path) {
    std::ifstream ist;
    ist.open(path);
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        exit(-1);
    }
    return load(ist);
}

void print(std::vector<std::tuple<bool, std::list<int>>> &al, std::ostream &ost) {

    for(int i=0; i<al.size(); i++) {
        auto [isZero, list] = al[i];
        if (!isZero) {
            std::cout << "list" << i+1 << ": ";
            for(int j=0; j<list.size(); j++) {
                int listElement = list.front();
                std::cout << listElement << " ";
                list.pop_front();
                list.push_back(listElement);
            }
            std::cout << "\n";
        }
    }
}

int checkList(void *i) {
    auto idx =*(int*)i;
    auto t = &arrayOfLists[idx];
    auto list = std::get<1>(*t);
    auto isZero = false;
    for (const auto &it : list) {
        if (it == 0) {
            std::get<0>(*t) = true;
            return 0;
        }
    }
    return 0;
}

void checkZeroList() {
    stacks = new char*[arrayOfLists.size()];
    par = new uint[arrayOfLists.size()];
    for (int i=0; i<arrayOfLists.size(); i++) {
        par[i] = i;
        char *stackTop;
        stacks[i] = new char[STACK_SIZE];
        stackTop = stacks[i] + STACK_SIZE;
        clone(checkList, (void *)stackTop, CLONE_VM|CLONE_VFORK, (void *)(&par[i]));
    }
}

int main()
{
    arrayOfLists = loadLists("lists");

    checkZeroList();
    print(arrayOfLists, std::cout);
    return 0;
}
