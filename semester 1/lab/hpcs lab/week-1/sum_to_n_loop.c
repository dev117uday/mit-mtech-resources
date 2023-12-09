#include <stdio.h>
#include <omp.h>

int main() {

	int N = 20;
	int sum = 0;

	#pragma omp parallel for
	for (int i = 0; i <= N; ++i) 
	{
		#pragma omp critical 
		{
			sum = sum + i;
		}

		// sum = sum + i;
	}

	printf("sum : %d\n", sum);

}