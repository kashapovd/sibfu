/**
 * @brief control task
 * @file def/main.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include <iostream>
#include <queue>
#include <limits>
#include <random>
#include <chrono>

#define timer_start (std::chrono::high_resolution_clock::now())
#if defined timer_start
#define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::milliseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif

double averageMax3(std::queue<int32_t> &q)
{
    const uint8_t n = 3;
    int32_t max3[n];
    for (uint8_t i=0; i < n; i++)
    {
        max3[i] = std::numeric_limits<int32_t>::min();
        for (uint64_t j=0; j < q.size(); j++)
        {
            auto elem = q.front();
            q.push(elem);
            q.pop();
            if (i != 0)
            {
                if (elem >= max3[i-1])
                {
                    continue;
                }
            }
            if (max3[i] < elem)
            {
                max3[i] = elem;
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

void removeLessAX(std::queue<int32_t> &q, float &a)
{
    auto ax = a * averageMax3(q);
    for (uint64_t i=0; i < q.size(); i++)
    {
        auto elem = q.front();
        if (elem < ax)
        {
            i--;
        } else
            {
                q.push(elem);
            }
        q.pop();
    }
}

void fill(std::queue<int32_t> &q, uint64_t size)
{
    std::mt19937 generator(time(nullptr));
    std::uniform_int_distribution<int32_t> distribution( // [-2^31, 2^31 - 1]
            std::numeric_limits<int32_t>::min(),
            std::numeric_limits<int32_t>::max());
    for (uint64_t i = 0; i < size; i++)
    {
        int32_t num = distribution(generator);
        q.push(num);
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

    std::queue<int32_t> q;
    fill(q, size);

    auto timer = timer_start;
    removeLessAX(q, a);
    auto elapsed = timer_elapsed(timer);
    std::cout << "\n";
    std::cout << "Size of array: " << q.size() << "\n";
    std::cout << size - q.size() << " elements " << "was deleted\n" ;
    std::cout << "computing time: " << elapsed << " milliseconds"<< "\n";

    return 0;
}
