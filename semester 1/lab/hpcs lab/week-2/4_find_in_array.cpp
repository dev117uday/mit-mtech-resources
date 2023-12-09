#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{

		int N;
		cout << "Enter the number of elements : ";
		cin >> N;

		int arr[N];
		cout << "Enter the array : \n";
		for (int i = 0; i < N; i++)
		{
			cin >> arr[i];
		}

		int element;
		cout << "Enter the element to find : ";
		cin >> element;

		MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&arr[N / 2], N / 2, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send(&element, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);

		bool flag1 = false, flag2 = false;

		for (int i = 0; i < N / 2; i++)
		{
			if (arr[i] == element)
			{
				flag1 = true;
				break;
			}
		}

		MPI_Recv(&flag2, 1, MPI_CXX_BOOL, 1, 3, MPI_COMM_WORLD, &status);

		if (flag1)
		{
			cout << "process 0 found the element\n";
		}
		else if (flag2)
		{
			int index;
			MPI_Recv(&index, 1, MPI_INT, 1, 4, MPI_COMM_WORLD, &status);
			cout << "process 1 found the element at " << index << endl;
		}
		else
		{
			cout << "Element not found\n";
		}
	}
	else if (rank == 1)
	{

		int N;
		MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		int brr[N / 2];
		MPI_Recv(&brr[0], N / 2, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		int element;
		MPI_Recv(&element, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);

		bool flag;
		int index;

		for (int i = 0; i < N / 2; i++)
		{
			if (brr[i] == element)
			{
				flag = true;
				index = i;
				break;
			}
		}

		index = index + 1 + N / 2;

		MPI_Send(&flag, 1, MPI_CXX_BOOL, 0, 3, MPI_COMM_WORLD);
		if (flag)
		{
			MPI_Send(&index, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
}
