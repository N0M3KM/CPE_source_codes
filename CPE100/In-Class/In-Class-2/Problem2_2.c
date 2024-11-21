#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int randomNumber() {
    srand(time(NULL));
    return rand()%100+1;
}

void guessNumber() {
    int number = randomNumber();
    int i = 0;
    int ans;

    while (i<7) {
        printf("Guess the number between 1-100 (Enter '-1' to stop the game): ");
        scanf("%d", &ans);

        if (ans == -1) {
            printf("You gave up after %d round(s). The number was %d.\n", i, number);
            return;
        }

        if (number<ans) {
            printf("The number is less than %d\n", ans);
        } else if (number>ans) {
            printf("The number is greater than %d\n", ans);
        } else if (ans==number) {
            printf("Congrats, You win!!\n");
        }
        i++;
    }
    printf("You lose... The number is %d\n", number);
}

int main() {
    guessNumber();
    return 0;
}