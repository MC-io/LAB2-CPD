import numpy as np

def block_matrix_multiply(A, B, block_size):
    # Ensure the dimensions are compatible for block matrix multiplication
    assert A.shape[1] == B.shape[0]
    
    # Get matrix dimensions
    m, n, p = A.shape[0], A.shape[1], B.shape[1]
    
    # Initialize the result matrix with zeros
    result = np.zeros((m, p))
    
    for i in range(0, m, block_size):
        for j in range(0, p, block_size):
            for k in range(0, n, block_size):
                # Multiply and accumulate block-wise
                for i_block in range(i, min(i + block_size, m)):
                    for j_block in range(j, min(j + block_size, p)):
                        for k_block in range(k, min(k + block_size, n)):
                            result[i_block][j_block] += A[i_block][k_block] * B[k_block][j_block]
    
    return result

# Example usage
# Create random matrices A and B
A = np.random.random((5, 1))
B = np.random.random((1, 5))

# Block size for block matrix multiplication
block_size = 2

# Perform block matrix multiplication
result = block_matrix_multiply(A, B, block_size)

print("Matrix A:")
print(A)

print("\nMatrix B:")
print(B)

print("\nResult of block matrix multiplication:")
print(result)