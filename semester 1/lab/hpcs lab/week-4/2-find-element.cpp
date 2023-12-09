#include<iostream>
#include<mpi.h>

using namespace std;

int main(int argc, char *argv[]) {

	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int arr[3][3];
	int brr;
	int element, counter = 0;

	if(rank ==0) {

		printf("Enter the arr\n");

		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				cin >> arr[i][j];
			}
		}

		printf("Enter the element\n");

		cin >> element;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Bcast(arr, 9, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&element, 1, MPI_INT, 0, MPI_COMM_WORLD);


	for(int i=0; i<3; i++) {
		if(arr[rank][i] == element) {
			counter++;
		}
	}

	MPI_Reduce(&counter, &brr, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank ==0) {
		cout << "Found no. of occurences : " << brr << " " << endl;
	}

	MPI_Finalize();

}