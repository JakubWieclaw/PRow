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

    std::cout << "Generating " << n << " sequences of " << m << " bits" << std::endl;
    auto sequences = generate_sequences_based_on_lines_and_points(n, m);
    std::cout << "Generating finshed\nSaving sequence to file" << std::endl;
    save_sequences_to_file(sequences, "sequences.txt");
    std::cout << "Saving finished" << std::endl;

    // start timne measurement
    auto start = std::chrono::high_resolution_clock::now();
    
    auto pairs = count_all_pairs_with_distance_equal_n(sequences, 1);

    // end time measurement
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    
        

    // Insert n, m time measurment to database ../results.csv
    std::ofstream outfile;
    outfile.open("results.csv", std::ios_base::app);
    outfile << "sequential," << n << "," << m << "," << elapsed.count() << "\n";
    outfile.close();
}