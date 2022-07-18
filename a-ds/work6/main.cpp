#include <vector>
#include <iostream>

#include "bintree.h"
#include "rbtree.h"
#include "avltree.h"


template <typename Type, typename Tree>
void tree_fill(std::vector<Type> &v, Tree &t)
{
    for(const auto &it : v)
        t.add(it);
}

int main()
{
    std::ostream &ost(std::cout);
    using type = int;
    std::vector<type> v {5, 2, 1, 4, 32, 7, 10, 22, -1, 23, 0, 45};
    ost << "<<<=======Standart BST=======>>>\n";
    bintree<type> btree;
    tree_fill(v, btree);
    btree.print(ost);
    ost << "\nmax: " << btree.max()
        << "\nall less than max/2 removed:\n";
    btree.removeLess(btree.max()/2.0);
    btree.print(ost);
    ost << "\n<<<=======Standart BST=======>>>\n";

    ost << "\n<<<=======Red-Black Tree=======>>>\n";
    rbtree<type> rbtree;
    tree_fill(v, rbtree);
    rbtree.print(ost);
    ost << "\nmax: " << rbtree.max()
        << "\nall less than max/2 removed:\n";
    rbtree.removeLess(rbtree.max()/2.0);
    rbtree.print(ost);
    ost << "\n<<<=======Red-Black Tree=======>>>\n";

    ost << "\n<<<=======AVL Tree=======>>>\n";
    avltree<type> avltree;
    tree_fill(v, avltree);
    avltree.print(ost);
    ost << "\nmax: " << avltree.max()
        << "\nall less than max/2 removed:\n";
    avltree.removeLess(avltree.max()/2.0);
    avltree.print(ost);
    ost << "\n<<<=======AVL Tree=======>>>";
    return 0;
}
