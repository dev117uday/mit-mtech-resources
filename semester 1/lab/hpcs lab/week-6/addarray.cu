#include <stdio.h>
#include "cuda_runtime.h"
#include <stdlib.h>

__global__ void addArray(int *a, int *b, int *c, int size)
{
    int tid = threadIdx.x;
    if (tid < size)
    {
        c[tid] = a[tid] + b[tid];
    }
}

int main()
{

    int a[1000], b[1000], c[1000], n = 20;

    // printf("Enter value of N:");
    // scanf("%d", &n);
    // printf("Enter array elements of array A\n");
    // for (i = 0; i < n; i++)
    //     scanf("%d", &a[i]);

    // printf("Enter array elements of array B\n");
    // for (i = 0; i < n; i++)
    //     scanf("%d", &b[i]);

    for (int i = 0; i < n; i++)
        a[i] = rand()%n;

    for (int i = 0; i < n; i++)
        b[i] = rand()%n;

    int *da, *db, *dc;
    int intsize = sizeof(int);

    cudaMalloc((void **)&da, intsize*n);
    cudaMalloc((void **)&db, intsize*n);
    cudaMalloc((void **)&dc, intsize*n);

    cudaMemcpy(da, a, intsize * n, cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, intsize * n, cudaMemcpyHostToDevice);

    addArray<<<1, n>>>(da, db, dc, n);

    cudaMemcpy(c, dc, intsize * n, cudaMemcpyDeviceToHost);

    printf("Sum array is :");
    for (int i = 0; i < n; i++)
        printf("%d %d %d\n", a[i], b[i], c[i]);

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
}