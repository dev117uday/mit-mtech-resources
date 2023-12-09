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

		cout << "Enter the number of elements : ";
		int N;
		cin >> N;
		int arr[N];

		for (int i = 0; i < N; i++)
			cin >> arr[i];

		MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&arr[N/2], N / 2, MPI_INT, 1, 1, MPI_COMM_WORLD);

		int sum0 = 0, sum1 = 0, sum2 = 0;

		for (int i = 0; i < N / 2; i++)
		{
			sum1 = sum1 + arr[i];
		}

		cout << "sum 1 : " << sum1 << endl;

		MPI_Recv(&sum2, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);

		sum0 = sum1 + sum2;
		cout << "final sum : " << sum0 << endl;
	}
	else if (rank == 1)
	{

		int N;
		MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		int brr[N / 2];
		MPI_Recv(&brr, N / 2, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

		int sum2 = 0;
		for (int i = 0; i < N / 2; ++i)
		{
			cout << brr[i] << " ";
			sum2 += brr[i];
		}

		cout << "sum 2 : " << sum2 << endl;
		MPI_Send(&sum2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
