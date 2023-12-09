//%%cu
#include "cuda_runtime.h"
#include <stdio.h>

__global__ void Add(int *a, int *b, int *c, int *d, int n)
{
    int id, i;
    id = threadIdx.x;
    for (i = 0; i < n; i++)
    {
        c[i * n + id] = a[i * n + id] + b[i * n + id];
        d[id * n + i] = a[id * n + i] + b[id * n + i];
    }
}

__global__ void AddEach(int *a, int *b, int *e, int n)
{
    int id, i;
    id = threadIdx.x;
    e[id] = a[id] + b[id];
}

int main(void)
{
    int a[100], b[100], c[100], d[100], e[100], n, i;
    int size, *d_a, *d_b, *d_c, *d_d, *d_e;

    printf("\nEnter N\n");
    // scanf("%d", &n);
    n = 3;

    printf("\nEnter MATRIX A\n");
    for (i = 0; i < n * n; i++)
    {
        // scanf("%d", &a[i]);
        a[i] = rand()%10;
        printf("%d  ", a[i] );
    }

    printf("\nEnter MATRIX B\n");
    for (i = 0; i < n * n; i++)
    {
        // scanf("%d", &b[i]);
        b[i] = rand()%10;
        printf("%d  ", b[i] );
    }

    size = sizeof(int);

    cudaMalloc((void **)&d_a, n * n * size);
    cudaMalloc((void **)&d_b, n * n * size);
    cudaMalloc((void **)&d_c, n * n * size);
    cudaMalloc((void **)&d_d, n * n * size);
    cudaMalloc((void **)&d_e, n * n * size);

    cudaMemcpy(d_a, a, n * n * size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, n * n * size, cudaMemcpyHostToDevice);

    Add<<<1, n>>>(d_a, d_b, d_c, d_d, n);
    AddEach<<<1, n * n>>>(d_a, d_b, d_e, n);

    cudaMemcpy(c, d_c, size * n * n, cudaMemcpyDeviceToHost);
    cudaMemcpy(d, d_d, size * n * n, cudaMemcpyDeviceToHost);
    cudaMemcpy(e, d_e, size * n * n, cudaMemcpyDeviceToHost);

    printf("\nAddition of through rows \n");
    for (i = 0; i < n * n; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\nAddition through cols\n");
    for (i = 0; i < n * n; i++)
    {
        printf("%d ", d[i]);
    }
    printf("\nAddition through each thread\n");
    for (i = 0; i < n * n; i++)
    {
        printf("%d ", e[i]);
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    cudaFree(d_d);
    cudaFree(d_e);
    return 0;
}