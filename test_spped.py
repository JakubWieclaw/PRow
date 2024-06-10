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
    for n in range(1000, 4001, 1000):
        for m in range(1000, 2001, 500):
            print(f"n={n}, m={m}")
            print("Sequential")
            os.system(f"{command_sequential} {n} {m}")
            print("Parallel")
            os.system(f"{command_parallel} {n} {m}")
            print("CUDA")
            os.system(f"{command_cuda} {n} {m}")
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
    plt.figure(figsize=(20, 8))

    # plt.plot(df_seq.index, df_seq['time'], label='Sequential', linestyle='-')
    # plt.plot(df_par.index, df_par['time'], label='Parallel', linestyle='--')
    # plt.plot(df_cuda.index, df_cuda['time'], label='CUDA', linestyle=':')

    plt.plot('(' + df_seq['n'].astype(str) + ',' + df_seq['m'].astype(str) + ')', df_seq['time'], label='Sequential', linestyle='-')
    plt.plot('(' + df_par['n'].astype(str) + ',' + df_par['m'].astype(str) + ')', df_par['time'], label='Parallel', linestyle='-')
    plt.plot('(' + df_cuda['n'].astype(str) + ',' + df_cuda['m'].astype(str) + ')', df_cuda['time'], label='CUDA', linestyle='-')

    plt.xlabel('(n,m)')
    plt.ylabel('Time (s)')
    plt.title('Execution Time by Method')
    plt.legend()
    plt.grid(True)
    plt.savefig('results.png')

def main():
    results_file = "results.csv"
    # remove_results_file(results_file)
    # create_results_file(results_file)
    # run_tests()
    df_seq, df_par, df_cuda = read_and_process_results(results_file)
    plot_results(df_seq, df_par, df_cuda)

if __name__ == "__main__":
    main()
