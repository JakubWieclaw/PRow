#include <vector>
#include <string>

int count_hamming_distance(const std::vector<bool>& a, const std::vector<bool>& b);
std::vector<std::vector<bool>> generate_n_sized_sequences_of_random_m_bits(int n, int m);
std::vector<std::pair<int, int>> count_all_pairs_with_distance_equal_n(const std::vector<std::vector<bool>> &vector_of_sequences, int n);
std::vector<std::pair<int, int>> parrallel_count_all_pairs_with_distance_equal_n(const std::vector<std::vector<bool>> &vector_of_sequences, int n);
std::vector<std::pair<int, int>> cuda_count_all_pairs_with_distance_equal_n(const std::vector<std::vector<bool>>& vector_of_sequences, int n);
std::vector<std::vector<bool>> generate_sequences_based_on_lines_and_points(int n, int m);
void save_sequences_to_file(const std::vector<std::vector<bool>>& sequences, const std::string& filename);
std::vector<std::vector<bool>> load_sequences_from_file(const std::string& filename);