//
// Created by yaroslav on 10/5/21.
//

#ifndef PCS_UNIVERSE_H
#define PCS_UNIVERSE_H

#include <vector>
#include <deque>
#include <utility>
#include <ostream>

#include "cell.h"

using cube = std::vector<std::vector<std::vector<cell>>>;

class universe {
    std::vector<cell> cuboid;
    void kill(const int &x, const int &y, const int &z);
    void revive(const int &x, const int &y, const int &z);
    uint checkNeigh(const int &x, const int &y, const int &z);
    std::vector<int> calculateNeighCoordsByAxis(const int &x) const;
    void genUniverse();
    uint universeSize;
    uint generation=0;
    cell &cellFromCube(int x, int y, int z);

public:
    explicit universe(uint size);
    ~universe();
    uint getNumberOfLiving();
    uint getGeneraton() const;
    bool nextgen();
    void print(std::ostream &ost);
};

#endif //PCS_UNIVERSE_H
