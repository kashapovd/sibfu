#include <cstdint>
#include "bintree.h"

template <typename T>
bintree<T>::bintree()
{
    size=0;
    root = nullptr;
}

template<typename T>
bintree<T>::~bintree()
{
    destroy(root);
    root = nullptr;
}

template <typename T>
void bintree<T>::add(T val) { add(val, root); }

template<typename T>
void bintree<T>::add(T &val, bintree::node *&n)
{
    if (n == nullptr)
    {
        n = node_alloc(val);
        size++;
    }
    else if (val < n->val)
        add(val, n->l);
    else if (val > n->val)
        add(val, n->r);
}

template<typename T>
bool bintree<T>::remove(T val)
{
    return static_cast<bool>(remove(val, root));
}

template<typename T>
typename bintree<T>::node *bintree<T>::remove(T &val, bintree::node *&n)
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
            if(n->l == nullptr)
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
            }
            else
                {
                    auto min_n = min(n->r);
                    n->val = min_n->val;
                    remove(min_n->val, n->r);
                }
        }
    return ret;
}

template<typename T>
inline typename bintree<T>::node* bintree<T>::node_alloc(T &val)
{
    node *n = new node;
    n->val = val;
    n->l = n->r = nullptr;
    return n;
}

template<typename T>
void bintree<T>::removeLess(double val)
{
    removeLess(val, root);
}

template<typename T>
void bintree<T>::removeLess(double &val, bintree::node *&n)
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
bool bintree<T>::search(T val) { return static_cast<bool>(search(val, root)); }

template<typename T>
typename bintree<T>::node* bintree<T>::search(T &val, bintree::node *&n)
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
T bintree<T>::max() { return max(root)->val; }

template<typename T>
typename bintree<T>::node *bintree<T>::max(node *mn)
{
    while (mn->r != nullptr)
        mn = mn->r;
    return mn;
}

template<typename T>
T bintree<T>::min() { return min(root)->val; }

template<typename T>
typename bintree<T>::node *bintree<T>::min(node *mn)
{
    while (mn->l != nullptr)
        mn = mn->l;
    return mn;
}

template<typename T>
void bintree<T>::print(std::ostream &ost) { print("", root, false, ost); }

template<typename T>
void bintree<T>::print(const std::string& prefix, const node* n, bool isLeft, std::ostream &ost)
{
    if( n != nullptr )
    {
        ost << prefix;

        if (n==root)
            ost << "> ";
        else
            ost << (isLeft ? "├── " : "└── " );

        // print the value of the node
        ost << "[" << n->val << "]" << std::endl;

        // enter the next tree level - left and right branch
        print( prefix + (isLeft ? "│   " : "    "), n->l, true,  ost);
        print( prefix + (isLeft ? "│   " : "    "), n->r, false, ost);
    }
}

template<typename T>
void bintree<T>::destroy(node *&n)
{
    if (n == nullptr)
        return;
    destroy(n->l);
    destroy(n->r);
    delete n;
}

template class bintree<int8_t>;
template class bintree<int16_t>;
template class bintree<int32_t>;
template class bintree<int64_t>;
template class bintree<uint8_t>;
template class bintree<uint16_t>;
template class bintree<uint32_t>;
template class bintree<uint64_t>;
template class bintree<double>;
template class bintree<float>;