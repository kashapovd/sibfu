//
// Created by yaroslav on 10/5/21.
//

#include <cstdlib>
#include <iostream>
#include <atomic>
#include <omp.h>

#include "universe.h"

universe::universe(uint size) {
    universeSize = size;
    std::vector<cell> cube (size*size*size);
    cuboid = std::move(cube);
    genUniverse();
}

uint universe::getNumberOfLiving() {
    uint numberOfLiving;
    int x,y,z;
#pragma omp parallel
    {
    #pragma omp for collapse(3) reduction(+:numberOfLiving)
        for (x = 0; x < universeSize; ++x) {
            for (y = 0; y < universeSize; ++y) {
                for (z = 0; z < universeSize; ++z) {
                    cellFromCube(x, y, z).isAlive() ? numberOfLiving++ : numberOfLiving;
                }
            }
        }
    }
    return numberOfLiving;
}

void universe::kill(const int &x, const int &y, const int &z) {
    cellFromCube(x, y, z).die();
}

void universe::revive(const int &x, const int &y, const int &z) {
    cellFromCube(x, y, z).resurrect();
}

bool universe::nextgen() {
    int x,y,z,sumOfCubeChanges=0;
#pragma omp parallel
    {
    std::vector<cell*> toBeKilled;
    std::vector<cell*> toBeRevived;
    #pragma omp for collapse(3) reduction(+:sumOfCubeChanges)
        for (x = 0; x < universeSize; ++x) {
            for (y = 0; y < universeSize; ++y) {
                for (z = 0; z < universeSize; ++z) {
                    uint neighs = checkNeigh(x, y, z);
                    cell *cell = &cellFromCube(x, y, z);
                    if (cell->isAlive()) {
                        if ((neighs > 5 && neighs < 14) or cell->getAge() > 2)
                            toBeKilled.push_back(cell);
                        cell->setAge(cell->getAge() + 1);
                    } else if (neighs == 7 or neighs == 21 or neighs == 14 or neighs == 3) {
                        toBeRevived.push_back(cell);
                    }
                }
            }
        }
        sumOfCubeChanges+=toBeRevived.size()+toBeKilled.size();
        if (sumOfCubeChanges != 0) {
            for (auto &cell : toBeKilled)
                cell->die();
            for (auto &cell : toBeRevived)
                cell->resurrect();
        }
    }

    generation++;
    return static_cast<bool>(sumOfCubeChanges);
}

uint universe::checkNeigh(const int &x, const int &y, const int &z) {
    uint numberOfAlive = 0;
    for (const auto &xitem : calculateNeighCoordsByAxis(x)) {
        for (const auto &yitem : calculateNeighCoordsByAxis(y)) {
            for (const auto &zitem : calculateNeighCoordsByAxis(z)) {
                if (xitem == x && yitem == y && zitem == z)
                    continue;
                cellFromCube(xitem, yitem, zitem).isAlive() ? numberOfAlive++ : numberOfAlive;
            }
        }
    }
    return numberOfAlive;
}

uint universe::getGeneraton() const {
    return generation;
}

void universe::genUniverse() {
    srand(10);
    for (int x=0; x < universeSize; ++x) {
         for (int y = 0; y < universeSize; ++y) {
             for (int z = 0; z < universeSize; ++z) {
                 if (x == 0 or y == 0 or z == 0 or x == universeSize-1 or y == universeSize-1 or z == universeSize-1)
                     if (rand() % 10)
                         cellFromCube(x, y, z).resurrect();
	        }
	    }
    }
}

inline std::vector<int> universe::calculateNeighCoordsByAxis(const int &x) const {
    return {static_cast<int>((-1 + x +universeSize) % universeSize), x, static_cast<int>((1 + x + universeSize) % universeSize)};
}

universe::~universe() {
    cuboid.clear();
}

void universe::print(std::ostream &ost) {
    for (int x=0; x < universeSize; ++x) {
        ost << "\nx=" << x;
        for (int y = 0; y < universeSize; ++y) {
            ost << "\n";
            for (int z = 0; z < universeSize; ++z) {
                ost << cellFromCube(x, y, z).isAlive() << " ";
            }
        }
    }
}

cell &universe::cellFromCube(int x, int y, int z) {
    return cuboid[(z * universeSize * universeSize) + (y * universeSize) + x];
}
