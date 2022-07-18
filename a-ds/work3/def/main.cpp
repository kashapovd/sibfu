/**
 * @brief work3. control task
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

class string : public std::string
{
public:
    using std::string::string;
    uint represent_n() const
    {
        uint n=0;
        int r = int(this->size()-1);
        for (auto &it : *this)
        {
            n += uint(this->at(this->size()-1-r)
                    * std::pow(26, r)); // from 26 to 10 notation
            r--;
        }
        return n;
    }
};

using vec = std::vector<string>;

bool cmp(const string &str1, const string &str2)
{
    return str1.represent_n() < str2.represent_n();
}

vec *creat_sec(std::istream &in)
{
    uint size;
    in >> size;
    vec *v = new vec;
    for (int i=0; i < size and !in.eof() and !in.fail(); i++)
    {
        string buff;
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

int isearch(vec *v, const string &str)
{
    if (v->front().represent_n() <= str.represent_n() and
            v->back().represent_n() >= str.represent_n())
    {
        uint s = 0;
        uint f = (unsigned int)v->size() - 1;
        while (s < f)
        {
            uint m = s + (str.represent_n() - v->at(s).represent_n())
                    *(f - s)/(v->at(f).represent_n() - v->at(s).represent_n());
            if (str == v->at(m)) {
                return m;
            }
            if (str.represent_n() <= v->at(m).represent_n()) {
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
    std::sort(v.begin(), v.end(), cmp);

    vec sv(v);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(sv.begin(), sv.end(), g);

    std::cout << "vector size: " << v.size() << "\n\n";
    std::cout << "<<<<interpolation search>>>>\n";
    auto timer = timer_start;
    int i = isearch(&v, v[0]);
    auto elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the first element " << "\"" << v[0] << "\"" << " at " << i
              << " took " << elapsed << " micros\n";

    timer = timer_start;
    i = isearch(&v, v[v.size()/2]);
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the middle element " << "\"" << v[v.size()/2] << "\"" << " at " << i
              << " took " << elapsed << " micros\n";

    timer = timer_start;
    i = isearch(&v, v[v.size()-1]);
    elapsed = timer_elapsed(timer);
    std::cout << "\tsearch the last element " << "\"" << v[v.size()-1] << "\"" << " at " << i
              << " took " << elapsed << " micros\n";

    timer = timer_start;
    for (const auto &it : v)
    {
        isearch(&v, it);

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
