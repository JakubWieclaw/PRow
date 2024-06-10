g++ -Iinclude -std=c++17 -O3 main.cpp solver/hamming.cpp -o hamming_sequential.exe
g++ -Iinclude -fopenmp -std=c++17 -O3 main_parallel.cpp solver/hamming.cpp -o hamming_parallel.exe

# cd cuda
nvcc -o hamming_cuda.exe main_cuda.cpp hamming_cuda.cu solver/hamming.cpp