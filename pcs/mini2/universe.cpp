//
// Created by yaroslav on 10/5/21.
//

#include <cstdlib>
#include <iostream>
#include <utility>
#include <cassert>
#include "universe.h"

universe::universe(cube bitmap) {
    load(bitmap);
    sizes.x = cuboid.size();
    sizes.y = cuboid[0].size();
    sizes.z = cuboid[0][0].size();
}

universe::universe(cube c, std::vector<std::vector<int>> t, std::vector<std::vector<int>> b) {
    load(c);
    sizes.x = cuboid.size();
    sizes.y = cuboid[0].size();
    sizes.z = cuboid[0][0].size();
    top_edge = t;
    bottom_edge = b;
    useEdges = true;
}

void universe::load(cube c) {
    cuboid = std::move(c);
}

cube universe::getSlices() {
    return cuboid;
}

uint universe::getNumberOfLiving() {
    uint numberOfLiving=0;
    int x,y,z;
    for (x = 0; x < sizes.x; ++x) {
        for (y = 0; y < sizes.y; ++y) {
            for (z = 0; z < sizes.z; ++z) {
                cuboid[x][y][z] ? numberOfLiving++ : numberOfLiving;
            }
        }
    }
    return numberOfLiving;
}

void universe::kill(const int &x, const int &y, const int &z) {
    cuboid[x][y][z] = false;
}

void universe::revive(const int &x, const int &y, const int &z) {
    cuboid[x][y][z] = true;
}

bool universe::nextgen() {
    std::vector<int*> toBeKilled;
    std::vector<int*> toBeRevived;
    int x,y,z;
    for (x = 0; x < sizes.x; ++x) {
        for (y = 0; y < sizes.y; ++y) {
            for (z = 0; z < sizes.z; ++z) {
                uint neighs = checkNeigh(x,y,z);
                int *cell = &cuboid[x][y][z];
                if (*cell) {
                    if ((neighs > 5 && neighs < 14) or *cell > 3)
                        toBeKilled.push_back(cell);
                    *cell++;
                }
                else
                    if (neighs == 7 or neighs == 21 or neighs == 14 or neighs == 3) {
                        toBeRevived.push_back(cell);
                }
            }
        }
    }

    for(auto cell : toBeKilled)
        *cell = false;
    for(auto cell : toBeRevived)
        *cell = true;
    generation++;
    return getNumberOfLiving() != 0;
}

uint universe::checkNeigh(const int &x, const int &y, const int &z) {
    
    cube cuboid_with_edges;
    cuboid_with_edges.push_back(bottom_edge);
    for (const auto &slice : cuboid) {
        cuboid_with_edges.push_back(slice);
    }   
    cuboid_with_edges.push_back(top_edge);
    uint numberOfAlive = 0;
    for (const auto &xitem : calculateNeighCoordsByAxisX(x+1)) {
        for (const auto &yitem : calculateNeighCoordsByAxisY(y)) {
            for (const auto &zitem : calculateNeighCoordsByAxisZ(z)) {
                if (xitem == x+1 && yitem == y && zitem == z)
                    continue;
                cuboid_with_edges[xitem][yitem][zitem] ? numberOfAlive++ : numberOfAlive;
            }
        }
    }
    return numberOfAlive;
}

uint universe::getGeneraton() const {
    return generation;
}

inline std::vector<int> universe::calculateNeighCoordsByAxisX(const int &x) const {
    return {static_cast<int>((-1 + x +sizes.x) % sizes.x), x, static_cast<int>((1 + x + sizes.x) % sizes.x)};
}

inline std::vector<int> universe::calculateNeighCoordsByAxisY(const int &x) const {
    return {static_cast<int>((-1 + x +sizes.y) % sizes.y), x, static_cast<int>((1 + x + sizes.y) % sizes.y)};
}

inline std::vector<int> universe::calculateNeighCoordsByAxisZ(const int &x) const {
    return {static_cast<int>((-1 + x +sizes.z) % sizes.z), x, static_cast<int>((1 + x + sizes.z) % sizes.z)};
}

universe::~universe() {
    cuboid.clear();
}

std::vector<std::vector<std::vector<int>>> universe::genUniverse(uint size) {
    std::vector<std::vector<std::vector<int>>> cube (
            size, std::vector<std::vector<int>> (
                    size, std::vector<int>(size)
            )
    );
    for (int x=0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            for (int z = 0; z < size; ++z) {
                if (x == 0 or y == 0 or z == 0 or x == size-1 or y == size-1 or z == size-1)
                    if (rand() % 10)
                        cube[x][y][z] = true;
            }
        }
    }

    // cube[0][0][2] = true;
    // cube[0][1][3] = true;
    // cube[0][1][1] = true;
    // cube[0][2][2] = true;
    // cube[1][1][2] = true;
    // cube[3][0][1] = true;
    // cube[2][1][2] = true;
    // cube[3][3][3] = true;
    return cube;
}

void universe::print(std::ostream &ost) {
    for (int x=0; x < sizes.x; ++x) {
        ost << "\nx=" << x;
        for (int y = 0; y < sizes.y; ++y) {
            ost << "\n";
            for (int z = 0; z < sizes.z; ++z) {
                ost << cuboid[x][y][z] << " ";
            }
        }
    }
}

int *universe::slice_to_c_array(const std::vector<std::vector<int>>& sl) {
    int size = sl.size();
    int *array = new int [size*size]; 

    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            array[i*size+j] = sl[i][j];
        }
    }
    return array;
}

std::vector<std::vector<int>> universe::slice_to_vector(const int *sl, int size) {
    std::vector<std::vector<int>> slice(size, std::vector<int>(size));
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            slice[i][j] = sl[i*size+j];
        }
    }
    return slice;
}