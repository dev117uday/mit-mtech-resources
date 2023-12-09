
#include <stdio.h>
#include "cuda_runtime.h"

__global__ void add(int *a, int *b, int *c)
{
    *c = *a + *b;
}

int main()
{
    int a, b, c;
    int *da, *db, *dc;

    //printf("Enter a b c : ");
    // scanf("%d %d %d", &a, &b, &c);

    a = 4, b = 5;

    int intsize = sizeof(int);

    cudaMalloc((void **)&da, intsize);
    cudaMalloc((void **)&db, intsize);
    cudaMalloc((void **)&dc, intsize);

    cudaMemcpy(da, &a, intsize, cudaMemcpyHostToDevice);
    cudaMemcpy(db, &b, intsize, cudaMemcpyHostToDevice);

    add<<<1, 1>>>(da, db, dc);

    cudaMemcpy(&c, dc, intsize, cudaMemcpyDeviceToHost);

    printf("Sum c : %d", c);
    
    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
    

}