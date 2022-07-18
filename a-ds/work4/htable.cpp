/**
 * @brief hash table with opening addressing and additive hash implementation
 * @file htable.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include "htable.h"
#include <cmath>

htable::htable()
{
    table = new vec;
    _size=0;
}

htable::~htable()
{
    delete table;
    table = nullptr;
}

void htable::add(int num)
{
    int pos = hash(num);
    int need_to_add = pos+1;

    if (!table->empty())
    {
        need_to_add-=int(table->size());
        for (; pos < table->size(); pos++)
        {
            if (table->at(pos).empty)
            {
                need_to_add=0;
                break;
            }
            need_to_add=1;
        }
    }

    while(need_to_add--)
    {
        auto *e = new entry;
        e->empty=true;
        table->push_back(*e);
    }
    table->at(pos) = {.empty=false, .value=num};
    _size++;
}

int htable::remove(const int num)
{
    entry *e = retrieve(num);
    if (e)
    {
        e->empty=true;
        trim();
        return _size--;
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

int htable::print(std::ostream &ost)
{
    int i=0;
    for (const auto &item : *table)
        //if(!item.empty)
            ost << (item.empty ? "*" : "") << "entry[" << i++ << "]: " << item.value << "\n";
    return size();
}

htable::entry *htable::retrieve(const int num)
{
    for (int i = hash(num); i < table->size(); i++)
    {
        if (table->at(i).value == num && !table->at(i).empty)
            return &table->at(i);
    }
    return nullptr;
}

inline void htable::trim()
{
    while ((table->end()-1)->empty)
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

int htable::search(int num)
{
    for (int i = hash(num); i < table->size(); i++)
    {
        if (table->at(i).value == num && !table->at(i).empty)
            return table->at(i).value;
    }
    return num-1;
}
