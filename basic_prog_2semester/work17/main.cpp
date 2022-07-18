#include <iostream>
#include <fstream>
#include "linked_list.h"
#include "mytask.h"

#define INSERT_LIST_NUM 3

#define IN_PATH "youpath"
#define OUT_PATH "yourpath"

int main()
{
    std::ifstream ist;
    std::ofstream ost;

    ist.open(IN_PATH);
    ost.open(OUT_PATH);

    if (!ist.is_open() || !ost.is_open())
    {
        std::cerr << "Unable to open file or files";
        return 1;
    }

    srand(time(NULL));

    LIST lst = LIST();
    MyTask task = MyTask();

    lst.loadTxt(ist);
    LIST::Node *first  = lst.getFirst();
    lst.printList(first, ost);

    LIST::Node *list = first;

    while(task.searchPerfect(list))
    {
        list = task.searchPerfect(list);
        for (int i = 0; i < INSERT_LIST_NUM; i++)
        {
            LIST::Node *newnode = new LIST::Node;
            newnode->data = task.genNum(list->data);
            lst.insertNode(list, newnode);
            list = newnode;
        }
        list = list->link;
    }

    lst.printList(first, ost, 'c'); // cout only

    return 0;
}
