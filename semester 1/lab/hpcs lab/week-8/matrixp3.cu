//%%cu
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define N 3 // Change this to the desired matrix size

__global__ void diagonalManipulation(int* matrix) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row == col) {
        matrix[row * N + col] = 0;
    } else if (row < col) {
        // Calculate the factorial of the element
        int fact = 1;
        for (int i = 2; i <= matrix[row * N + col]; i++) {
            fact *= i;
        }
        matrix[row * N + col] = fact;
    } else {
        // Calculate the sum of digits of the element
        int num = matrix[row * N + col];
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        matrix[row * N + col] = sum;
    }
}

int main() {
    int matrix[N][N];

    // Initialize the matrix with some values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }

    int* d_matrix;
    cudaMalloc((void**)&d_matrix, N * N * sizeof(int));
    cudaMemcpy(d_matrix, matrix, N * N * sizeof(int), cudaMemcpyHostToDevice);

    dim3 dimBlock(N, N);
    dim3 dimGrid(1, 1);

    diagonalManipulation<<<dimGrid, dimBlock>>>(d_matrix);
    cudaDeviceSynchronize();

    cudaMemcpy(matrix, d_matrix, N * N * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the modified matrix
    printf("Modified Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    cudaFree(d_matrix);
    return 0;
}
