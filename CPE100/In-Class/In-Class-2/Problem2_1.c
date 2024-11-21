#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int randomNumber() {
    srand(time(NULL));
    return rand()%100+1;
}

void guessNumber(int number) {
    int i = 0;
    int num;

    while (i<7) {
        printf("Guess the number between 1-100 : ");
        scanf("%d", &num);

        if (number<num) {
            printf("The number is less than %d\n", num);
        } else if (number>num) {
            printf("The number is greater than %d\n", num);
        } else if (num==number) {
            printf("Congrats, You win!!\n");
        }
        i++;
    }
    printf("You lose... The number is %d\n", number);
}

int main() {
    int number = randomNumber();

    guessNumber(number);
    return 0;
}