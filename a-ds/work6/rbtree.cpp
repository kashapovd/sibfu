#include <cstdint>
#include "rbtree.h"

template <typename T>
rbtree<T>::rbtree()
{
    size=0;
    leaf = new node {0, BLACK, nullptr, nullptr, nullptr};
    root = leaf;
}

template<typename T>
rbtree<T>::~rbtree()
{
    destroy(root);
    delete leaf;
    leaf = root = nullptr;
}

template <typename T>
void rbtree<T>::add(T val)
{
    auto n = add(val, root);
    fix_addition(n);
}

template<typename T>
typename rbtree<T>::node *rbtree<T>::add(T &val, rbtree::node *&n)
{
    node *ret = nullptr;

    if (n == leaf)
    {
        n = node_alloc(val);
        if (root == n)
        {
            n->c = color::BLACK;
            n->p = nullptr;
        }
        size++;
        return n;
    }
    else if (val < n->val) {
        ret = add(val, n->l);
        n->l->p = n;
    }
    else if (val > n->val) {
        ret = add(val, n->r);
        n->r->p = n;
    }
    return ret;
}

template<typename T>
void rbtree<T>::fix_addition(node *&n)
{
    while (n != root && n->p->c == RED)
    {
        auto parent = n->p;
        node *gparent = n->p->p;
        if (parent == gparent->l) // father is left child
        {
            auto u = gparent->r;
            if (u != leaf && u->c == RED) {
                color_flip(gparent);
                n = gparent;
            }
            else
                {
                    if (n == parent->r)
                    {
                        leftRotate(parent);
                        n = parent;
                        parent = n->p;
                    }
                    rightRotate(gparent);
                    std::swap(parent->c, gparent->c);
                    n = parent;
                }
        }
        else // father is right child
            {
                auto u = gparent->l;
                if (u != leaf && u->c == RED) {
                    color_flip(gparent);
                    n = gparent;
                }
                else
                    {
                        if (n == parent->l)
                        {
                            rightRotate(parent);
                            n = parent;
                            parent = n->p;
                        }
                        leftRotate(gparent);
                        std::swap(parent->c, gparent->c);
                        n = parent;
                    }
            }
        //fix_addition(u->p);
    }
    root->c = BLACK;
}

template<typename T>
void rbtree<T>::color_flip(node *&n)
{
    if (n->c == RED)
    {
        n->c = BLACK;
        n->l->c = n->r->c = RED;
    }
    else
        {
            n->c = RED;
            n->l->c = n->r->c = BLACK;
        }
}

template<typename T>
bool rbtree<T>::remove(T val)
{
    return static_cast<bool>(remove(val, root));
}

template<typename T>
typename rbtree<T>::node *rbtree<T>::remove(T &val, rbtree::node *&n)
{
    auto ret = n;
    if (n == nullptr)
        return nullptr;
    if (val < n->val)
        ret = remove(val, n->l);
    else if (val > n->val)
        ret = remove(val, n->r);
    else
    {
        auto old_n = n;
        node x {.val=n->val, .c=n->c, .p=n->p, .l=n->l, .r=n->r};
        auto original_color = old_n->c;
        if(n->l == leaf)
        {
            n = n->r;
            if (n != leaf)
                n->p = old_n->p;
            delete old_n;
            size--;
        }
        else if (n->r == leaf)
        {
            n = n->l;
            if (n != leaf)
                n->p = old_n->p;
            delete old_n;
            size--;

        }
        else
        {
            auto min_n = min(n->r);
            n->val = min_n->val;
            return remove(min_n->val, n->r);
        }
        if (original_color == BLACK && size != 0) {
            fix_removing(&x);
        }
    }
    return ret;
}

template<typename T>
void rbtree<T>::fix_removing(rbtree::node *n)
{
    while (n != root and n->c == BLACK)
    {
        if (n->val < n->p->val)
        {
            auto s = n->p->r;
            if (s->c == RED)
            {
                std::swap(s->c, n->p->c);
                leftRotate(n->p);
                s = n->p->r;
            }
            if (s->l->c == BLACK and s->r->c == BLACK)
            {
                s->c = RED;
                n = n->p;
            }
            else
                {
                    if (s->r->c == BLACK)
                    {
                        std::swap(s->c, s->l->c);
                        rightRotate(s);
                        s = n->p->r;
                    }
                    s->c = n->p->c;
                    n->p->c = BLACK;
                    s->r->c = BLACK;
                    leftRotate(n->p);
                    n = root;
                }
        }
        else
            {
                auto s = n->p->l;
                if (s->c == RED)
                {
                    std::swap(s->c, n->p->c);
                    rightRotate(n->p);
                    s = n->p->l;
                }
                if (s->r->c == BLACK && s->l->c == BLACK)
                {
                    s->c = RED;
                    n = n->p;
                }
                else
                    {
                        if (s->l->c == BLACK)
                        {
                            std::swap(s->c, s->r->c);
                            leftRotate(s);
                            s = n->p->l;
                        }

                        s->c = n->p->c;
                        n->p->c = BLACK;
                        s->l->c = BLACK;
                        rightRotate(n->p);
                        n = root;
                }
            }
        }
    n->c = BLACK;
}

