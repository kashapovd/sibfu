#include <iostream>
#include <chrono>

#include "mpi.h"
#include "universe.h"

#define timer_start (std::chrono::high_resolution_clock::now())
#ifdef timer_start
#define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::milliseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif
#define TAG 0
#define TOP 0
#define BOTTOM 1

void print(int **sl, int size) {
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            std::cout << sl[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {

    int numOfGenerations;
    int universeSize=1;
    char printGenInfo = 'y';
    char printGenMaps = 'n';

    int rank, commSize;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    if (rank == 0) {
        if (commSize == 1) {
            std::cout << "Run with more than one process\n";
            exit(1);
        }
        std::cout << "Size of cube: ";
        std::cin >> universeSize;

        std::cout << "Number of generations: ";
        std::cin >> numOfGenerations;

        do {
            std::cout << "Print generations info? [y/n]: ";
            std::cin >> printGenInfo;
        } while (!std::cin.fail() && std::tolower(printGenInfo) != 'y' && std::tolower(printGenInfo) != 'n');

        if (printGenInfo == 'y') {
            do {
                std::cout << "Print cube layers? [y/n]: ";
                std::cin >> printGenMaps;
            } while (!std::cin.fail() && std::tolower(printGenMaps) != 'y' && std::tolower(printGenMaps) != 'n');
        }

        std::cout << "Life has begun...\n";
        auto timer = timer_start;

        auto cuboid = universe::genUniverse(universeSize);
        universe *u;
        u = new universe(cuboid);
        int buf = universeSize;
        int slices_count = universeSize / (commSize-1);
        for(int i=1; i < commSize; ++i) {
            MPI_Send(&buf, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        for(int i=1; i < commSize; ++i) {
            MPI_Send(&numOfGenerations, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

       bool lifeDie = false;
       std::ostream &ost(std::cout);

        for (uint i=0; i < numOfGenerations; ++i) {

            if (printGenInfo == 'y') {
                std::cout << "GEN: " << i << " LIVING: " << u->getNumberOfLiving() << std::endl;
                if (printGenMaps == 'y')
                    u->print(ost);
            }
            for(int j=0; j < commSize-1; ++j) {
                MPI_Send(&slices_count, 1, MPI_INT, j+1, TAG, MPI_COMM_WORLD);
                for (int k=0; k < slices_count; ++k) {
                    auto *slice = universe::slice_to_c_array(cuboid[j+k]);
                    MPI_Send(slice, universeSize*universeSize, MPI_INT, j+1, TAG, MPI_COMM_WORLD);
                    delete slice;
                }
            }

            cuboid.clear();
            for(int j=0; j < commSize-1; ++j) {
                for (int k=0; k < slices_count; ++k) {
                    int *slice = new int [universeSize*universeSize];
                    MPI_Recv(slice, universeSize*universeSize, MPI_INT, j+1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    cuboid.push_back(universe::slice_to_vector(slice, universeSize));
                }
            }

            u->load(cuboid);
            //u->print(std::cout);

            if (!u->getNumberOfLiving()) {
                lifeDie = true;
                numOfGenerations = i + 1;
                break;
            }
        }

        auto elapsed = timer_elapsed(timer);
        if (lifeDie) {
            std::cout << "All cellulars died due to mass extinction on " << numOfGenerations << " generation\n";
        }
        std::cout << "Life for " << numOfGenerations << " generations took " << elapsed << " microseconds" << std::endl;
        delete u;
        u = nullptr;
    } else {

        int size, slices_count;
        MPI_Recv(&size, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&numOfGenerations, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (uint i=0; i < numOfGenerations; ++i) {
            MPI_Recv(&slices_count, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            cube slices;
            for (int i=0; i < slices_count; i++) {
                int *slice = new int [size*size];
                MPI_Recv(slice, size*size, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                slices.push_back(universe::slice_to_vector(slice, size));
                delete slice;
            }

            cube edges;
            int top_idx = (rank+1 > commSize-1) ? 0 : rank+1;
            int bottom_idx = (rank-1 == 0) ? commSize-1 : rank-1;

            int *top = universe::slice_to_c_array(slices.front());
            int *bottom = universe::slice_to_c_array(slices.back());
            if (commSize != 2) {
                MPI_Send(bottom, size*size, MPI_INT, bottom_idx, BOTTOM, MPI_COMM_WORLD);
                MPI_Send(top, size*size, MPI_INT, top_idx, TOP, MPI_COMM_WORLD);
                MPI_Recv(bottom, size*size, MPI_INT, bottom_idx, BOTTOM, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(top, size*size, MPI_INT, top_idx, TOP, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            edges.push_back(universe::slice_to_vector(bottom, size));
            edges.push_back(universe::slice_to_vector(top, size));
            

            universe *u;
            u = new universe(slices, edges.back(), edges.front());
            u->nextgen();

            slices = u->getSlices();
            for(int j=0; j < slices_count; ++j) {
                auto *slice = universe::slice_to_c_array(slices[j]);
                MPI_Send(slice, size*size, MPI_INT, 0, TAG, MPI_COMM_WORLD);
                delete slice;
            }
            
            delete u, top, bottom;
            top, u, bottom = nullptr;
        }
    }

    MPI_Finalize();
    return 0;
}