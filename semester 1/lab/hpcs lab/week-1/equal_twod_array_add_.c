#include <stdio.h>
#include <omp.h>

int main()
{

	int num_cpu = omp_get_num_procs();

	printf("num_cpu : %d\n", num_cpu);

	int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int b[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int c[8];

	int tid;

#pragma omp parallel num_threads(num_cpu)
	{
		tid = omp_get_thread_num();
		c[tid] = a[tid] + b[tid];
		printf("c[%d] = %d \n", tid, c[tid]);
	}
}