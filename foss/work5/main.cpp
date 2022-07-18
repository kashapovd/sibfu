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

class matrix
{
public:
    explicit matrix(std::ifstream &ist, std::ostream &ost) {
        m = load(ist);

        shmid = shmget(IPC_PRIVATE, sizeof(matrixData), IPC_CREAT|0666);
        if (shmid == -1) {
            throw "Bad memory allocation";
        }
        ost << "Shared memory object ID " << shmid << " was allocated\n";

        semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);
        if (semid == -1) {
            throw "Bad semaphore allocation";
        }
        ost << "Semaphore ID " << semid << " was allocated\n";

        semop(semid, &spp, 1);
        mD = (matrixData *)shmat(shmid,NULL,0);
    };
    ~matrix() {
        semctl(semid, 1, IPC_RMID);
        shmctl(shmid, IPC_RMID, NULL);
    }

    void calcMaxMin() {
        mD->max = m[0][0];
        mD->min = m[0][m.size()-1];
        for (int i=0; i < m.size(); i++) {
            if (fork() == 0) {
                if (m[i][i] > mD->max) {
                    semop(semid, &smm, 1);
                    mD->max = m[i][i];
                    semop(semid, &spp, 1);
                }
                if (m[i][m.size()-i-1] < mD->min) {
                    semop(semid, &smm, 1);
                    mD->min = m[i][m.size()-i-1];
                    semop(semid, &spp, 1);
                }
                exit(0);
            }
            wait(NULL);
        }
        for (int i=0; i < m.size(); i++)
            wait(NULL);
    }

    int getSumMaxMin() {
        return mD->max+mD->min;
    }

private:
    M m;
    int semid;
    int shmid;
    struct matrixData
    {
        int max;
        int min;
    } *mD;

    sembuf spp = {0, 1, 0};
    sembuf smm = {0, -1, 0};
    static M load(std::ifstream &ist) {
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
};

int main()
{
    std::ifstream ist;
    ist.open("/home/yaroslav/repos/foss/work5/matrix");
    if (!ist.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 0;
    }

    matrix *m;
    try {
         m = new matrix(ist, std::cout);
    } catch (std::string& str) {
        std::cout << "Exception: " << str << '\n';
        return -1;
    }
    fflush(stdout);
    m->calcMaxMin();

    std::cout << "sum of max from main diag and min from invdiag: "<< m->getSumMaxMin() << "\n";
    delete m;
    return 0;
}
