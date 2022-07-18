#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>
#include <bitset>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

std::vector<uint> primes;
char **stacks;
uint *par;

int checkPrime(void *num) {
    auto n = *(uint*)num;
    if (n == 1) {
        primes.push_back(n);
        return 0;
    }
    for(int i = 2; i <= n/2; i++) {
        if(n % i == 0) {
            return 0;
        }
    }
    primes.push_back(n);

    return 0;
}

void calcPrimes(int a, int b) {
    stacks = new char*[b-a+1];
    par = new uint[b-a+1];
    for(int i=a; i <= b; i++) {
        par[i] = i;
        char *stackTop;
        stacks[i] = new char[STACK_SIZE];
        stackTop = stacks[i] + STACK_SIZE;
        clone(checkPrime, (void *)stackTop, CLONE_VM|CLONE_VFORK, (void *)(&par[i]));
    }

}

int main() {
    std::string astr, bstr;
    std::cout << "Insert A(<B) palindrome: ";
    std::cin >> astr;
    std::cout << "Insert B(>A) palindrome: ";
    std::cin >> bstr;

    std::bitset<32> aBinNum(astr);
    int a = aBinNum.to_ulong();
    std::bitset<32> bBinNum(bstr);
    int b = bBinNum.to_ulong();
    std::cout << "a: " << a << " b: " << b << "\n";

    calcPrimes(a, b);

    std::cout << "sum of primes from [A, B]: " << std::accumulate(primes.begin(), primes.end(), 0);
    return 0;
}
