/**
 * @brief small array implementation
 * @file array.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include "array.h"

array::array(uint64_t &size) : _size(size)
{
    first = new int32_t [size];
}

void array::remove(uint64_t idx)
{
    if (!_size && (idx >= _size)) return;
    for (uint64_t i = idx; i < _size-1; i++)
    {
        *(first+i) = *(first+i+1);
    }
    _size--;
}

array::~array()
{
    delete[] first;
    first = nullptr;
}

uint64_t array::size() const
{
    return _size;
}

int32_t& array::operator[](const uint64_t &idx)
{
    if (idx >= _size) return *first;
    return *(first+idx);
}

bool array::isEmpty()
{
    return !static_cast<bool>(size());
}
