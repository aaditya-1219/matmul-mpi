// Name: Aaditya S. Patil PRN: 21610005 Batch: T4
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 1000
int A[N][N];
int B[N][N];

void matrixMultiplication(){
    int result[N][N];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                result[i][j] += A[i][k]*B[k][j];
            }
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            A[i][j] = (rand() % 9)+1;
            B[i][j] = (rand() % 9)+1;
        }
    }
    matrixMultiplication();
    return 0;
}