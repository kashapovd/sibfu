/**
 * @brief chain hash table with additive hashing implementation
 * @file htable.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include "htable.h"
#include <cmath>

htable::htable()
{
    table = new std::vector<std::list<int>>;
    _size=0;
}

htable::~htable()
{
    delete table;
    table = nullptr;
}

void htable::add(const int num)
{
    int pos = hash(num);
    int need_to_add = pos+1;
    if (!table->empty())
    {
        if (pos >= table->size())
            need_to_add -= int(table->size());
        else
            need_to_add = 0;
    }
    while (need_to_add--)
    {
        auto *e = new std::list<int>;
        table->push_back(*e);
    }
    table->at(pos).push_front(num);
    _size++;
}

int htable::remove(const int num)
{
    std::list<int> *list = &table->at(hash(num));
    auto it = retrieve(num);
    if (list->end() != it && !table->empty())
    {
        list->erase(it);
        trim();
        return --_size;
    }
    return -1;
}

void htable::load_file(std::ifstream &ist, const std::string &p)
{
    if(!ist.is_open()) ist.open(p, std::ifstream::in);
    int size;
    ist >> size;
    while (size--)
    {
        int buff;
        ist >> buff;
        add(buff);
    }
    ist.close();
}

inline int htable::hash(int num)
{
    int r=0;
    while(num)
    {
        r+=std::abs(num)%10;
        num/=10;
    }
    return r;
}

int htable::print(std::ostream &ost) const
{
    for (int i=0; i < table->size(); i++)
    {

        ost << "[" << i << "]: ";
        for (const auto &item : table->at(i)) {
            ost << "<" << item << "> ";
        }
        ost << "\n";
    }
    return _size;
}

std::list<int>::iterator htable::retrieve(const int num) const
{
    std::list<int> *list = &table->at(hash(num));
    for(auto it=list->begin(); it!=list->end(); it++)
        if (*it == num)
            return it;
    return list->end();
}

inline void htable::trim()
{
    while ((table->end()-1)->empty())
    {
        table->erase(table->end()-1);
    }
}

int htable::capacity() const
{
    return table->size();
}

int htable::size() const
{
    return _size;
}

void htable::clear()
{
    table->clear();
    _size=0;
}

int htable::search(int num) const
{
    std::list<int> *list = &table->at(hash(num));
    auto it = retrieve(num);
    if (list->end() != it && !table->empty())
    {
        return num;
    }
    return num+1;
}
