g++ -Iinclude -std=c++17 -O3 main.cpp solver/hamming.cpp -o hamming.exe
g++ -Iinclude -fopenmp -std=c++17 -O3 main_parallel.cpp solver/hamming.cpp -o hamming_parallel.exe

cd cuda
nvcc -o main_cuda main_cuda.cpp hamming_cuda.cu ../solver/hamming.cpp