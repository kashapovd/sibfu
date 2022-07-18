#ifndef WORK6_BINTREE_H
#define WORK6_BINTREE_H

#include <iostream>

template <typename T>
class bintree {

    struct node
            {
                T val;
                node *l;
                node *r;
            };
    node *root;
    void destroy(node *&);
    static node *node_alloc(T &);
    void add(T &, node* &);
    node *remove(T &, node *&);
    void removeLess(double &, node *&);
    node *search(T &, node *&);
    node *min(node *);
    node *max(node *);
    void print(const std::string &, const node *n, bool isLeft, std::ostream &);
    uint64_t size;


public:
    bintree();
    ~bintree();
    void add(T);
    void print(std::ostream &);
    void removeLess(double);
    bool remove(T);
    bool search(T);
    T min();
    T max();
};


#endif //WORK6_BINTREE_H
