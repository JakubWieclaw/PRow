#include "solver/hamming.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "2 arguments required (n, m)" << std::endl;
        return 1;
    }
    int n = std::atoi(argv[1]);
    int m = std::atoi(argv[2]);
    if (n <= 0 || m <= 0) {
        std::cout << "Arguments must be positive integers" << std::endl;
        return 1;
    }

    srand(time(NULL));

    auto sequences = generate_n_sized_sequences_of_random_m_bits(n, m);
    auto pairs = count_all_pairs_with_distance_equal_n(sequences, 1);
}