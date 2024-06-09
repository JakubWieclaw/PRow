g++ -Iinclude -std=c++17 -O3 main.cpp solver/hamming.cpp -o hamming.exe
g++ -Iinclude -fopenmp -std=c++17 -O3 main_parallel.cpp solver/hamming.cpp -o hamming_parallel.exe