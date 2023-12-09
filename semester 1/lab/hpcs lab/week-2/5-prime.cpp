#include <iostream>
#include <mpi.h>

using namespace std;

int is_prime(int num)
{
	if (num <= 1)
	{
		return 0;
	}
	for (int i = 2; i * i <= num; ++i)
	{
		if (num % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[])
{

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		for(int i=0; i<50; i++) {
			if(is_prime(i)) {
				cout << "Process " << rank << " found prime : " << i << endl;
			}
		}
	}
	else if (rank == 1)
	{
		for(int i=50; i<=100; i++) {
			if(is_prime(i)) {
				cout << "Process " << rank << " found prime : " << i << endl;
			}
		}
	}

	MPI_Finalize();
}
