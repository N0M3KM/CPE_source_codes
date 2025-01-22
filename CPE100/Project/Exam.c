#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <math.h>

#define MAX_SIZE_STRING 256
#define TOTAL_OPTIONS 4 // Total valid option
#define HI_LO_MULTIPLY 7

float total_hi = 0.0; 
float total_lo = 0.0; 
float total_hi_lo = 0.0; 
int total_round = 0;
float balance = 1000.0;

typedef struct gameRecord { 
    float total_win;
    float total_loss;
} gameRecord;

gameRecord game_round[10]; // maximum round is 10

int isNumeric(const char *str)
{
    int hasDecimal = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '.')
        {
            if (hasDecimal)
            {

                return 0;
            }
            hasDecimal = 1;
        }
        else if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

// display user interface of the rolling phase.
void displayResultTerminal(int rollingResult[], int summation, char gameResult[3][5]) {
    printf("\n-------> Rolling Phase <-------\n");
    printf("The roll result is %d  %d  %d\n", rollingResult[0], rollingResult[1], rollingResult[2]);
    printf("The summation is %d. Please see your betting result below.\n", summation);
    
    if (total_hi!=0) {
        printf("1. Hi (x1) %.2f Baht. -> You %s %.2f Baht.\n", total_hi, gameResult[0], total_hi);
    } else if (total_hi==0) {
        printf("1. Hi (x1) 0 Baht. -> You get nothing.\n");
    }
    if (total_lo!=0) {
        printf("2. Lo (x1) %.2f Baht. -> You %s %.2f Baht.\n", total_lo, gameResult[1], total_lo);
    } else if (total_lo==0) {
        printf("2. Lo (x1) 0 Baht. -> You get nothing.\n");
    }
    if (total_hi_lo!=0) {
        printf("3. 11 Hi-Lo (x7) %.2f Baht.-> You %s %.2f Baht.\n", total_hi_lo, gameResult[2], total_hi_lo);
    } else if (total_hi_lo==0) {
        printf("3. 11 Hi-Lo (x7) 0 Baht. -> You get nothing.\n");
    }
}
// ------------------------------------------

// display user interface of the betting menu.
void displayMenuTerminal() {
    printf("\n-------> HI-LO FOREVER <-------\n");
    printf("Option for betting (Insert your choice)\n");
    printf("1. Hi(x1)\n");
    printf("2. Lo(x1)\n");
    printf("3. 11 Hi-Lo (x7)\n");
    printf("4. Finish betting phase\n");
}
// ------------------------------------------

// display user interface of exiting program.
void displayGoodbyeTerminal() {
    printf("\n==========================================\n");
    printf("Thank you for playing... Hope you enjoyed :)\n");
    printf("By Drarun Yookphan 67070501016\n");
    printf("==========================================\n");
}
// ------------------------------------------

void gameResult() {
    float temp = 0.0;
    printf("\nSummary\n");
    printf("Initial amount in your pocket : 1000.00 Baht.\n");
    for (int i=1;i<=total_round;i++) {
        if (game_round[i].total_win > game_round[i].total_loss) {
            float total_earn = game_round[i].total_win - game_round[i].total_loss;
            temp += total_earn;
            printf("Round [%d] : Win %.2f Baht.\n", i, total_earn);
        } else if (game_round[i].total_win < game_round[i].total_loss) {
            float total_loss = game_round[i].total_loss-game_round[i].total_win;
            temp -= total_loss;
            printf("Round [%d] : Loss %.2f Baht.\n", i, total_loss);
        } else if (game_round[i].total_win == game_round[i].total_loss) {
            printf("Round [%d] : Win equals loss, you get nothing.\n");
        }
    }

    if (temp==0) {
        printf("Good for you, you didn't win nor loss.\n");
    } else if (temp < 0) {
        printf("Please pay your debt %.2f Baht before leaving.\n", 0-temp);
    } else if (temp > 0) {
        printf("Please get your %.2f Baht before leaving.\n", temp);
    }
}



int randomNumber() {
    return rand()%6+1;
}

// do random dices
void rollingPhase() {
    int rollingResult[3] = {0,0,0};
    char gameResult[3][5] = {"LOSE", "LOSE", "LOSE"};
    int summation = 0;

    float t = total_hi + total_lo + total_hi_lo;

    balance -= t;

    game_round[total_round].total_loss += t;

    for (int i=0;i<3;i++) {
        rollingResult[i] = randomNumber();
        summation += rollingResult[i];
    }

    if (summation >= 3 && summation <= 10) {
        strcpy(gameResult[1], "WIN"); // lo result
        balance += total_lo * 2;
        game_round[total_round].total_win += total_lo*2;
    } else if (summation >= 12 && summation <= 18) {
        strcpy(gameResult[0], "WIN"); // hi result
        balance += total_hi * 2;
        game_round[total_round].total_win += total_hi*2;
    } else if (summation == 11) {
        strcpy(gameResult[1], "WIN"); // hi-lo result
        balance += total_hi_lo * HI_LO_MULTIPLY;
        game_round[total_round].total_win += total_hi_lo * HI_LO_MULTIPLY;
    }

    displayResultTerminal(rollingResult, summation, gameResult);
}
// ------------------------------------------

