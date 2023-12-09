#include <stdio.h>
#include <omp.h>

int main() {

	int N = 20;
	int sum = 0;
	int tid;


	#pragma omp parallel for reduction(+:sum)
	for( int i=0; i<=N; i++) 
	{
		sum += i;
	}


	printf("sum : %d\n", sum);

}