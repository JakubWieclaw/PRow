#include "../solver/hamming.h"
#include <cstdlib>
#include <cuda_runtime.h>
#include <vector>
#include <iostream>

__device__ int count_hamming_distance_cuda(const bool* a, const bool* b, int m) {
    int distance = 0;
    for (int i = 0; i < m; i++) {
        if (a[i] != b[i]) {
            distance++;
        }
    }
    return distance;
}

__global__ void count_all_pairs_with_distance_equal_n_cuda(const bool* d_sequences, int* d_pairs, int num_sequences, int m, int n, int* d_count) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int total_pairs = num_sequences * (num_sequences - 1) / 2;

    if (idx < total_pairs) {
        int i = idx / (num_sequences - 1);
        int j = idx % (num_sequences - 1);
        if (j >= i) j++;

        const bool* a = d_sequences + i * m;
        const bool* b = d_sequences + j * m;

        if (count_hamming_distance_cuda(a, b, m) == n) {
            int index = atomicAdd(d_count, 1);
            d_pairs[index * 2] = i;
            d_pairs[index * 2 + 1] = j;
        }
    }
}

std::vector<std::pair<int, int>> cuda_count_all_pairs_with_distance_equal_n(const std::vector<std::vector<bool>>& vector_of_sequences, int n) {
    int num_sequences = vector_of_sequences.size();
    int m = vector_of_sequences[0].size();
    int total_pairs = num_sequences * (num_sequences - 1) / 2;

    bool* h_sequences = new bool[num_sequences * m];
    int* h_pairs = new int[total_pairs * 2];
    int h_count = 0;

    for (int i = 0; i < num_sequences; i++) {
        for (int j = 0; j < m; j++) {
            h_sequences[i * m + j] = vector_of_sequences[i][j];
        }
    }

    bool* d_sequences;
    int* d_pairs;
    int* d_count;

    cudaMalloc(&d_sequences, num_sequences * m * sizeof(bool));
    cudaMalloc(&d_pairs, total_pairs * 2 * sizeof(int));
    cudaMalloc(&d_count, sizeof(int));

    cudaMemcpy(d_sequences, h_sequences, num_sequences * m * sizeof(bool), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &h_count, sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (total_pairs + blockSize - 1) / blockSize;
    count_all_pairs_with_distance_equal_n_cuda<<<numBlocks, blockSize>>>(d_sequences, d_pairs, num_sequences, m, n, d_count);

    cudaMemcpy(&h_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
    cudaMemcpy(h_pairs, d_pairs, h_count * 2 * sizeof(int), cudaMemcpyDeviceToHost);

    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < h_count; i++) {
        pairs.push_back(std::make_pair(h_pairs[i * 2], h_pairs[i * 2 + 1]));
    }

    cudaFree(d_sequences);
    cudaFree(d_pairs);
    cudaFree(d_count);
    delete[] h_sequences;
    delete[] h_pairs;

    return pairs;
}
