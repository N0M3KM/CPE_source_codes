// 67070501016 Drarun Yookphan
// ===========================

#include <stdio.h>

int main() {
    int input = 0;
    int summation = 0;
    printf("Finding summation of input\n");
    for (int i=1;;i++) {
        printf("Enter input %d (type -1 to end this program):", i);
        scanf("%d", &input);
        if (input == -1) {
            printf("The summation of %d inputs is %d.", i-1, summation);
            break;
        } else {
            summation += input;
        }
    }
    return 0;
}
