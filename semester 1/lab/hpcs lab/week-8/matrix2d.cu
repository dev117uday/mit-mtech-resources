//%%cu
#include "cuda_runtime.h"
#include <stdio.h>
#define Block_Size 2

__global__ void matrixmul(int *md, int *nd, int *pd, int n_wid)
{
    int a;
    int Pvalue = 0;
    int col = blockIdx.x * Block_Size + threadIdx.x;
    int row = blockIdx.y * Block_Size + threadIdx.y;

    for (a = 0; a < n_wid; a++)
    {
        Pvalue += (md[row * n_wid + a] * nd[a * n_wid + col]);
    }
    pd[row * n_wid + col] = Pvalue;
}
int main(void)
{
    int N = 4, i, j, sz;
    int A[4][4];
    int B[4][4];
    int C[4][4];
    int *d_a, *d_b, *d_c;

    printf("\ngiven matrix:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 1;
        }
    }
    printf("\nMatrix A:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix B:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    sz = sizeof(int) * N * N;
    int Grid_Sz;
    Grid_Sz = N / Block_Size;

    cudaMalloc((void **)&d_a, sz);
    cudaMalloc((void **)&d_b, sz);
    cudaMalloc((void **)&d_c, sz);

    cudaMemcpy(d_a, A, sz, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, B, sz, cudaMemcpyHostToDevice);

    dim3 blockDim(Block_Size, Block_Size);
    dim3 gridDim(Grid_Sz, Grid_Sz);

    matrixmul<<<gridDim, blockDim>>>(d_a, d_b, d_c, N);

    cudaMemcpy(C, d_c, sz, cudaMemcpyDeviceToHost);
    printf("\nMatrix C:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}