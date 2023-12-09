#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		char message[8] = "manipal";
		char rec_message[8];
		int len = 8;

		printf("\nsending message : %s from rank %d\n", message, rank);

		MPI_Ssend(&len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Ssend(&message, len, MPI_CHAR, 1, 1, MPI_COMM_WORLD);

		MPI_Recv(&rec_message, len, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
		printf("\nreceived : %s in rank %d\n", rec_message, rank);
	}
	else if (rank == 1)
	{
		int len;
		char message[8];

		MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&message, len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
		printf("\nreceived : %s in rank %d\n", message, rank);

		for(int i=0; i<len; i++) {
			if(message[i] >= 97) {
				message[i] -= 32;
			} else {
				message[i] += 32;
			}
		}

		MPI_Ssend(&message, len, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
		printf("\nsending message : %s from rank %d\n", message, rank);
	}

	MPI_Finalize();
}
