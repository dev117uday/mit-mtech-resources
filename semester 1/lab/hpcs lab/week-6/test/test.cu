#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"

__global__ void octal(int *a,int *b)
{
	int tid = threadIdx.x;
	long int rem[50],i=0,length=0,x=0;
	int num=a[tid];
	while(num>7)
 	{
 		rem[i]=num%8;
 		num=num/8;
 		i++;
 		length++;
 	}

	for(i=length-1;i>=0;i--)
	{
		x=x+(rem[i]*(10*i));
	}	
	b[tid]=x;

}
int main(void)
{
	int i,a[10000],b[10000],n;
	printf("Enter value of N:");
	n=20
	printf("Enter array elements of array A\n");
	for(i=0;i<n;i++)
		a[i] = rand()%100;
	int *d_a,*d_b;
	int size = sizeof(int);
	cudaMalloc((void **)&d_a,size*n);
	cudaMalloc((void **)&d_b,size*n);
	cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size*n,cudaMemcpyHostToDevice);
	octal<<<1,n>>>(d_a,d_b);
	cudaMemcpy(b,d_b,size*n,cudaMemcpyDeviceToHost);
	printf("Octal array is :");
	for(i=0;i<n;i++)
	{
		printf("%d\t",b[i]);
	}
	cudaFree(d_a);
	cudaFree(d_b);

	return 0;
}
