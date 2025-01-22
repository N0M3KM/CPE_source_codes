// 67070501016 Drarun Yookphan
// ===========================

#include <stdio.h>

int main() {
    int input1, input2;
    printf("Player 1, please enter a number :\n");
    scanf(" %d", &input1);
    while (1) {
        printf("Player 2, please guess the number :\n");
        scanf(" %d", &input2);
        if (input2 > input1) {
            printf("%d is too high.\n", input2);
        } else if (input2 < input1) {
            printf("%d is too low.\n", input2);
        } else if (input2 == input1) {
            printf("Your answer is correct. End of program.\n");
            break;
        }
    }
    return 0;
}
