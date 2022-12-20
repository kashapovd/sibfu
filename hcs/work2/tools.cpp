#include <cstdint>
#include <random>

#define EPS 0.01

static std::random_device rd;
static std::mt19937 generator{rd()};

void fill_random(float *arr, uint64_t size) {
    std::uniform_real_distribution<float> distribution(
        -10.0,
        10.0
    );
    for (uint64_t i = 0; i < size; i++) {
        float num = distribution(generator);
        arr[i] = num;
    }
}

bool compare_floats(float &a, float &b) {
    if (fabs(a - b) < EPS)
        return true;
    return false;
}

bool compare_array(float *a, float *b, uint64_t size) {
    for (uint64_t i=0; i<size; i++) {
        if (!compare_floats(a[i], b[i]))
            return false;
    }
    return true;
}

void printMatrix(float *a, uint64_t n, std::ostream &ost) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            ost << a[i*n + j] << " ";
        }
        ost << "\n";
    }
}