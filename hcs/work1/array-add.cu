#include <cuda_runtime.h>
#include <cuda_profiler_api.h>
#include <helper_cuda.h>
#include "tools.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstring>
#include <cassert>

#define INIT_ARRAY_SIZE 100
#define THREADS_PER_BLOCKS 1024

#define timer_start (std::chrono::high_resolution_clock::now())
#if defined timer_start
    #define timer_elapsed(t) (std::chrono::duration_cast \
                                <std::chrono::nanoseconds> \
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

void HostVsDevice(size_t size, std::ostream &ost) {
    auto device_blocks = (size + THREADS_PER_BLOCKS - 1) / THREADS_PER_BLOCKS;

    int32_t *host_a, *host_b, *host_c, *buff_device_on_host;
    int32_t *device_a, *device_b, *device_c;

    // alloc mem on host
    checkCudaErrors(cudaMallocHost(&buff_device_on_host, size * sizeof(int32_t)));
    checkCudaErrors(cudaMallocHost(&host_a, size * sizeof(int32_t)));
    checkCudaErrors(cudaMallocHost(&host_b, size * sizeof(int32_t)));
    checkCudaErrors(cudaMallocHost(&host_c, size * sizeof(int32_t)));

    // alloc mem on device
    checkCudaErrors(cudaMalloc(reinterpret_cast<void **>(&device_a), size * sizeof(int32_t)));
    checkCudaErrors(cudaMalloc(reinterpret_cast<void **>(&device_b), size * sizeof(int32_t)));
    checkCudaErrors(cudaMalloc(reinterpret_cast<void **>(&device_c), size * sizeof(int32_t)));

    // create cuda events to measure timing 
    cudaEvent_t start, stop;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));

    // init host memory
    fill_random(host_a, size);
    fill_random(host_b, size);

    checkCudaErrors(cudaMemcpy(device_a, host_a, size * sizeof(int32_t), cudaMemcpyHostToDevice));
    checkCudaErrors(cudaMemcpy(device_b, host_b, size * sizeof(int32_t), cudaMemcpyHostToDevice));

    // exec calc on host
    auto timer = timer_start;
    vector_add_cpu(host_a, host_b, host_c, size);
    auto elapsed = timer_elapsed(timer);
    
    ost << "Host calcs took: " << float(elapsed/1000000.0) << "ms" << std::endl;

    checkCudaErrors(cudaProfilerStart());
    // exec calc on device
    checkCudaErrors(cudaEventRecord(start, 0));
    vector_add_gpu <<<device_blocks, THREADS_PER_BLOCKS>>> (device_a, device_b, device_c, size);
    checkCudaErrors(cudaEventRecord(stop, 0));
    checkCudaErrors(cudaEventSynchronize(stop));
    checkCudaErrors(cudaProfilerStop());

    float msecTotal = 0.0f;
    cudaEventElapsedTime(&msecTotal, start, stop);
    ost << "Device calcs took: " << msecTotal << "ms" << std::endl; 

    checkCudaErrors(cudaMemcpy(buff_device_on_host, device_c, size * sizeof(int32_t), cudaMemcpyDeviceToHost));

    if (compare_array(host_c, buff_device_on_host, size))
        ost << "Computed arrays from device and host are identical" << std::endl;
    else 
        ost << "Computed arrays from device and host aren't identical" << std::endl;

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
    
    for (int i = 1; i <= 5; i++) {
        std::cout << "Test №" << i << " === Array size: " << INIT_ARRAY_SIZE*std::pow(10, i) << std::endl; 
        HostVsDevice(INIT_ARRAY_SIZE*std::pow(10, i), std::cout);
        std::cout << std::endl;
    }
    return 0;
}
