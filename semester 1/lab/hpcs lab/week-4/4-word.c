#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, i, j, n, r;
    double t, o;
    char a[100], b[100], c[100];
    int p = 1;
    MPI_Init(&argc, &argv);
    double w = MPI_Wtime();
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        printf("enter length of string\n");
        scanf("%d", &n);
        printf("enter string \n ");
        scanf("%s", a);
    }

    MPI_Scatter(a, 1, MPI_CHAR, b, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // for (i = 0; i < rank + 1; i++)
    //     printf("%s ", &b[0]);

    MPI_Gather(b, rank + 1, MPI_CHAR, c, rank + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < strlen(c); i++)
        {
            printf("%c", c[i]);
        }
    }

    t = MPI_Wtime();
    o = t - w;
    printf(" time by %d: %f ms \n ", rank, o);

    MPI_Finalize();
}
