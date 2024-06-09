import time
import os

command_sequential = ".\hamming.exe"
command_parallel = ".\hamming_parallel.exe"

for n in range(1000, 5001, 500):
    for m in range(1000, 5001, 500):
        start = time.time()
        os.system(f"{command_sequential} {n} {m}")
        end = time.time()
        seq_time = end-start
    
        start = time.time()
        os.system(f"{command_parallel} {n} {m}")
        end = time.time()
        par_time = end-start

        print("Parallel/Sequential: ", par_time/seq_time, "n: ", n, "m: ", m)