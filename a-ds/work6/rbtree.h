#ifndef WORK6_RBTREE_H
#define WORK6_RBTREE_H

#include <iostream>

template <typename T>
class rbtree {
    enum color {RED, BLACK};
    struct node
    {
        T val;
        color c;
        node *p;
        node *l;
        node *r;
    };
    node *root;
    node *leaf;
    void destroy(node *&);
    node *node_alloc(T &, color = RED);
    void fix_addition(node *&);
    void fix_removing(node *);
    void leftRotate(node *&);
    void rightRotate(node *&);
    void color_flip(node *&);
    node *add(T &, node *&);
    node *remove(T &, node *&);
    void removeLess(double &, node *&);
    node *search(T &, node *&);
    node *searchLess(double &, node *&);
    node *min(node *);
    node *max(node *);
    void print(const std::string& prefix, const node* n, bool isLeft, std::ostream &ost);
    uint64_t size;


public:
    rbtree();
    ~rbtree();
    void add(T);
    void print(std::ostream &ost);
    void removeLess(double);
    bool remove(T);
    bool search(T);
    T min();
    T max();
};

#endif //WORK6_RBTREE_H
