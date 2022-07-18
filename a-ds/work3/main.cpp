/**
 * @brief work2. Search algorithms
 * @file main.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

#define timer_start (std::chrono::high_resolution_clock::now())
#ifdef timer_start
#define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::microseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif

using vec = std::vector<std::string>;
vec *creat_sec(std::istream &in)
{
    int size;
    in >> size;
    vec *v = new vec;
    for (int i=0; i < size and !in.eof() and !in.fail(); i++)
    {
        std::string buff;
        in >> buff;
        v->push_back(buff);
    }
    return v;
}

int lsearch(vec *v, const std::string& str)
{
    for (int i=0; i < v->size(); i++)
    {
        if (str == v->at(i))
        {
            return i;
        }
    }
    return -1;
}

int bsearch(vec *v, const std::string &str)
{
    if (v->front() <= str and v->back() >= str)
    {
        int s = 0;
        int f = (int)v->size() - 1;
        while (s < f)
        {
            int m = s + (f - s) / 2;
            if (str == v->at(m)) {
                return m;
            }
            if (str <= v->at(m)) {
                f = m - 1;
            } else {
                s = m + 1;
            }
        }
        if (v->at(f) == str) {
            return f;
        }
    }
    return -1;
}

int main()
{
    std::ifstream in ("/home/yaroslav/repos/a-ds/work3/tests/scba2.txt", std::ifstream::in);
    vec v(*creat_sec(in));
    if (!std::is_sorted(v.begin(), v.end()))
        std::sort(v.begin(), v.end());

    vec sv(v);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(sv.begin(), sv.end(), g);

    std::cout << "vector size: " << v.size() << "\n\n";
    std::cout << "<<<<binary search>>>>\n";
    auto timer = timer_start;
    int i = bsearch(&v, v[0]);
    auto elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the first element " << "\"" << v[0] << "\"" << " at " << i
            << " took " << elapsed << " micros\n";

    timer = timer_start;
    i = bsearch(&v, v[v.size()/2]);
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the middle element " << "\"" << v[v.size()/2] << "\"" << " at " << i
            << " took " << elapsed << " micros\n";

    timer = timer_start;
    i = bsearch(&v, v[v.size()-1]);
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the last element " << "\"" << v[v.size()-1] << "\"" << " at " << i
            << " took " << elapsed << " micros\n";

    timer = timer_start;
    for (const auto &it : v)
    {
        bsearch(&v, it);

    }
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch all elements from shuffle took " << elapsed << " micros\n\n";

    std::cout << "<<<<linear search>>>>\n";
    timer = timer_start;
    i = lsearch(&v, v[0]);
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the first element " << "\"" << v[0] << "\"" << " at " << i
            << " took " << elapsed << " micros\n";

    timer = timer_start;
    i = lsearch(&v, v[v.size()/2]);
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the middle element " << "\"" << v[v.size()/2] << "\"" << " at " << i
            << " took " << elapsed << " micros\n";

    timer = timer_start;
    i = lsearch(&v, v[v.size()-1]);
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the last element " << "\"" << v[v.size()-1] << "\"" << " at " << i
            << " took " << elapsed << " micros\n";

    timer = timer_start;
    for (const auto &it : v)
    {
        lsearch(&v, it);
    }
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch all elements from shuffle took " << elapsed << " micros\n";
    return 0;
}
