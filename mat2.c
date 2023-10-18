// Name: Aaditya S. Patil
// PRN: 21610005
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpi.h"

#define N 1000

MPI_Status status;

void printMatrix(int matrix[N][N]);

int matrix1[N][N];
int matrix2[N][N];
int productMatrix[N][N];

int i, j, k;

int main(int argc, char **argv)
{
    int size;
    int rank;

    int sourceProcessor;
    int worker;
    int rows;
    int matrixSubset;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int workers = size - 1;

    if (rank == 0)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                matrix1[i][j] = (rand() % 9) + 1;
                matrix2[i][j] = (rand() % 9) + 1;
            }
        }

        matrixSubset = 0;
        for (worker = 1; worker <= workers; worker++)
        {
            for(worker = 1; worker <= workers; worker++){
                MPI_Send(&matrixSubset, 1, MPI_INT, worker, 1, MPI_COMM_WORLD);
                MPI_Send(&matrix1[matrixSubset][0], N, MPI_INT, worker, 1, MPI_COMM_WORLD);
                MPI_Send(&matrix2, N * N, MPI_INT, worker, 1, MPI_COMM_WORLD);
                matrixSubset++;
            }
        }

        for (i = 1; i <= workers; i++)
        {
            sourceProcessor = i;
            MPI_Recv(&matrixSubset, 1, MPI_INT, sourceProcessor, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&productMatrix[matrixSubset][0], N, MPI_INT, sourceProcessor, 2, MPI_COMM_WORLD, &status);
        }
        printf("Product Matrix:\n");
        printMatrix(productMatrix);
    }

    if (rank > 0)
    {
        sourceProcessor = 0;
        MPI_Recv(&matrixSubset, 1, MPI_INT, sourceProcessor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&matrix1, N, MPI_INT, sourceProcessor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&matrix2, N * N, MPI_INT, sourceProcessor, 1, MPI_COMM_WORLD, &status);

        for (j = 0; j < N; j++)
        {
            productMatrix[0][j] = 0;
            for (k = 0; k < N; k++)
            {
                productMatrix[0][j] += (matrix1[0][k] * matrix2[k][j]);
            }
        }
        MPI_Send(&matrixSubset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&productMatrix, N, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

void printMatrix(int matrix[N][N])
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
