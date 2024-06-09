#include "../solver/hamming.h"
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

    std::cout << "Generating " << n << " sequences of " << m << " bits" << std::endl;
    auto sequences = generate_n_sized_sequences_of_random_m_bits(n, m);
    std::cout << "Generating finshed" << std::endl;
    auto pairs = cuda_count_all_pairs_with_distance_equal_n(sequences, 1);

    // for (const auto& pair : pairs) {
    //     std::cout << "Pair: (" << pair.first << ", " << pair.second << ")" << std::endl;
    // }

    return 0;
}
