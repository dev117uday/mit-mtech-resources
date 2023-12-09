#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char string[100];
    char recString[100];
    int output[2];
    int len;

    if (rank == 0)
    {
        scanf("%[^\n]s", string);
        printf("string : %s\n", string);
        len = strlen(string);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(string, len / 2, MPI_CHAR, recString, len / 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    printf("\nstring %s rank %d\n", recString, rank);

    int count = 0;

    for (int i = 0; i < len / 2; i++)
    {
        if (recString[i] != 'a' && recString[i] != 'e' && recString[i] != 'i' && recString[i] != 'o' && recString[i] != 'u')
        {
            count++;
        }
    }

    MPI_Gather(&count, 1, MPI_INT, output, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank ==0) {
        for (int i=0; i<2; i++) {
            printf("%d ", output[i]);
        }
    }

    MPI_Finalize();
}