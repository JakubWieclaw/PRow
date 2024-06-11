import os
import pandas as pd
import matplotlib.pyplot as plt

# Define command paths
command_sequential = ".\hamming_sequential.exe"
command_parallel = ".\hamming_parallel.exe"
command_cuda = ".\hamming_cuda.exe"

def remove_results_file(file_path):
    """Remove the results.csv file if it exists."""
    if os.path.exists(file_path):
        os.remove(file_path)

def create_results_file(file_path):
    """Create the results.csv file with the header."""
    with open(file_path, "w") as f:
        f.write("method,n,m,time\n")

def run_tests():
    """Run the hamming tests with different parameters."""
    print("Running tests...")
    for n in range(2000, 5001, 500):
        for m in range(1000, 2001, 500):
            print(f"n={n}, m={m}")
            print("Sequential")
            os.system(f"{command_sequential} {n} {m}")
            print("Parallel")
            os.system(f"{command_parallel} {n} {m}")
            print("CUDA")
            os.system(f"{command_cuda} {n} {m}")

            # Compare results from sequential_pairs.txt, parallel_pairs.txt, and cuda_pairs.txt
            with open("sequential_pairs.txt", "r") as f:
                seq_pairs = f.readlines()
                new_seq_pairs = []
                for el in seq_pairs:
                    line = el.split()
                    new_seq_pairs.append(tuple([int(line[0]), int(line[1])]))
            with open("parallel_pairs.txt", "r") as f:
                par_pairs = f.readlines()
                # sort pairs by their first and then second element
                par_pairs = sorted(par_pairs, key=lambda x: (int(x.split()[0]), int(x.split()[1])))
                new_par_pairs = []
                for el in par_pairs:
                    line = el.split()
                    new_par_pairs.append(tuple([int(line[0]), int(line[1])]))
                    
            with open("cuda_pairs.txt", "r") as f:
                cuda_pairs = f.readlines()
                # sort pairs by their first and then second element
                cuda_pairs = sorted(cuda_pairs, key=lambda x: (int(x.split()[0]), int(x.split()[1])))
                new_cuda_pairs = []
                for el in cuda_pairs:
                    line = el.split()
                    new_cuda_pairs.append(tuple([int(line[0]), int(line[1])]))

            # Check if the pairs are the same
            # asert = True
            for i in range(len(new_seq_pairs)):
                if new_seq_pairs[i][0] != new_par_pairs[i][0] or new_seq_pairs[i][1] != new_par_pairs[i][1] or new_seq_pairs[i][0] != new_cuda_pairs[i][0] or new_seq_pairs[i][1] != new_cuda_pairs[i][1] or new_par_pairs[i][0] != new_cuda_pairs[i][0] or new_par_pairs[i][1] != new_cuda_pairs[i][1]:
                    print("Sequential and Parallel pairs are not the same")
                    print(f"i: {i}, seq: {new_seq_pairs[i]}, par: {new_par_pairs[i]}, cuda: {new_cuda_pairs[i]}")
                    break
    print("Tests completed!")

def read_and_process_results(file_path):
    """Read the results from the CSV file and process the data."""
    df = pd.read_csv(file_path)
    df['time'] = df['time'].astype(float)
    
    df_seq = df[df['method'] == 'sequential'].sort_values(by='time').reset_index(drop=True)
    df_par = df[df['method'] == 'parallel'].sort_values(by='time').reset_index(drop=True)
    df_cuda = df[df['method'] == 'cuda'].sort_values(by='time').reset_index(drop=True)
    
    return df_seq, df_par, df_cuda

def plot_results(df_seq, df_par, df_cuda):
    """Plot the data from the processed DataFrames."""
    plt.figure(figsize=(20, 13))

    # plt.plot(df_seq.index, df_seq['time'], label='Sequential', linestyle='-')
    # plt.plot(df_par.index, df_par['time'], label='Parallel', linestyle='--')
    # plt.plot(df_cuda.index, df_cuda['time'], label='CUDA', linestyle=':')

    plt.scatter(df_seq['n'].astype(str) + ',' + df_seq['m'].astype(str), df_seq['time'], label='Sequential', linestyle='-')
    plt.scatter(df_par['n'].astype(str) + ',' + df_par['m'].astype(str), df_par['time'], label='Parallel', linestyle='-')
    plt.scatter(df_cuda['n'].astype(str) + ',' + df_cuda['m'].astype(str), df_cuda['time'], label='CUDA', linestyle='-')

    plt.xlabel('(n,m)', fontsize = 18)
    plt.ylabel('Time (s)', fontsize = 18)
    plt.title('Execution Time by Method')
    plt.legend()
    plt.grid(True)
    plt.xticks(rotation=45, fontsize = 15)
    plt.yticks(fontsize = 15)
    plt.savefig('results.png')

def main():
    results_file = "results.csv"
    # Comment next 3 line if you only want to change plots on the same results
    remove_results_file(results_file)
    create_results_file(results_file)
    run_tests()
    df_seq, df_par, df_cuda = read_and_process_results(results_file)
    plot_results(df_seq, df_par, df_cuda)

if __name__ == "__main__":
    main()
