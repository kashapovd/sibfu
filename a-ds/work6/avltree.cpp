#include <cstdint>
#include "avltree.h"

template <typename T>
avltree<T>::avltree()
{
    size=0;
    root = nullptr;
}

template<typename T>
avltree<T>::~avltree()
{
    destroy(root);
    root = nullptr;
}

template <typename T>
void avltree<T>::add(T val)
{
    root = add(val, root);
}

template<typename T>
typename avltree<T>::node *avltree<T>::add(T &val, avltree::node *&n)
{
    if (n == nullptr)
    {
        n = node_alloc(val);
        size++;
        return n;
    }
    else if (val < n->val)
        add(val, n->l);
    else if (val > n->val)
        add(val, n->r);
    n->h = ch(n);
    n = fix_addition(n);
    return n;
}

template<typename T>
typename avltree<T>::node *avltree<T>::fix_addition(avltree::node *&n)
{
    if(bf(n) == 2 && bf(n->l) == 1)
        return rightRotate(n);
    else if(bf(n) == -2 && bf(n->r) == -1)
        return leftRotate(n);
    else if(bf(n) == -2 && bf(n->r) == 1)
    {
        n->r = rightRotate(n->r);
        return leftRotate(n);
    }
    else if(bf(n) == 2 && bf(n->l) == -1)
    {
        n->l = leftRotate(n->l);
        return rightRotate(n);
    }
    return n;
}

template<typename T>
bool avltree<T>::remove(T val)
{
    root = remove(val, root);
}

template<typename T>
typename avltree<T>::node *avltree<T>::remove(T &val, avltree::node *&n)
{
    if (n == nullptr)
        return nullptr;
    if (val < n->val)
    {
        remove(val, n->l);
        n->h = ch(n);
    }
    else if (val > n->val)
    {
        remove(val, n->r);
        n->h = ch(n);
    }
    else {
        auto old_n = n;
        if (n->l == nullptr)
        {
            n = n->r;
            delete old_n;
            size--;
        }
        else if (n->r == nullptr)
        {
            n = n->l;
            delete old_n;
            size--;
        } else
            {
                auto min_n = min(n->r);
                n->val = min_n->val;
                remove(min_n->val, n->r);
            }
    }
    n = fix_removing(n);
    return n;
}

template<typename T>
typename avltree<T>::node *avltree<T>::fix_removing(avltree::node *&n)
{
    if (n == nullptr) return n;
    if(bf(n)==2 && bf(n->l)==1)
        return rightRotate(n);
    else if(bf(n)==2 && bf(n->l)==0)
        return rightRotate(n);
    else if(bf(n)==-2 && bf(n->r)==-1)
        return leftRotate(n);
    else if(bf(n)==-2 && bf(n->r)==0)
        return leftRotate(n);
    else if(bf(n)==2 && bf(n->l)==-1)
    {
        n->l = leftRotate(n->l);
        return rightRotate(n);
    }
    else if(bf(n)==-2 && bf(n->r)==1)
    {
        n->r = rightRotate(n->r);
        return leftRotate(n);
    }
    return n;
}

template<typename T>
inline typename avltree<T>::node* avltree<T>::node_alloc(T &val)
{
    node *n = new node;
    n->val = val;
    n->l = n->r = nullptr;
    n->h = 1;
    return n;
}

template<typename T>
void avltree<T>::removeLess(double val)
{
    auto x = searchLess(val, root);
    while (x)
    {
        remove(x->val);
        x = searchLess(val, root);
    }
}

template<typename T>
typename avltree<T>::node *avltree<T>::searchLess(double &val, avltree::node *&n)
{
    if (n->val < val)
        return n;
    if (n->l != nullptr)
        return searchLess(val, n->l);
    if (n->r != nullptr)
        return searchLess(val, n->r);
    return nullptr;
}

