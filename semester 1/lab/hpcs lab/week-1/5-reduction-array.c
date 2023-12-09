#include <stdio.h>
#include <omp.h>

int main()
{

	int myArray[6] = {};

#pragma omp parallel for reduction(+ : myArray[ : 6])
	
	for (int i = 0; i < 50; ++i)
	{
		int a = 2;
		for (int n = 0; n < 6; ++n)
		{
			myArray[n] += a;
		}
	}

	for (int n = 0; n < 6; ++n)
	{
		printf("%d ", myArray[n]);
	}

	printf("\n");
}