template<typename T>
inline typename rbtree<T>::node* rbtree<T>::node_alloc(T &val, color c)
{
    node *n = new node;
    n->c = c;
    n->val = val;
    n->l = n->r = leaf;
    return n;
}

template<typename T>
void rbtree<T>::destroy(node *&n)
{
    if (n == leaf)
        return;
    destroy(n->l);
    destroy(n->r);
    delete n;
}

template<typename T>
void rbtree<T>::removeLess(double val)
{
    removeLess(val, root);
}

template<typename T>
void rbtree<T>::removeLess(double &val, rbtree::node *&n)
{
    auto x = searchLess(val, root);
    while (x)
    {
        remove(x->val);
        x = searchLess(val, root);
    }
}

template<typename T>
typename rbtree<T>::node *rbtree<T>::searchLess(double &val, rbtree::node *&n)
{
    if (n->val < val)
        return n;
    if (n->l != leaf)
        return searchLess(val, n->l);
    if (n->r != leaf)
        return searchLess(val, n->r);
    return nullptr;
}

template<typename T>
bool rbtree<T>::search(T val) { return static_cast<bool>(search(val, root)); }

template<typename T>
typename rbtree<T>::node* rbtree<T>::search(T &val, rbtree::node *&n)
{
    if (n == nullptr) return n;
    if (n->val == val)
        return n;
    else if (val < n->val)
        search(val, n->l);
    else if (val > n->val)
        search(val, n->r);
    return nullptr;
}

template<typename T>
T rbtree<T>::max() { return max(root)->val; }

template<typename T>
typename rbtree<T>::node *rbtree<T>::max(rbtree::node *mn)
{
    while (mn->r != leaf)
        mn = mn->r;
    return mn;
}

template<typename T>
T rbtree<T>::min() { return min(root)->val; }

template<typename T>
typename rbtree<T>::node *rbtree<T>::min(rbtree::node *mn)
{
    while (mn->l != leaf)
        mn = mn->l;
    return mn;
}

template<typename T>
void rbtree<T>::print(std::ostream &ost)
{
    if (!size)
        ost << "> tree is empty\n";
    else
        print("", root, false, ost);
}

template<typename T>
void rbtree<T>::print(const std::string& prefix, const node* n, bool isLeft, std::ostream &ost)
{
    if(n != leaf)
    {
        ost << prefix;

        if (n==root)
            ost << "> ";
        else
            ost << (isLeft && n->p->r != leaf ? "├── " : "└── " );

        std::cout << (n->c == color::RED ? "r" : "b") << "[" << n->val << "]" << std::endl;

        print( prefix + (isLeft ? "│   " : "    "), n->l, true, ost);
        print( prefix + (isLeft ? "│   " : "    "), n->r, false, ost);
    }
}

template<typename T>
void rbtree<T>::leftRotate(rbtree::node *&n)
{
    auto nr = n->r;
    n->r = nr->l;

    if (n->r != leaf)
        n->r->p = n;
    nr->p = n->p;

    if (n->p == nullptr)
        root = nr;
    else if (n == n->p->l)
        n->p->l = nr;
    else
        n->p->r = nr;

    nr->l = n;
    n->p = nr;
}

template<typename T>
void rbtree<T>::rightRotate(rbtree::node *&n)
{
    auto nl = n->l;
    n->l = nl->r;

    if (n->l != leaf)
        n->l->p = n;
    nl->p = n->p;

    if (n->p == nullptr)
        root = nl;
    else if (n == n->p->l)
        n->p->l = nl;
    else
        n->p->r = nl;

    nl->r = n;
    n->p = nl;
}

template class rbtree<int8_t>;
template class rbtree<int16_t>;
template class rbtree<int32_t>;
template class rbtree<int64_t>;
template class rbtree<uint8_t>;
template class rbtree<uint16_t>;
template class rbtree<uint32_t>;
template class rbtree<uint64_t>;
template class rbtree<double>;
template class rbtree<float>;