template<typename T>
void avltree<T>::removeLess(double &val, avltree::node *&n)
{
    if (n == nullptr) return;
    if (n->val >= val)
        removeLess(val, n->l);
    else
    {
        removeLess(val, n->l);
        removeLess(val, n->r);
        remove(n->val, n);
    }
}

template<typename T>
bool avltree<T>::search(T val) { return static_cast<bool>(search(val, root)); }

template<typename T>
typename avltree<T>::node* avltree<T>::search(T &val, avltree::node *&n)
{
    if (n->val == val)
        return n;
    else if (val < n->val)
        search(val, n->l);
    else if (val > n->val)
        search(val, n->r);
    return nullptr;
}

template<typename T>
T avltree<T>::max() { return max(root)->val; }

template<typename T>
typename avltree<T>::node *avltree<T>::max(node *mn)
{
    while (mn->r != nullptr)
        mn = mn->r;
    return mn;
}

template<typename T>
T avltree<T>::min() { return min(root)->val; }

template<typename T>
typename avltree<T>::node *avltree<T>::min(node *mn)
{
    while (mn->l != nullptr)
        mn = mn->l;
    return mn;
}

template<typename T>
void avltree<T>::print(std::ostream &ost) { print("", root, false, ost); }

template<typename T>
void avltree<T>::destroy(node *&n)
{
    if (n == nullptr)
        return;
    destroy(n->l);
    destroy(n->r);
    delete n;
}

template<typename T>
int avltree<T>::bf(avltree::node *&n)
{
    if(n->l != nullptr && n->r != nullptr){
        return n->l->h - n->r->h;
    }
    else if(n->l != nullptr && n->r == nullptr){
        return n->l->h;
    }
    else if(n->l == nullptr && n->r != nullptr ){
        return -(n->r->h);
    }
}

template<typename T>
typename avltree<T>::node *avltree<T>::rightRotate(avltree::node *&n)
{
    auto nl = n->l;
    n->l = nl->r;
    nl->r = n;

    if (nl->l != nullptr)
        nl->l->h = ch(nl->l);
    if (nl->r != nullptr)
        nl->r->h = ch(nl->r);
    nl->h = ch(nl);

    return nl;
}

template<typename T>
typename avltree<T>::node *avltree<T>::leftRotate(avltree::node *&n)
{
    auto nr = n->r;
    n->r = nr->l;
    nr->l = n;

    if (nr->l != nullptr)
        nr->l->h = ch(nr->l);
    if (nr->r != nullptr)
        nr->r->h = ch(nr->r);
    nr->h = ch(nr);

    return nr;
}

template<typename T>
int avltree<T>::ch(avltree::node *&n)
{
    if(n->l != nullptr && n->r != nullptr)
        if (n->l->h < n->r->h)
            return n->r->h + 1;
        else
            return  n->l->h + 1;
    else if(n->l != nullptr && n->r == nullptr)
        return n->l->h + 1;
    else if(n->l == nullptr && n->r != nullptr)
        return n->r->h + 1;
    return 1;
}

template<typename T>
void avltree<T>::print(const std::string& prefix, const node* n, bool isLeft, std::ostream &ost)
{
    if( n != nullptr )
    {
        ost << prefix;

        if (n==root)
            ost << "> ";
        else
            ost << (isLeft ? "├── " : "└── " );

        // print the value of the node
        std::cout << n->h << "[" << n->val << "]" << std::endl;

        // enter the next tree level - left and right branch
        print( prefix + (isLeft ? "│   " : "    "), n->l, true, ost);
        print( prefix + (isLeft ? "│   " : "    "), n->r, false, ost);
    }
}

template class avltree<int8_t>;
template class avltree<int16_t>;
template class avltree<int32_t>;
template class avltree<int64_t>;
template class avltree<uint8_t>;
template class avltree<uint16_t>;
template class avltree<uint32_t>;
template class avltree<uint64_t>;
template class avltree<double>;
template class avltree<float>;
