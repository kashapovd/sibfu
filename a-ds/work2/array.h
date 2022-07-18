/**
 * @brief header of "array" class
 * @file array.h
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include <cstdint>
#include <string>

#ifndef WORK2_ARRAY_H
#define WORK2_ARRAY_H

class array {
public:
    explicit array(uint64_t &size);
    ~array();
    void remove(uint64_t idx);
    uint64_t size() const;
    int32_t& operator[](const uint64_t &idx);
    bool isEmpty();

private:
    uint64_t _size;
    int32_t *first;
};


#endif //WORK2_ARRAY_H
