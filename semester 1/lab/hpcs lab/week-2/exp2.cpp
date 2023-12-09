
#include <iostream>
#include<mpi.h>

using namespace std;

int main(int argc, char * argv[]) {

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// if(rank == 0) {
	// 	char message[8] = "manipal";
	// 	char rec_message[8];
	// 	int len = 8;

	// 	printf("sending %s from rank %d\n", message, rank);

	// 	MPI_Send(&len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	// 	MPI_Send(&message, len,MPI_CHAR, 1, 1, MPI_COMM_WORLD);
		
	// 	MPI_Recv(&rec_message, len, MPI_CHAR, 1,2, MPI_COMM_WORLD, &status);
	// 	printf("\nreceived message : %s in rank %d\n", rec_message, rank);

	// } else if (rank ==1 ){
	// 	int len;
	// 	char message[8];

	// 	MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	// 	MPI_Recv(&message, len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
	// 	printf("\nreceived : %s in rank %d\n", message, rank);

	// 	MPI_Send(&message, len, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
	// 	printf("\nsending message : %s from rank %d\n", message, rank);
	// }

	// if(rank == 0) {
	// 	// dont send to rank == 0
	// 	for(int i=1;i< size; ++i) 
	// 	{
	// 		printf("sending %d to rank %d\n", i, i);
	// 		MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	// 	}

	// } else if (rank != 0) {
	// 	int num;
	// 	MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	// 	printf("\nreceived %d in rank %d", num, rank);
	// }


	// if(rank == 0) {
	// 	// dont send to rank == 0
	// 	for(int i=1;i< size; ++i) 
	// 	{
	// 		char message[8] = "manipal";
	// 		int len = 8;
	// 		printf("\nsending msg : %s to rank %d", message, i);
	// 		MPI_Send(&len, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	// 		MPI_Send(&message, len, MPI_CHAR, i, 1, MPI_COMM_WORLD);
	// 	}

	// } else if (rank != 0) {
	// 	int len;
	// 	char message[8];
	// 	MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	// 	MPI_Recv(&message, len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
	// 	printf("\nreceived message %s in rank %d", message, rank);
	// }

	if (rank == 0) {
		cout << "Enter the number of elements : ";
		int N;
		cin >> N;
		int arr[N];
		for (int i=0; i<N; i++) cin >> arr[i];

		MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&arr[N/2], N/2, MPI_INT, 1, 1, MPI_COMM_WORLD);

		int sum0=0, sum1=0, sum2 = 0;

		for(int i=0;i<N/2; i++) {
			sum1  = sum1 + arr[i];
		}

		cout << "sum1 " << sum1 << endl;

		MPI_Recv(&sum2, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		sum0 = sum1+sum2;
		cout << "final sum : " << sum0 << endl;		

	} else if (rank == 1) {
		int N;
		MPI_Recv(&N, 1, MPI_INT, 0,0, MPI_COMM_WORLD, &status);
		int brr[N/2];
		MPI_Recv(&brr[0], N/2, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

		int sum2 = 0;
		for (int i = 0; i < N/2; ++i)
		{
			sum2 += brr[i];
		}

		cout << "sum2 " << sum2 << endl;

		MPI_Send(&sum2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}



	

	MPI_Finalize();

}
