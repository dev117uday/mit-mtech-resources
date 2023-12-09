#include <stdio.h>
#include <omp.h>

int main()
{

#pragma omp parallel for collapse(2)
	for (int i = 0; i < 4; ++i)
	{
		// this line wont work cuz of openmp mapping : printf("%d ", omp_get_thread_num());
		for (int j = 0; j < 4; ++j)
		{
			printf("%d ", omp_get_thread_num());
		}
	}
}