#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdlib>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

using A=std::vector<int>;

int *interval;
int *shmOffset;
sembuf spp = {0, 1, 0};
sembuf smm = {0, -1, 0};
int semid;

int fillIntervalMaxToMin(A &arr){
    int max = *std::max_element(arr.begin(), arr.end());
    int min = *std::min_element(arr.begin(), arr.end());
    int intervalElemNumber = 0;
    for (int i=min+1; i < max; i++) {
        if (std::find(arr.begin(), arr.end(), i) == arr.end())
            intervalElemNumber++;
    }

    int shmidInterval = shmget(IPC_PRIVATE, sizeof(int)*intervalElemNumber, IPC_CREAT|0666);
    if (shmidInterval == -1) {
        std::cout << "Bad memory allocation";
        exit(0);
    }
    interval = (int *)shmat(shmidInterval,NULL,0);

    int shmidOffset = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);
    if (shmidOffset == -1) {
        std::cout << "Bad memory allocation";
        exit(0);
    }
    shmOffset = (int *)shmat(shmidOffset,NULL,0);
    *shmOffset=0;

    for (int i=min+1; i < max; i++) {
        if(fork() == 0) {
            if (std::find(arr.begin(), arr.end(), i) == arr.end()) {
                semop(semid, &smm, 1);
                interval[(*shmOffset)++] = i;
                semop(semid, &spp, 1);
            }
            exit(0);
        }
        wait(NULL);
    }
    return intervalElemNumber;
}

A arrayLoad(std::ifstream &ist) {
    int size;
    ist >> size;
    A v;
    for (int i = 0; i < size; i++) {
        int buf;
        ist >> buf;
        v.push_back(buf);
    }
    return v;
}

int main()
{
    std::ifstream ist;
    ist.open("/home/yaroslav/repos/foss/work5/array");
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 0;
    }
    auto a = arrayLoad(ist);

    semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
    if (semid == -1) {
        std::cout << "Bad semaphore allocation";
        return -1;
    }
    semop(semid, &spp, 1);
    int intervalSize = fillIntervalMaxToMin(a);

    std::cout << "interval: ";
    for(int i=0; i < intervalSize; i++) {
        std::cout << interval[i] << " ";
    }
    return 0;
}
