#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[size * size];
    int arr1[size];
    int arr2[size * size];
    int brr[size][size];
    int brr1[size];
    int brr2[size][size];
    

    if (rank == 0)
    {
        for (int i = 0; i < size * size; i++)
        {
            scanf("%d", &arr[i]);
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                scanf("%d", &brr[i][j]);
            }
        }
        for (int i = 0; i < size * size; i++)
        {
            printf("%d-", arr[i]);
        }
        printf("\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d-", brr[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Scatter(arr, size, MPI_INT, arr1, size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(brr, size, MPI_INT, brr1, size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < size; i++)
    {
        printf("%d-%d\n", arr1[i], rank);
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d-%d\n", brr1[i], rank);
    }

    MPI_Finalize();
}