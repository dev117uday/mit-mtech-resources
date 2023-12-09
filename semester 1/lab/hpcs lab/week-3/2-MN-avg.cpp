#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
	int size, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int N = size;
	int M = atoi(argv[1]);

	int arr[N][M];
	int brr[N];
	double crr[N];

	if(rank == 0) {

		printf("Enter the array %dx%d : \n",N,M);

		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				cin >> arr[i][j];
			}
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Scatter(&arr, N, MPI_INT, &brr, M, MPI_INT, 0, MPI_COMM_WORLD);

	double avg = 0;

	for (int j = 0; j < M; ++j)
	{
		avg = avg + brr[j];
	}

	avg = avg / M;

	MPI_Gather(&avg, 1, MPI_DOUBLE, &crr, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		double total_avg = 0;
		for (int j = 0; j < M; ++j)
		{
			total_avg += crr[j];
		}
		total_avg = total_avg / M;
		cout << "Total avg " << total_avg << endl;
	}

	MPI_Finalize();
}
