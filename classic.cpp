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


    matrix C1 = classic_matrix_multiplication(A, B);

    return 0;
}