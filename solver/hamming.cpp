#include "hamming.h"
#include <cstdlib>

int count_hamming_distance(const std::vector<bool>& a, const std::vector<bool>& b) {
    int distance = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            distance++;
        }
    }
    return distance;
}

std::vector<std::vector<bool>> generate_n_sized_sequences_of_random_m_bits(int n, int m) {
    std::vector<std::vector<bool>> sequences;
    for (int i = 0; i < n; i++) {
        std::vector<bool> sequence;
        for (int j = 0; j < m; j++) {
            sequence.push_back(rand() % 2);
        }
        sequences.push_back(sequence);
    }
    return sequences;
}

std::vector<std::pair<int, int>> count_all_pairs_with_distance_equal_n(const std::vector<std::vector<bool>> &vector_of_sequences, int n) {
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < vector_of_sequences.size(); i++) {
        for (int j = i + 1; j < vector_of_sequences.size(); j++) {
            if (count_hamming_distance(vector_of_sequences[i], vector_of_sequences[j]) == n) {
                pairs.push_back(std::make_pair(i, j));
            }
        }
    }
    return pairs;
}

std::vector<std::pair<int, int>> parrallel_count_all_pairs_with_distance_equal_n(const std::vector<std::vector<bool>> &vector_of_sequences, int n)
{
    std::vector<std::pair<int, int>> pairs;
    #pragma omp parallel for
    for (int i = 0; i < vector_of_sequences.size(); i++) {
        for (int j = i + 1; j < vector_of_sequences.size(); j++) {
            if (count_hamming_distance(vector_of_sequences[i], vector_of_sequences[j]) == n) {
                // #pragma omp critical
                pairs.push_back(std::make_pair(i, j));
            }
        }
    }
    return pairs;
}