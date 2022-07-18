#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <fstream>

class LIST
{
    public:

    LIST();
    ~LIST();

    struct Node
    {
        int data;
        Node *link;
    };

    void loadTxt(std::istream &ist);

    void printList(
            const Node *first,
            std::ostream &ost,
            char mode='f'
            );

    Node *insertNode(
            Node *prev,
            Node *node
            );

    Node *getFirst();

    private:
        Node *first;
};

#endif // LINKED_LIST_H
