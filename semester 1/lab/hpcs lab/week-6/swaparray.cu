
#include <stdio.h>
#include "cuda_runtime.h"
#include <stdlib.h>

__global__ void swaparr(int *a, int size)
{
    int tid = threadIdx.x;
    if (tid < size && tid % 2 == 0)
    {
        int temp = a[tid + 1];
        a[tid + 1] = a[tid];
        a[tid] = temp;
    }
}

int main()
{

    int a[1000], n = 20;

    printf("Enter value of N:");
    scanf("%d", &n);
    printf("Enter array elements of array A\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // for (int i = 0; i < n; i++)
    //     a[i] = rand() % n;

    printf("Array is :\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    int *da;
    int intsize = sizeof(int);

    cudaMalloc((void **)&da, intsize * n);
    cudaMemcpy(da, a, intsize * n, cudaMemcpyHostToDevice);

    swaparr<<<1, n>>>(da, n);

    cudaMemcpy(a, da, intsize * n, cudaMemcpyDeviceToHost);

    printf("Sum array is : \n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    cudaFree(da);
}