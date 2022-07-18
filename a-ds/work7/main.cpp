#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using type=int;
using matrix=std::vector<std::vector<type>>;
using row=std::vector<type>;

class graph
{
public:
    explicit graph(std::ifstream &ist) {m = get(ist);};
    ~graph() = default;
    void print(std::ostream &ost)
    {
        for (int i = 0; i < m.size(); i++)
        {
            for (int j = 0; j < m.at(0).size(); j++)
            {
                ost << m[i][j] << " ";
            }
            ost << "\n";
        }
    }
    uint max_shortest(uint sv)
    {
        auto v = dijkstra(sv);
        return *std::max_element(v.begin(), v.end());
    }

private:
    matrix m;
    static matrix get(std::ifstream &ist)
    {
        int size;
        ist >> size;
        matrix v;
        for (int i = 0; i < size; i++)
        {
            auto *r = new row;
            v.push_back(*r);
            for (int j = 0; j < size; j++)
            {
                int buf;
                ist >> buf;
                v[i].push_back(buf);
            }
        }
        return v;
    }

    std::vector<int> dijkstra(uint &sv)
    {
        int size = m.size();
        int curr;

        struct vertex {bool used; int d;};
        std::vector<vertex> v (size, vertex{.used = false, .d = -1});
        v[sv].d = 0;

        for (int i=0; i < size; i++)
        {
            int min=std::numeric_limits<type>::max();
            for (int j=0; j < size; j++)
            {
                if (!v[j].used && v[j].d < min && v[j].d != -1)
                {
                    min=v[j].d;
                    curr=j;
                }
            }
            v[curr].used = true;
            for(int j=0;j<size;j++)
            {
                if (m[curr][j] == 1 && (v[j].d > v[curr].d + m[curr][j] or v[j].d == -1))
                {
                    v[j].d = v[curr].d + m[curr][j];
                }
            }
        }
        std::vector<int> ret(size);
        curr = 0;
        for (auto &it : ret)
        {
            it = v[curr++].d;
        }
        return ret;
    }
};

int main()
{
    std::ifstream ist;
    ist.open("/home/yaroslav/repos/a-ds/work7/matrix");
    if (!ist.is_open())
        std::cerr << "Unable to open file.\n";

    graph g(ist);
    uint v;
    std::cout << "enter vertex: ";
    std::cin >> v;

    std::cout << "maximum shortest path from " << v  << ": "<< g.max_shortest(v) << "\n";
    return 0;
}
