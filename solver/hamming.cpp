#include "hamming.h"
#include <cstdlib>
#include <fstream>

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

std::vector<std::vector<bool>> generate_sequences_based_on_lines_and_points(int n, int m) {
    std::vector<std::vector<bool>> sequences;
    std::vector<std::pair<double, double>> lines;
    std::vector<std::pair<double, double>> points;

    // Generate m random lines
    for (int i = 0; i < m; ++i) {
        double slope = (rand() % 20001 - 10000) / 100.0; // from -100 to 100
        double intercept = (rand() % 20001 - 10000) / 100.0; // from -100 to 100
        lines.push_back({slope, intercept});
    }

    // Generate n random points
    for (int i = 0; i < n; ++i) {
        double x = (rand() % 20001 - 10000) / 100.0; // from -100 to 100
        double y = (rand() % 20001 - 10000) / 100.0; // from -100 to 100
        points.push_back({x, y});
    }

    // Generate the sequences based on points and lines
    for (const auto& point : points) {
        std::vector<bool> sequence;
        for (const auto& line : lines) {
            double y_line = line.first * point.first + line.second;
            sequence.push_back(point.second > y_line);
        }
        sequences.push_back(sequence);
    }

    return sequences;
}

void save_sequences_to_file(const std::vector<std::vector<bool>>& sequences, const std::string& filename) {
    // Clear and recreate the file
    std::ofstream file(filename);
    for (const auto& sequence : sequences) {
        for (const auto& bit : sequence) {
            file << bit;
        }
        file << std::endl;
    }
    file.close();
}

std::vector<std::vector<bool>> load_sequences_from_file(const std::string& filename) {
    std::vector<std::vector<bool>> sequences;
    std::ifstream
    file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<bool> sequence;
        for (char c : line) {
            sequence.push_back(c == '1');
        }
        sequences.push_back(sequence);
    }
    return sequences;
}