// start Hi
void PlaceHi(float *place) {
    total_hi += *place;
    printf("Your betting is %.2f.\n", *place);
    printf("Your betting is recorded.\n");
}
// start Lo
void PlaceLo(float *place) {
    total_lo += *place;
    printf("Your betting is %.2f.\n", *place);
    printf("Your betting is recorded.\n");
}
// start HiLo
void PlaceHiLo(float *place){
    total_hi_lo += *place;
    printf("Your betting is %.2f.\n", *place);
    printf("Your betting is recorded.\n");
} 

void TotalPlaceSummarize() {
    printf("Betting phase is ended. Below is the summary of your betting.\n");
    printf("1. Hi (x1) %.2f Baht.\n", total_hi);
    printf("2. Lo (x1) %.2f Baht.\n", total_lo);
    printf("3. 11 Hi-Lo (x7) %.2f Baht.\n", total_hi_lo);
}

// ask player to place their bet.
float placeBet() {
    float bet = 1.0;
    char *buffer = malloc(MAX_SIZE_STRING);
    if (!buffer)
    {
        printf("No memory to create buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return -1;

    }

    buffer[0] = '\0';

    do {
        if (!isNumeric(buffer) || bet <= 0)
        {   
            printf("\033[1;31mInvalid input! Please enter a valid number.\033[0m\n");
        }
        printf("\033[1;36mEnter your bet amount: \033[0m");
        fgets(buffer, MAX_SIZE_STRING, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    } while (sscanf(buffer, "%f", &bet) != 1 || !isNumeric(buffer) || bet <= 0);

    free(buffer);

    return bet;
}
// ------------------------------------------

int bettingPhase() {
    int option = 1;
    char *buffer = malloc(MAX_SIZE_STRING);
    if (buffer == NULL)
    {
        printf("No memory to create buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return -1;
    }
    do
    {
        do
        {
            displayMenuTerminal();
            if (option < 1 || option > TOTAL_OPTIONS)
            {
                printf("\033[1;31mInvalid option! Please select again.\033[0m\n");
            }

            printf("Select an option : ");
            fgets(buffer, MAX_SIZE_STRING, stdin);
            option = 0;
        } while (sscanf(buffer, "%d", &option) != 1);
    } while (option < 1 || option > TOTAL_OPTIONS);

    return option;
}
// ------------------------------------------

void playGame() {
    total_round += 1;
    game_round[total_round].total_loss = 0.0;
    game_round[total_round].total_win = 0.0;

    float placeAmount = 0.0;
    int option = 0;
    int previousOption = 0;

    while (option!=4) {
        option = bettingPhase();
        switch (option)
        {
        case 1:
            if (previousOption != option) {
                placeAmount = placeBet();
            }
            previousOption = option;
            PlaceHi(&placeAmount);
            break;
        case 2:
            if (previousOption != option) {
                placeAmount = placeBet();
            }
            previousOption = option;
            PlaceLo(&placeAmount);
            break;
        case 3:
            if (previousOption != option) {
                placeAmount = placeBet();
            }
            previousOption = option;
            PlaceHiLo(&placeAmount);
            break;
        case 4:
            TotalPlaceSummarize();
            break;
        }
    }

    rollingPhase();
}

// ask to play again
int askPlayAgain() {
    char option = 'y';
    char *buffer = malloc(MAX_SIZE_STRING);
    if (buffer == NULL)
    {
        printf("No memory to create buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return -1;
    }

    do
    {
        do
        {
            printf("\nDo you want to play again (y/n)? : ");
            if (option != 'y' && option != 'n')
            {
                printf("\033[1;31mInvalid option! Please select again.\033[0m\n");
            }

            fgets(buffer, MAX_SIZE_STRING, stdin);
            option = 'y';
        } while (sscanf(buffer, "%c", &option) != 1);
    } while (option != 'y' && option != 'n');

    if (option == 'y') {
        return 0;
    } else if (option == 'n') {
        gameResult();

        displayGoodbyeTerminal();
        return 1;
    }
}
// ------------------------------------------

int main() {
    srand(time(NULL));

    do {
        total_hi = 0.0;
        total_lo = 0.0;
        total_hi_lo = 0.0;
        playGame();
    } while (askPlayAgain()!=1);


    return 0;
}