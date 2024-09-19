//67070501016 Drarun Yookphan
#include <stdio.h>
#include <math.h>

int main() {
    int n = 0;
    int array[100];
    int x;

    double sum = 0.0;
    double sumSquare = 0.0;
    double SD = 0.0;
    double mean = 0.0;
    printf("Input student scores (type -1 to start calculation)\n");
    while (1) {
        printf("Enter score of student %d: ", n+1);
        scanf("%d", &x);
        if (x<0){break;}
        array[n] = x;
        n++;
    }

    for (int i=0; i<n; i++) {
        sum += array[i];
    }
    mean = sum/n;

    for (int i=0; i<n; i++) {
        sumSquare += array[i] * array[i];
    }
    SD = sqrt((sumSquare/n)-(mean*mean));

    printf("Mean score of %d students = %.1f, SD = %.2f\n", n, mean, SD);
}
