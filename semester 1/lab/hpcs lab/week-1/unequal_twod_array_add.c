#include <stdio.h>
#include <omp.h>

int main()
{

	int num_cpu = omp_get_num_procs();
	printf("num_cpu : %d\n", num_cpu);

	int a[12] = {1, 2, 3, 1, 2, 3, 1, 2};
	int b[12] = {5, 4, 3, 5, 4, 1, 2, 3};
	int c[12];

	int tid;

#pragma omp parallel num_threads(num_cpu)
	{
		tid = omp_get_thread_num();
		c[tid] = a[tid] + b[tid];
		printf("c[%d] = %d \n", tid, c[tid]);
	}
}