/**
 * @brief List implementation
 * @file list.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include "list.h"

#include <cmath>
#include <limits>

list::list()
{
    last = first =  nullptr;
    _size = 0;
}

list::~list()
{
    if(!_size)
    {
        for (uint64_t i=0; i< _size; i++)
        {
            remove(i);
        }
    }
}

void list::remove(uint64_t idx)
{
    if (!_size && (idx >= _size)) return;
    node::node* curr = inode(idx);

    if (curr->prev == nullptr)
        first = curr->next;
    else
        curr->prev->next=curr->next;

    if (curr->next == nullptr)
        last = curr->prev;
    else
        curr->next->prev= curr->prev;

    curr->prev = nullptr;
    curr->next = nullptr;

    delete curr;
    _size--;
}

void list::push_back(int32_t &val)
{
    if (_size == std::numeric_limits<uint64_t>::max()) return;
    _size++;
    auto *node = new node::node {val, nullptr, nullptr};
    if (first == nullptr)
    {
        last = first = node;
        return;
    }
    node->prev = last;
    last->next = node;
    last = node;
}

uint64_t list::size() const
{
    return _size;
}

int32_t& list::operator[](uint64_t idx)
{
    return inode(idx)->val;
}

node::node* list::inode(uint64_t idx)
{
    if(!_size) return nullptr;
    uint64_t from_end = _size-1 - idx;
    uint64_t distance = std::min(idx, from_end);

    node::node *it;
    bool toForward;

    if (idx > from_end)
    {
        toForward = false;
        it = last;
    }
    else
        {
            toForward = true;
            it = first;
        }

    for (uint64_t i=0; i < distance; i++)
    {
        if(toForward)
            it = it->next;
        else
            it = it->prev;
    }
    return it;
}

bool list::isEmpty()
{
    return !static_cast<bool>(size());
}
