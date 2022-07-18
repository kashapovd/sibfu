/**
 * @brief work2. Linear Data Structures
 * @file main.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include <iostream>
#include <random>
#include <chrono>

#include "list.h"
#include "array.h"

#define timer_start (std::chrono::high_resolution_clock::now())
#if defined timer_start
    #define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::milliseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif

template <class T>
void print(T &arr)
{
    std::cout << "array:\n";
    if (arr.isEmpty()) std::cout << arr.typeName() << " is empty\n";
    for (uint64_t i=0; i < arr.size() and !arr.isEmpty(); i++)
    {
        std::cout << i <<". <" << arr[i] << ">\n";
    }
    std::cout << std::endl;
}

template<typename T>
void removeLessAX(T &arr, float &a) {
    auto ax = a * averageMax3(arr);
    for (uint64_t i=0; i < arr.size(); i++)
    {
        if ((double)arr[i] < ax)
        {
            arr.remove(i);
            i--;
        }
    }
}

template <class T>
double averageMax3(T &arr)
{
    const int n = 3;
    int32_t max3[n];
    for (int i=0; i < n; i++)
    {
        max3[i] = std::numeric_limits<int32_t>::min();
        for (uint64_t j=0; j < arr.size(); j++)
        {
            if (i != 0)
            {
                if (arr[j] >= max3[i-1])
                {
                    continue;
                }
            }
            if (max3[i] < arr[j])
            {
                max3[i] = arr[j];
            }
        }
    }
    int64_t sum=0;
    for (int32_t &i : max3)
    {
         sum += i;
    }
    return static_cast<double>(sum/3.0);
}

void fill(array &arr, list &list, uint64_t &size)
{
    std::mt19937 generator(time(nullptr));
    //std::mt19937 generator(0);
    std::uniform_int_distribution<int32_t> distribution( // [-2^31, 2^31 - 1]
            std::numeric_limits<int32_t>::min(),
            std::numeric_limits<int32_t>::max());
    for (uint64_t i = 0; i < size; i++)
    {
        int32_t num = distribution(generator);
        arr[i] = num;
        list.push_back(num);
    }
}

int main()
{
    float a=0;
    std::cout << "A = ";
    std::cin >> a;

    uint64_t size=0;
    std::cout << "Array and list size:= ";
    std::cin >> size;

    array array(size);
    list list;

    fill(array, list, size);

    auto timer = timer_start;
    removeLessAX(array, a);
    auto elapsed = timer_elapsed(timer);
    std::cout << "\n";
    std::cout << "Size of array: " << array.size() << "\n";
    std::cout << size - array.size() << " elements " << "was deleted\n" ;
    std::cout << "computing time: " << elapsed << " seconds"<< "\n";

    timer = timer_start;
    removeLessAX(list, a);
    elapsed = timer_elapsed(timer);
    std::cout << "-------\n";
    std::cout << "Size of double linked list: " << list.size() << "\n";
    std::cout << size - list.size() << " elements " << "was deleted\n" ;
    std::cout << "computing time: " << elapsed << " seconds" << std::endl;

    return 0;
}
