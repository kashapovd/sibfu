#include <cuda_runtime.h>
#include <helper_cuda.h>
#include "tools.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstring>
#include <cassert>
#include <thread>

#define N 160
#define MATRIX_SIZE (N*N)
#define BLOCK_SIZE 32
#define THREADS_PER_BLOCKS 1024

#define timer_start (std::chrono::high_resolution_clock::now())
#if defined timer_start
    #define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::nanoseconds> \
                                (std::chrono::high_resolution_clock \
                                        ::now() - t).count())
#endif

void simple_matrix_mul_cpu(float *matrix_a, float *matrix_b, float *matrix_c, uint64_t n) {
    float sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            float sum = 0.0;
            for (size_t k = 0; k < n; ++k) {
                sum += matrix_a[i*n + k] * matrix_b[k*n + j];
            }
            matrix_c[i*n + j] = sum;
        }
    }
}

__global__ void simple_matrix_mul_gpu(float *matrix_a, float *matrix_b, float *matrix_c, uint64_t n) {
    uint64_t tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < n) {
        uint64_t j = tid / N;
        uint64_t i = tid % N;
        float sum = 0.0;
        for (uint64_t k = 0; k < N; k++) {
            sum += matrix_a[i*N + k] * matrix_b[k*N + j];
        }
        matrix_c[i*N + j] = sum;
    }
}

void HostVsDevice(uint8_t size) {

    float *host_a, *host_b, *host_c, *buff_device_on_host;
    float *device_a, *device_b, *device_c;
    // alloc mem on host
    checkCudaErrors(cudaMallocHost(&buff_device_on_host, MATRIX_SIZE * sizeof(float)));
    checkCudaErrors(cudaMallocHost(&host_a, MATRIX_SIZE * sizeof(float)));
    checkCudaErrors(cudaMallocHost(&host_b, MATRIX_SIZE * sizeof(float)));
    checkCudaErrors(cudaMallocHost(&host_c, MATRIX_SIZE * sizeof(float)));

    // alloc mem on device
    checkCudaErrors(cudaMalloc(reinterpret_cast<void **>(&device_a), MATRIX_SIZE * sizeof(float)));
    checkCudaErrors(cudaMalloc(reinterpret_cast<void **>(&device_b), MATRIX_SIZE * sizeof(float)));
    checkCudaErrors(cudaMalloc(reinterpret_cast<void **>(&device_c), MATRIX_SIZE * sizeof(float)));

    // create cuda events to measure timing 
    cudaEvent_t start, stop;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));

    // init host memory
    fill_random(host_a, MATRIX_SIZE);
    fill_random(host_b, MATRIX_SIZE);

    // copy arrays to device
    checkCudaErrors(cudaMemcpy(device_a, host_a, MATRIX_SIZE * sizeof(float), cudaMemcpyHostToDevice));
    checkCudaErrors(cudaMemcpy(device_b, host_b, MATRIX_SIZE * sizeof(float), cudaMemcpyHostToDevice));

    // exec calc on host
    auto timer = timer_start;
    simple_matrix_mul_cpu(host_a, host_b, host_c, N);
    auto elapsed = timer_elapsed(timer);
    std::cout << "Host calcs took: " << elapsed/1000000.0 << "ms" << std::endl;

    // exec calc on device
    checkCudaErrors(cudaEventRecord(start, 0));
    simple_matrix_mul_gpu <<<BLOCK_SIZE, THREADS_PER_BLOCKS>>> (device_a, device_b, device_c, MATRIX_SIZE);
    checkCudaErrors(cudaEventRecord(stop, 0));
    checkCudaErrors(cudaEventSynchronize(stop));

    float msecTotal = 0.0f;
    cudaEventElapsedTime(&msecTotal, start, stop);
    std::cout << "Device calcs took: " << msecTotal << "ms" << std::endl; 

    // copy calcs from device to host
    checkCudaErrors(cudaMemcpy(buff_device_on_host, device_c, MATRIX_SIZE * sizeof(float), cudaMemcpyDeviceToHost));
    if (compare_array(host_c, buff_device_on_host, MATRIX_SIZE))
        std::cout << "Computed matrixes from device and host are identical" << std::endl;
    else 
        std::cout << "Computed matrixes from device and host aren't identical" << std::endl;

    // set up cache config
    //checkCudaErrors(cudaFuncSetCacheConfig(matrix_mul_gpu, cudaFuncCachePreferShared));

    // checkCudaErrors(cudaEventRecord(start, 0));
    // matrix_mul_gpu <<<dimGrid, dimBlock>>> (device_a, device_b, device_c, N);
    // checkCudaErrors(cudaEventRecord(stop, 0));
    // checkCudaErrors(cudaEventSynchronize(stop));

    // msecTotal = 0.0f;
    // cudaEventElapsedTime(&msecTotal, start, stop);
    // std::cout << "Device calcs took: " << msecTotal << "ms" << std::endl;

    // // copy calcs from device to host
    // checkCudaErrors(cudaMemcpy(buff_device_on_host, device_c, MATRIX_SIZE * sizeof(float), cudaMemcpyDeviceToHost));
    // if (compare_array(host_c, buff_device_on_host, MATRIX_SIZE))
    //     std::cout << "Computed matrixes from device and host are identical" << std::endl;
    // else 
    //     std::cout << "Computed matrixes from device and host aren't identical" << std::endl;

    checkCudaErrors(cudaFree(device_a));
    checkCudaErrors(cudaFree(device_b));
    checkCudaErrors(cudaFree(device_c));

    checkCudaErrors(cudaFreeHost(buff_device_on_host));
    checkCudaErrors(cudaFreeHost(host_a));
    checkCudaErrors(cudaFreeHost(host_b));
    checkCudaErrors(cudaFreeHost(host_c));
}

int main(int argc, char **argv) {
    int devID = findCudaDevice(argc, (const char **)argv);
    cudaSetDevice(devID);
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, devID);
    std::cout << "Device name: " << deviceProp.name << std::endl;
    std::cout << "Multiprocessors: " << deviceProp.multiProcessorCount << std::endl;
    std::cout << "Shared mem per multiprocessor: " << deviceProp.sharedMemPerMultiprocessor/1024.0 << " KB" << std::endl;
    std::cout << "L2 cache size: " << deviceProp.l2CacheSize/1024.0 << " KB" << std::endl;
    std::cout << "Const mem size: " << deviceProp.totalConstMem/1024.0 << " KB" << std::endl;
    std::cout << "Global mem size: " << deviceProp.totalGlobalMem/1073741824.0 << " GB" << std::endl;
    
    HostVsDevice(MATRIX_SIZE);
    return 0;
}