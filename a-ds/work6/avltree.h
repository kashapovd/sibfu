#ifndef WORK6_AVLTREE_H
#define WORK6_AVLTREE_H

#include <iostream>

template <typename T>
class avltree {

    struct node
    {
        T val;
        int h;
        node *l;
        node *r;
    };

    node *root;
    void destroy(node *&);
    static node *node_alloc(T &);
    node *add(T &, node *&);
    node *remove(T &, node *&);
    node *fix_addition(node *&);
    node *fix_removing(node *&);
    void removeLess(double &, node *&);
    node *searchLess(double &, node *&);
    int bf(node *&);
    int ch(node *&);
    node *leftRotate(node *&);
    node *rightRotate(node *&);
    node *search(T &, node *&);
    node *min(node *);
    node *max(node *);
    void print(const std::string& prefix, const node* n, bool isLeft, std::ostream &ost);
    uint64_t size;


public:
    avltree();
    ~avltree();
    void add(T);
    void print(std::ostream &ost);
    void removeLess(double);
    bool remove(T);
    bool search(T);
    T min();
    T max();
};


#endif //WORK6_BINTREE_H
