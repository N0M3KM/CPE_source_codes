#include <stdio.h>
#define SIZE 5 // define SIZE as '5'

void printMatrix(int M[SIZE][SIZE])
{
    int i, j;
    printf("\nPrint Matrix:\n");
    for (i=0; i<SIZE;i++) {
        for (j=0;j<SIZE;j++) {
            printf("%2d", M[i][j]);
        }
        printf("\n");
    }
}

void warshallAlgorithm(int W[SIZE][SIZE]) {
    for (int k=0;k<SIZE;k++) {
        for (int i=0;i<SIZE;i++) {
            for (int j=0;j<SIZE;j++) {
                W[i][j] = (W[i][j]||(W[i][k] && W[k][j]));
            }
        }
    }
    printMatrix(W);
}

void readMatrix(int M[SIZE][SIZE])
{
    int i, j;
    printf("\nEnter no. of rows and columns of matrix: ");
    scanf("%d", SIZE);
    printf("\nInput elements of matrix [%d %d]:\n", SIZE, SIZE);
    for (i=0; i<SIZE;i++){
        for (j=0;j<SIZE;j++)
        {
            printf("M[%d][%d]: ", i, j);
            scanf("%d", &M[i][j]);
        }
    }
}
int main() {
    int M1[SIZE][SIZE]={
        {0,1,0,1,0},
        {0,0,1,0,1},
        {1,1,0,0,1},
        {1,0,0,0,0},
        {0,0,0,1,0}
    };
    // printf("Read Matrix M1:\n");
    // readMatrix(M1);
    warshallAlgorithm(M1);
    return 0;
}