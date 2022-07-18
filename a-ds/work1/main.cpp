/**
 * @brief work1. Analysis of algorithms
 * @file main.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include <iostream>
#include <sys/resource.h>
#include <QElapsedTimer> // timer start() and elapsed()

// time complexity: O(n)
// space complexity: O(1)
uint64_t compute_num_seq(uint64_t &n);

// time complexity: O(n)
// space complexity: O(n)
uint64_t compute_num_seq_r(uint64_t n);

int main()
{
    uint64_t n = 0;
    std::cout << "N: ";
    std::cin >> n;

    // 1GB stack able to call ~33550000 compute_num_seq_r (for clarity of results:>)
    // 8MB stack able to call 261949 compute_num_seq_r
    const rlim_t stacksize = 1024 * 1024 * 1024;
    struct rlimit rl;
    int r = getrlimit(RLIMIT_STACK, &rl);
    if (!r)
    {
        rl.rlim_cur = stacksize;
        setrlimit(RLIMIT_STACK, &rl);
    }
    std::cout << "size of stack: "<< rl.rlim_cur << "\n\n";

    QElapsedTimer timer;
    timer.start();
    std::cout << "Sum of the first N elements via cycles: " << compute_num_seq(n) << "\n";
    std::cout << "computing took " << timer.elapsed() << " milliseconds\n\n";

    timer.restart();
    std::cout << "Sum of the first N elements via recursion: " << compute_num_seq_r(n) << std::endl;
    std::cout << "computing took " << timer.elapsed() << " milliseconds\n" << std::endl;
    return 0;
}


uint64_t compute_num_seq(uint64_t &n)
{
    uint64_t result = 0;
    for (uint64_t i = 1; i <= n; i++)
    {
        result += i;
    }
    return result;
}

uint64_t compute_num_seq_r(uint64_t i)
{
    if (i == 0)
    {
        return 0;
    }
    return compute_num_seq_r(i-1) + i;
}




