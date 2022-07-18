#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#define QSRAND 1
#define VRAND 0

#define timer_start (std::chrono::high_resolution_clock::now())
#ifdef timer_start
#define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::microseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif

namespace instertionsort {
    template<typename T>
    std::vector<T> insertionsort(std::vector<T> v)
    {
        for (int j, i = 1; i < v.size(); i++)
        {
            T key = v[i];
            for (j = i; j > 0 && v[j - 1] > key; j--)
                v[j] = v[j - 1];
            v[j] = key;
        }
        return v;
    }
}

namespace shellsort {
    template <typename T>
    std::vector<T> shellsort(std::vector<T> v)
    {
        for (uint step = v.size()/2; step > 0; step/=2)
        {
            for (int j, i=step; i < v.size(); i++)
            {
                T key = v[i];
                for (j = int(i-step); j >= 0 && v[j] > key; j-=step)
                    v[j+step] = v[j];
                v[j+step] = key;
            }
        }
        return v;
    }
}

namespace selectionsort
{
    template<typename T>
    std::vector<T> selectionsort(std::vector<T> v)
    {
        for (uint i = 0; i < v.size(); i++)
        {
            uint m_idx = i;
            for (uint j = i + 1; j < v.size(); j++)
                if (v[j] < v[m_idx])
                    m_idx = j;
            std::swap(v[i], v[m_idx]);
        }
        return v;
    }
}

namespace quicksort
{
    template<typename T>
    uint qpart(std::vector<T> &v, uint &l, uint &r)
    {
        T p = v[l];
        uint i = l + 1;
        for (uint j = l + 1; j <= r; j++)
            if (v[j] < p)
                std::swap(v[j], v[i++]);
        std::swap(v[l], v[i - 1]);
        return i-1;
    }

    uint chpivot(uint &l, uint &r)
    {
        std::mt19937 generator(time(nullptr));
        std::uniform_int_distribution<uint> distribution(l,r);
        return distribution(generator);
    }

    template<typename T>
    uint chpivot(std::vector<T> &v, uint &l, uint &r)
    {
        uint imin=l, imax = l;
        for (int i=l; i <= r; i++)
        {
            if (v[imax] < v[i])
                imax = i;
            if (v[i] < v[imin])
                imin = i;
        }
        T median = (v[imax] - v[imin])/2 + v[imin];
        for (uint i=1; i < v.size(); i++)
            if (v[i] > v[imin] && v[i] <= median)
                imin = i;
        return imin;
    }

    template<typename T>
    void qsort(std::vector<T> &v, uint l, uint r)
    {
        if (l >= r)
            return;
#if(QSRAND==0)
        uint i = chpivot(v, l, r); //O(n)
#else
        uint i = chpivot(l, r); //O(1)
#endif
        std::swap(v[l], v[i]);
        uint j = qpart(v, l, r);
        if (j != 0)
            qsort(v, l, j-1);
        if (j != v.size()-1)
            qsort(v, j+1, r);
    }

    template<typename T>
    std::vector<T> qsort(std::vector<T> v)
    {
        qsort(v, 0, v.size()-1);
        return v;
    }
}

template <typename T>
void print(const std::vector<T> &v)
{
    std::cout << "\n\tsorted seq: [ ";
    for (const auto &it : v)
    {
        std::cout << "<" << it  << "> ";
    }
    std::cout << "]\n";
}

template <typename T>
void fill(std::vector<T> &v, uint size)
{
    std::mt19937 generator(time(nullptr));
    //std::mt19937 generator(0);
    std::uniform_int_distribution<T> distribution(
            std::numeric_limits<T>::min(),
            std::numeric_limits<T>::max());
    for (uint64_t i = size; i > 0; i--)
    {
        int32_t num = distribution(generator);
        v.push_back(num);
    }
}


int main()
{
#if(VRAND==1)
    std::vector<int> v;
    fill(v,10000);
#else
    std::vector<int> v {-1, 7, 3, 210, -10, 1, 1, 2, 3, 10, 20, 2, 5, 6, 1, 0, 8, 4, 11, 12,7};
    //std::vector<int> v {1, 2, 3, 4, 5};
#endif

    //std::cout << "\n<<insertion sort>>";
    //print(instertionsort::insertionsort(v));

    std::cout << "\n<<Shell sort>>";
    auto timer = timer_start;
    print(shellsort::shellsort(v));
    auto elapsed = timer_elapsed(timer);
    std::cout << elapsed << std::endl;

    //std::cout << "\n<<selection sort>>";
    //print(selectionsort::selectionsort(v));

    std::cout << "\n<<quick sort>>";
    timer = timer_start;
    print(quicksort::qsort(v));
    elapsed = timer_elapsed(timer);
    std::cout << elapsed << std::endl;

    return 0;
}
