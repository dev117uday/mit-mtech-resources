#include <iostream>
#include <mpi.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
	int rank, size;
	int i, j;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	char s1[100], s2[100], a[100], b[100];

	if (rank == 0)
	{
		printf("Enter the first string\n");
		scanf("%s", s1);
		printf("Enter the second string\n");
		scanf("%s", s2);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Scatter(&s1[0], 1, MPI_CHAR, &a[0], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Scatter(&s2[0], 1, MPI_CHAR, &a[1], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Gather(&a[0], 2, MPI_CHAR, &b[0], 2, MPI_CHAR, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("result : %s\n", b);
	}
	MPI_Finalize();
	return 0;
}
