#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int randomNumber() {
    return rand()%100+1;
}

void guessNumber(int* t_score, int* t_round) {
    int number = randomNumber();
    int i = 0;
    int ans;

    *t_round+=1;
    
    while (i<7) {
        printf("Guess the number between 1-100: ");
        scanf("%d", &ans);

        if (number<ans) {
            printf("The number is less than %d\n", ans);
        } else if (number>ans) {
            printf("The number is greater than %d\n", ans);
        } else if (ans==number) {
            printf("Congrats, You win!!\n");
            *t_score += 1;
            return;
        }
        i++;
    }
    if (i == 7 && ans != number) {
        printf("You lose... The number was %d\n", number);
    }
}

void Selection(int* t_score, int* t_round) {
    int ans;
    while (1) {
        printf("\n===== Guess the number =====\n");
        printf("1.) Play the game.\n");
        printf("2.) Leave the game and show the score.\n");
        printf("Please select a choice by typing '1' or '2' : ");
        scanf("%d", &ans);

        if (ans == 1) {
            guessNumber(t_score, t_round);
        } else if (ans == 2) {
            printf("End of the game... You played for %d round(s). Your total score is %d.\n", *t_round, *t_score);
            break;
        } else {
            printf("Incorrect format (only 1 or 2)!! Please select again.\n");
        }
    }
}

int main() {
    srand(time(NULL));

    int total_score = 0;
    int total_round = 0;

    Selection(&total_score, &total_round);
    return 0;
}