#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <fstream>

#define matrix std::vector<std::vector<int>> 

matrix block_matrix_multiplication(matrix A, matrix B, int block_size)
{
    int m  = A.size();
    int n  = A[0].size();
    int p  = B[0].size();

    matrix C;

    C.resize(A.size());
    for (int i = 0; i < A.size(); i++)
    {
        C[i].resize(B[0].size());
        for (int j = 0; j < B[0].size(); j++)
        {
            C[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i += block_size)
    {
        for (int j = 0; j < p; j += block_size)
        {
            for (int k = 0; k < n; k += block_size)
            {
                for (int i_block = i; i_block < std::min(i + block_size, m); i_block++)
                {
                    for (int j_block = j; j_block < std::min(j + block_size, p); j_block++)
                    {
                        for (int k_block = k; k_block < std::min(k + block_size, n); k_block++)
                        {
                            C[i_block][j_block] += A[i_block][k_block] * B[k_block][j_block];
                        }   
                    }     
                } 
            }
        }
    }
    return C;

}

matrix create_random_mat(int n, int m)
{
    matrix A(n);

    for (int i = 0; i < n; i++)
    {
        A[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            A[i][j] = rand() % 100 + 1;
        }
    }

    return A;
}

int main()
{
    srand(time(0));


    int size = 1024;
    matrix A = create_random_mat(size,size);
    matrix B = create_random_mat(size,size);


    matrix C1 = block_matrix_multiplication(A, B, 128);

    return 0;
}