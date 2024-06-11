#include "solver/hamming.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>

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

    //std::cout << "Generating " << n << " sequences of " << m << " bits" << std::endl;
    //auto sequences = generate_sequences_based_on_lines_and_points(n, m);
    auto sequences = load_sequences_from_file("sequences.txt");
    //std::cout << "Generating finshed" << std::endl;

    // start timne measurement
    auto start = std::chrono::high_resolution_clock::now();

    auto pairs = cuda_count_all_pairs_with_distance_equal_n(sequences, 1);

    // end time measurement
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Print pairs into cuda_pairs.txt
    std::ofstream outfile_pairs;
    outfile_pairs.open("cuda_pairs.txt");
    for (auto pair : pairs) {
        outfile_pairs << pair.first << " " << pair.second << "\n";
    }
    outfile_pairs.close();
    

    // Insert n, m time measurment to database ../results.csv
    std::ofstream outfile;
    outfile.open("results.csv", std::ios_base::app);
    outfile << "cuda," << n << "," << m << "," << elapsed.count() << "\n";
    outfile.close();
    return 0;
}
