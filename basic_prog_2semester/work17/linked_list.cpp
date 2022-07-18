#include "linked_list.h"
#include "mytask.h"
#include <iostream>
//constructor
LIST::LIST(){}

//destructor
LIST::~LIST()
{
    Node *next;
    while (first)
    {
        next = first->link;
        delete first;
        first = next;
    }
}


void LIST::loadTxt(std::istream &ist)
{
    first = nullptr;
    int data;
    Node *newnode;
    while(ist >> data)
    {
        newnode = new Node {data, nullptr}; // initializate Node
        first = insertNode(nullptr, newnode);
    }
    newnode = nullptr;
}

void LIST::printList(const Node *first, std::ostream &ost, char mode)
{
    MyTask task = MyTask();
    Node _a = *first;
    Node *_first = &_a;
    while(_first)
    {
        if (mode=='f') // full output mode
        {
            std::cout << ((task.isPerfect(_first->data)) ? "*" : "") << _first->data
                      << " -> " << ((_first->link == nullptr) ? "END" : "");
            ost << _first->data << ' ';
        }
        else {
            std::cout << ((task.isPerfect(_first->data)) ? "*" : "") << _first->data
                      << " -> " << ((_first->link == nullptr) ? "END" : "");
        }
        _first = _first->link;
    }
    std::cout << std::endl;
}

LIST::Node *LIST::insertNode(Node *prev, Node *node)
{
    if (!prev)
    {
        node->link = first;
        first = node;
    }
    else
    {
        node->link = prev->link;
        prev->link = node;
    }
    return first;
}

LIST::Node *LIST::getFirst() { return first; }
