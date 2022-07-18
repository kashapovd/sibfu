/**
 * @brief header for the htable class
 * @file htable.h
 * @author Kashapov Yaroslav
 * @date 2020
*/

#ifndef WORK4_HTABLE_H
#define WORK4_HTABLE_H

#include <vector>
#include <fstream>

class htable {

public:
    struct entry {bool empty; int value;};
    htable();
    ~htable();
    int capacity() const;
    int size() const;
    int print(std::ostream &);
    void add(int);
    int remove(int);
    void load_file(std::ifstream &, const std::string &);
    void clear();
    int search(int num);
private:

    static int hash(int);
    void trim();
    int _size;
    using vec=std::vector<entry>;
    vec *table;
    entry* retrieve(int);

};

#endif //WORK4_HTABLE_H
