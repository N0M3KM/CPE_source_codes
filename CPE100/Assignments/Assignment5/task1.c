//67070501016 Drarun Yookphan
#include <stdio.h>

void findLowest(int n, int arr[]) {
    int index = 1;
    int lowest = arr[0];

    for (int i=1;i<=n; i++) {
        if (lowest>arr[i]) {
            lowest = arr[i];
            index = i+1;
        }
    }
    printf("The minimum score is %d.\n", lowest);
    printf("Student %d has minimum score.", index);
}

int main() {
    int n = 0;
    int array[10];
    int x;

    printf("Enter student scores (type -1 to start calculation)\n");
    while (1) {
        printf("Enter score of student %d: ", n+1);
        scanf("%d", &x);
        if (x<0){break;}
        array[n] = x;
        n++;
    }

    findLowest(n, array);
}
