#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{

    int size, rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        char string[100];
        scanf("%[^\n]s", string);
        printf("string is : %s\n", string);
        int len = strlen(string);
        printf("len : %d\n", len);
        MPI_Send(&len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&string[len / 2], len, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        for (int i = 0; i < len / 2; i++)
        {
            printf("%c", string[i]);
        }
        printf("\n");

        int count = 0;

        for (int i = 0; i < len / 2; i++)
        {
            if (string[i] != 'a' && string[i] != 'e' && string[i] != 'i' && string[i] != 'o' && string[i] != 'u')
            {
                count++;
            }
        }

        printf("counter : %d\n", count);
    }
    if (rank == 1)
    {
        int len;
        MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        char string[len / 2];
        MPI_Recv(&string[0], len / 2, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        for (int i = 0; i < len / 2; i++)
        {
            printf("%c", string[i]);
        }

        int count = 0;

        for (int i = 0; i < len / 2; i++)
        {
            if (string[i] != 'a' && string[i] != 'e' && string[i] != 'i' && string[i] != 'o' && string[i] != 'u')
            {
                count++;
            }
        }

        printf("counter : %d\n", count);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
}