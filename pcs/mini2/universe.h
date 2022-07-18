//
// Created by yaroslav on 10/5/21.
//

#ifndef PCS_UNIVERSE_H
#define PCS_UNIVERSE_H

#include <vector>
#include <deque>
#include <utility>
#include <ostream>

using cube = std::vector<std::vector<std::vector<int>>>;

class universe {
    cube cuboid;
    void kill(const int &x, const int &y, const int &z);
    void revive(const int &x, const int &y, const int &z);
    
    std::vector<int> calculateNeighCoordsByAxisX(const int &x) const;
    std::vector<int> calculateNeighCoordsByAxisY(const int &x) const;
    std::vector<int> calculateNeighCoordsByAxisZ(const int &x) const;
    
    struct axissizes {
        int x;
        int y;
        int z;
    } sizes;
    std::vector<std::vector<int>> top_edge, bottom_edge;
    bool useEdges = false;
    uint generation=0;

public:
    universe(cube c);
    uint checkNeigh(const int &x, const int &y, const int &z);
    universe(cube c, std::vector<std::vector<int>> t, std::vector<std::vector<int>> b);
    void load(cube c);
    cube getSlices();
    static cube genUniverse(uint size);
    ~universe();
    uint getNumberOfLiving();
    uint getGeneraton() const;
    bool nextgen();
    static int *slice_to_c_array(const std::vector<std::vector<int>>& sl);
    static std::vector<std::vector<int>> slice_to_vector(const int *sl, int size);
    void print(std::ostream &ost);
};

#endif //PCS_UNIVERSE_H
