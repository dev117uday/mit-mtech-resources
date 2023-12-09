
// display hello by all process
// hello by odd
// hello by even
// hello by those who rank is perfect square

#include<iostream>
#include<mpi.h>
#include<math.h>

using namespace std;

int main(int argc, char *argv[]) {

	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// if(rank ==0) {		
	// 	cout << "Hello by rank : " << rank <<  endl;
	// } else if (rank == 1) {
	// 	cout << "Hello by rank : " << rank <<  endl;
	// }

	// if (rank%2==0) {
	// 	cout << "Hello by rank : " << rank <<  endl;
	// }

	// if (rank%2 == 1) {
	// 	cout << "Hello by rank : " << rank <<  endl;	
	// }

	if (rank !=0 && rank == (int)sqrt(rank)*sqrt(rank)) {
		cout << "Hello by rank : " << rank <<  endl;	
	}


	MPI_Finalize();
}


	// for (int i=0;i<size; i++) {
	// 	if(rank == i) {
	// 		cout << "Hello by rank : " << rank <<  endl;
	// 	}
	// }