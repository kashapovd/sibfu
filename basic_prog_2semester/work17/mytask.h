#ifndef MYTASK_H
#define MYTASK_H
#include "linked_list.h"

class MyTask
{
    public:
        MyTask();
        bool isPerfect(int num);
        LIST::Node *searchPerfect(LIST::Node *first);
        int genNum(int startNum);
};

#endif // MYTASK_H
