#include <cstdint>
#include <random>

void fill_random(int32_t *arr, uint64_t size)
{
    std::mt19937 generator(time(nullptr));
    //std::mt19937 generator(0);
    std::uniform_int_distribution<int32_t> distribution(
            std::numeric_limits<int32_t>::min(),
            std::numeric_limits<int32_t>::max());
    for (uint64_t i = 0; i < size; i++)
    {
        int32_t num = distribution(generator);
        arr[i] = num;
    }
}

// void fill_random(double &arr, uint64_t &size)
// {
//     std::mt19937 generator(time(nullptr));
//     //std::mt19937 generator(0);
//     std::uniform_int_distribution<double> distribution(
//             std::numeric_limits<double>::min(),
//             std::numeric_limits<double>::max());
//     for (uint64_t i = 0; i < size; i++)
//     {
//         double num = distribution(generator);
//         arr[i] = num;
//     }
// }

bool compare_array(int32_t *a, int32_t *b, uint64_t size) {
    for (uint64_t i=0; i<size; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}