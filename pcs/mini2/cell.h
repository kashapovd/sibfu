//
// Created by yaroslav on 10/5/21.
//

#ifndef PCS_CELL_H
#define PCS_CELL_H

#include <cstdlib>

class cell {
    enum estate {ALIVED, KILLED};
    estate state = KILLED;
    uint _age;

public:
    explicit cell(bool alive = false);
    void die();
    void resurrect();
    bool isAlive() const;
    void setAge(uint age);
    uint getAge() const;
};
#endif //PCS_CELL_H
