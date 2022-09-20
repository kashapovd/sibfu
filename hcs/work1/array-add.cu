#include "cuda_runtime.h"
#include "tools.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstring>
#include <cassert>


#define ARRAY_SIZE 100000
#define THREADS_PER_BLOCKS 1024

#define timer_start (std::chrono::high_resolution_clock::now())
#if defined timer_start
    #define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::milliseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif

void vector_add_cpu(int32_t *host_a, int32_t *host_b, int32_t *host_c, uint64_t n) {
    uint64_t i;
    for (i = 0; i < n; ++i)
        host_c[i] = host_a[i] + host_b[i];
}


__global__ void vector_add_gpu(int32_t *device_a, int32_t *device_b, int32_t *device_c, uint64_t n) {
    int i =  blockDim.x * blockIdx.x + threadIdx.x;
    if (i < n)
        device_c[i] = device_a[i] + device_b[i];
}

int main() {

    int32_t *host_a, *host_b, *host_c;
    int32_t *device_a, *device_b, *device_c;

    // malloc mem on host
    host_a = (int32_t *)malloc(ARRAY_SIZE * sizeof(int32_t));
    host_b = (int32_t *)malloc(ARRAY_SIZE * sizeof(int32_t));
    host_c = (int32_t *)malloc(ARRAY_SIZE * sizeof(int32_t));

    // malloc mem on device
    auto r = cudaMalloc(&device_a, ARRAY_SIZE * sizeof(int32_t));
    assert((r == cudaError::cudaSuccess));
    r = cudaMalloc(&device_a, ARRAY_SIZE * sizeof(int32_t));
    assert((r == cudaError::cudaSuccess));
    r = cudaMalloc(&device_a, ARRAY_SIZE * sizeof(int32_t));
    assert((r == cudaError::cudaSuccess));

    fill_random(host_a, ARRAY_SIZE);
    fill_random(host_b, ARRAY_SIZE);

    cudaMemcpy(device_a, host_a, ARRAY_SIZE * sizeof(int32_t), cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, host_b, ARRAY_SIZE * sizeof(int32_t), cudaMemcpyHostToDevice);

    auto timer = timer_start;
    vector_add_cpu(host_a, host_b, host_c, ARRAY_SIZE);
    auto elapsed = timer_elapsed(timer);
    std::cout << "vector_add_cpu_int: " << elapsed << " seconds" << std::endl;

    auto blocks = (ARRAY_SIZE + THREADS_PER_BLOCKS - 1) / THREADS_PER_BLOCKS;
    timer = timer_start;
    vector_add_gpu <<<blocks, THREADS_PER_BLOCKS>>> (device_a, device_b, device_c, ARRAY_SIZE);
    cudaDeviceSynchronize();
    elapsed = timer_elapsed(timer);
    std::cout << "vector_add_gpu_int: " << elapsed << " seconds" << std::endl;

    auto buff_device_on_host = (int32_t *)malloc(ARRAY_SIZE * sizeof(int32_t));
    cudaMemcpy(buff_device_on_host, device_c, ARRAY_SIZE * sizeof(int32_t), cudaMemcpyDeviceToHost);
    if (compare_array(host_c, buff_device_on_host, ARRAY_SIZE))
        std::cout << "Computed arrays from device and host are identical" << std::endl;
    else 
        std::cout << "Computed arrays from device and host aren't identical" << std::endl;

    cudaFree(device_a);
    cudaFree(device_b);
    cudaFree(device_b);

    free(host_a);
    free(host_b);
    free(host_c);

    return 0;
}