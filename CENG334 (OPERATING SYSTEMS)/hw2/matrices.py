import numpy as np
def generate_input(input_file,output_file):
    # Define the dimensions of the matrices
    N = np.random.randint(1, 100)
    M = np.random.randint(1, 100)
    K = np.random.randint(1, 100)

    # Generate two matrices of random integers
    matrix_a = np.random.randint(0, 10, (N, M))
    matrix_b = np.random.randint(0, 10, (N, M))
    matrix_c = np.random.randint(0, 10, (M, K))
    matrix_d = np.random.randint(0, 10, (M, K))
    # Print the original matrices
    with open(input_file, "w") as f:
        f.write(f"{N} {M}\n")
        for row in matrix_a:
            f.write(" ".join(str(x) for x in row))
            f.write("\n")
        f.write(f"{N} {M}\n")
        for row in matrix_b:
            f.write(" ".join(str(x) for x in row))
            f.write("\n")
        f.write(f"{M} {K}\n")
        for row in matrix_c:
            f.write(" ".join(str(x) for x in row))
            f.write("\n")
        f.write(f"{M} {K}\n")
        for row in matrix_d:
            f.write(" ".join(str(x) for x in row))
            f.write("\n")

    # Add the matrices
    matrix_sum1 = matrix_a + matrix_b
    matrix_sum2 = matrix_c + matrix_d

        # Multiply the matrices
    matrix_product = np.matmul(matrix_sum1, matrix_sum2)

    # Print the product of the matrices
    with open(output_file, "w") as f:
        for row in matrix_product:
            for x in row:
                f.write(f"{x} ")
            f.write("\n")

def generate_test_cases(n):
    for i in range(n):
        generate_input(f"inputs/input{i+1}.txt",f"outputs/output{i+1}.txt")