//67070501016 Drarun Yookphan
#include <stdio.h>

int main() {
    int m1[10][10], m2[10][10], result[10][10];
    int rows1, cols1, rows2, cols2;

    printf("Matrix Multiplication\n");
    printf("Enter matrix dimension of M1 (rows columns): ");
    scanf("%d %d", &rows1, &cols1);

    printf("Enter M1 matrix elements:\n");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            scanf("%d", &m1[i][j]);
        }
    }

    printf("Enter matrix dimension of M2 (rows columns): ");
    scanf("%d %d", &rows2, &cols2);

    printf("Enter M2 matrix elements:\n");
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            scanf("%d", &m2[i][j]);
        }
    }

    if (cols1 != rows2) {
        printf("Invalid matrices dimension. Number of columns in M1 must equal to the number of rows in M2.\n");
        return 1;
    }
    
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < rows1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    
    printf("Resultant of Matrix Mb (M1 * M2):\n");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}