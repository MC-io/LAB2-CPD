#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <fstream>

#define matrix std::vector<std::vector<int>> 

matrix classic_matrix_multiplication(matrix A, matrix B)
{
    matrix C(A.size());
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B[0].size(); j++)
        {
            C[i].push_back(0);
            for (int k = 0; k < B.size(); k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

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



void print_mat(matrix A)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[0].size(); j++)
        {
            std::cout << A[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main()
{
    srand(time(0));

    std::ofstream file("output.txt");

    file << "Tamano,Bloques-1,Bloques-2,Bloques-4,Bloques-8,Bloques-16,Bloques-32,Bloques-64,Bloque-128,Clasica,\n";
    for (int size = 16; size <= 1024; size *= 2)
    {
        file << size << ',';
        matrix A = create_random_mat(size,size);
        matrix B = create_random_mat(size,size);

        for (int block_size = 1; block_size <= 128; block_size *= 2)
        {
            auto st = std::chrono::steady_clock::now();
            matrix C2 = block_matrix_multiplication(A, B, block_size);
            auto fi = std::chrono::steady_clock::now();

            double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(fi - st).count();
            file << elapsed << ',';
        }

        auto start = std::chrono::steady_clock::now();
        matrix C1 = classic_matrix_multiplication(A, B);
        auto finish = std::chrono::steady_clock::now();
        double elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

        file << elapsed_seconds << ',';

        file << '\n';


    }

    file.close();
    



    return 0;
}