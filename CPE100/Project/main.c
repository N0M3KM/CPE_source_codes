#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <direct.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(ms) Sleep(ms)
#else
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#define CLEAR_SCREEN() printf("\033[H\033[J")
#define SLEEP(ms) usleep((ms) * 1000)
int getch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#define SHOW_CURSOR() printf("\033[?25h")
#define HIDE_CURSOR() printf("\033[?25l")
#define DIRECTORY_PERMISSIONS 0777

void make_directory(const char *name)
{
    struct stat st = {0};

    if (stat(name, &st) == -1)
    {
#ifdef __linux__
        mkdir(name, DIRECTORY_PERMISSIONS);
#else
        _mkdir(name);
#endif
    }
}

#define MAX_PLAYERS 100
#define MAX_SIZE_STRING 256
#define STARTER_BALANCE 50000
#define MIN_BET_FACTOR 0.1

const char *filename = "player_logs.txt";
const char *slotmachine_folder = "SlotMachine_Logs";
const char *blackjack_folder = "BlackJack_Logs";

char *SlotMachine_File(const char *playerName)
{
    char *filepath = malloc(MAX_SIZE_STRING);
    if (!filepath)
    {
        perror("Failed to allocate memory");
        return NULL;
    }
    snprintf(filepath, MAX_SIZE_STRING, "%s/%s.txt", slotmachine_folder, playerName);
    return filepath;
}
char *BlackJack_File(const char *playerName)
{
    char *filepath = malloc(MAX_SIZE_STRING);
    if (!filepath)
    {
        perror("Failed to allocate memory");
        return NULL;
    }
    snprintf(filepath, MAX_SIZE_STRING, "%s/%s.txt", blackjack_folder, playerName);
    return filepath;
}

const float MIN_BET_PERCENTAGE = MIN_BET_FACTOR * 100;

#define DECK_SIZE 52
#define BLACKJACK 21
#define DEALER_HIT 17

void moveCursorTo(int line, int column)
{
    printf("\033[%d;%dH", line, column);
}
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

char *getFilePathForGameType(const char *playerName, const char *gameType)
{
    if (strcmp(gameType, "SlotMachine") == 0)
    {
        return SlotMachine_File(playerName);
    }
    else if (strcmp(gameType, "BlackJack") == 0)
    {
        return BlackJack_File(playerName);
    }
    return NULL;
}
int countLinesWithWord(const char *word, const char *playerName, const char *gameType)
{
    char *filepath = getFilePathForGameType(playerName, gameType);
    if (filepath == NULL)
    {
        return -1;
    }

    FILE *game_log = fopen(filepath, "r");

    if (game_log == NULL)
    {
        fprintf(stderr, "You haven't played %s yet\n", gameType);
        free(filepath);
        return -1;
    }
    char *count_buffer = malloc(MAX_SIZE_STRING);
    int count = 0;
    rewind(game_log);
    while (fgets(count_buffer, MAX_SIZE_STRING, game_log) != NULL)
    {

        if (strstr(count_buffer, word) != NULL)
        {
            count++;
        }
    }

    rewind(game_log);
    fclose(game_log);
    free(count_buffer);
    free(filepath);
    return count;
}
int getGameCount(const char *playerName, const char *gameType)
{
    char *filepath = getFilePathForGameType(playerName, gameType);
    if (filepath == NULL)
    {
        return -1;
    }

    FILE *game_log = fopen(filepath, "r");
    if (game_log == NULL)
    {
        free(filepath);
        return -1;
    }
    rewind(game_log);
    int gameCount = 0;
    char *line = malloc(MAX_SIZE_STRING);
    if (line == NULL)
    {
        printf("No memory to create line\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return -1;
    }

    while (fgets(line, MAX_SIZE_STRING, game_log))
    {
        if (strstr(line, "Game: ") != NULL)
        {
            gameCount++;
        }
    }
    rewind(game_log);
    fclose(game_log);
    free(line);
    free(filepath);
    return gameCount;
}
void LoadingScreen(const char *playerName, float *balance)
{
    int progress = 0;
    int total = 100;
    CLEAR_SCREEN();

    HIDE_CURSOR();
    printf("\033[1;33mLoading... Please wait... \033[0m\n");
    printf("Welcome %s.\n", playerName);
    if (*balance == 0)
    {

        char *filepath = SlotMachine_File(playerName);
        char *filepath2 = BlackJack_File(playerName);
        printf("\033[1;31mYou have no money left! Your data will be reset.\033[0m\n");
        *balance = STARTER_BALANCE;
        remove(filepath);
        remove(filepath2);
    }
    while (progress <= total)
    {
        int barWidth = 50;
        int pos = barWidth * progress / total;
        printf("\033[1;33m[\033[0m");
        for (int i = 0; i < barWidth; i++)
        {
            if (i < pos)
                printf("\033[1;33m=\033[0m");
            else if (i == pos)
                printf("\033[1;33m>\033[0m");
            else
                printf("\033[1;33m \033[0m");
        }
        printf("\033[1;33m] %d%%\033[0m\r", (progress * 100) / total);
        fflush(stdout);

        progress++;
        int delay = 50 + (rand() % 50);
        SLEEP(delay); // Delay for effect
    }
    printf("\n\033[1;33mLoading Complete!\033[0m\n");
    SLEEP(1000);
    SHOW_CURSOR();
}
void SavePlayerData(const char *playerName, float balance)
{
    char *file_buffer = malloc(MAX_SIZE_STRING);
    if (file_buffer == NULL)
    {
        perror("Failed to allocate memory");
        return;
    }

    int found = 0;

    FILE *player_log = fopen(filename, "r");
    if (player_log == NULL)
    {
        perror("Error opening player log file");
        free(file_buffer);
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL)
    {
        perror("Error creating temporary file");
        free(file_buffer);
        fclose(player_log);
        return;
    }

    while (fgets(file_buffer, MAX_SIZE_STRING, player_log) != NULL)
    {
        if (strncmp(file_buffer, "Player: ", 8) == 0)
        {
            char existingPlayerName[MAX_SIZE_STRING];
            sscanf(file_buffer + 8, "%s", existingPlayerName);

            if (strcmp(existingPlayerName, playerName) == 0)
            {
                fprintf(temp_file, "Player: %s Balance: %.2f\n", playerName, balance);
                found = 1;
                continue;
            }
        }
        fputs(file_buffer, temp_file);
    }

    if (!found)
    {
        fprintf(temp_file, "Player: %s Balance: %.2f\n", playerName, balance);
    }
    fclose(player_log);
    fclose(temp_file);
    free(file_buffer);

    if (remove(filename) != 0)
    {
        perror("Error deleting original file");
    }
    if (rename("temp.txt", filename) != 0)
    {
        perror("Error renaming temporary file");
    }
}
void getPlayerName(char *playerName)
{
    printf("Enter your name: ");
    fgets(playerName, MAX_SIZE_STRING, stdin);
    if ((strlen(playerName) > 0) && (playerName[strlen(playerName) - 1] == '\n'))
    {
        playerName[strlen(playerName) - 1] = '\0';
    }
    // Remove spaces
    int non_space_count = 0;
    for (int i = 0; playerName[i] != '\0'; i++)
    {
        if (playerName[i] != ' ')
        {
            playerName[non_space_count++] = playerName[i];
        }
    }
    playerName[non_space_count] = '\0';
}
void PrintCasinoLogo()
{
    printf("\033[1;33m        _..._                                            .-'''-.      \033[0m\n");
    printf("\033[1;33m     .-'_..._''.                                        '   _    \\   \033[0m\n");
    printf("\033[1;33m   .' .'      '.\\                     .--.   _..._    /   /` '.   \\ \033[0m\n");
    printf("\033[1;33m  / .'                                |__| .'     '. .   |     \\  '  \033[0m\n");
    printf("\033[1;33m . '                                  .--..   .-.   .|   '      |  '  \033[0m\n");
    printf("\033[1;33m | |                 __               |  ||  '   '  |\\    \\     / / \033[0m\n");
    printf("\033[1;33m | |              .:--.'.         _   |  ||  |   |  | `.   ` ..' /    \033[0m\n");
    printf("\033[1;33m . '             / |   \\ |      .' |  |  ||  |   |  |    '-...-'`    \033[0m\n");
    printf("\033[1;33m  \\ '.          .`\" __ | |     .   | /|  ||  |   |  |               \033[0m\n");
    printf("\033[1;33m   '. `._____.-'/ .'.''| |   .'.'| |//|__||  |   |  |                 \033[0m\n");
    printf("\033[1;33m     `-.______ / / /   | |_.'.'.-'  /     |  |   |  |                 \033[0m\n");
    printf("\033[1;33m              `  \\ \\._,\\ '/.'   \\_.'      |  |   |  |             \033[0m\n");
    printf("\033[1;33m                  `--'  `\"                '--'   '--'                \033[0m\n");
    printf("\033[1;33m                       Welcome to the Casino!                         \033[0m\n");
}
void showPlayerNames(FILE *player_log)
{
    char *playerName = malloc(MAX_SIZE_STRING);
    rewind(player_log);
    if (player_log == NULL)
    {
        printf("No memory to create player_log\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return;
    }
    while (fgets(playerName, MAX_SIZE_STRING, player_log))
    {
        if ((strlen(playerName) > 0) && (playerName[strlen(playerName) - 1] == '\n'))
        {
            playerName[strlen(playerName) - 1] = '\0';
        }

        printf("%s\n", playerName);
    }
    free(playerName);
}
float loadPlayerBalance(FILE *player_log, const char *playerName)
{
    rewind(player_log);
    char *line = malloc(MAX_SIZE_STRING);
    float balance = -1.0f;

    if (line == NULL)
    {
        printf("No memory to create line\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return -1;
    }

    while (fgets(line, MAX_SIZE_STRING, player_log))
    {
        if (strstr(line, playerName) != NULL && strstr(line, "Player: ") == line)
        {
            int parsed = sscanf(line, "Player: %*s Balance: %f", &balance);
            if (parsed == 1)
            {
                free(line);
                return balance;
            }
        }
    }

    free(line);
    return -1;
}

void Gamehistory(const char *playerName)
{
    int slotMachineWinCount = countLinesWithWord("[ WIN ]", playerName, "SlotMachine");
    int slotMachineLoseCount = countLinesWithWord("[ LOSE ]", playerName, "SlotMachine");
    int slotMachineGameCount = getGameCount(playerName, "SlotMachine");

    int blackjackWinCount = countLinesWithWord("[ WIN ]", playerName, "BlackJack");
    int blackjackLoseCount = countLinesWithWord("[ LOSE ]", playerName, "BlackJack");
    int blackjackTieCount = countLinesWithWord("[ TIE ]", playerName, "BlackJack");
    int blackjackGameCount = getGameCount(playerName, "BlackJack");

    char *blackJack = BlackJack_File(playerName);

    char *slotMachine = SlotMachine_File(playerName);

    FILE *blackjack_log = fopen(blackJack, "r");

    FILE *slotmachine_log = fopen(slotMachine, "r");

    char choice = '1';
    int second_page = 0;
    char *blackjack_line = malloc(MAX_SIZE_STRING);
    if (blackjack_line == NULL)
    {
        printf("No memory to create blackjack_line\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return;
    }
    char *slotmachine_line = malloc(MAX_SIZE_STRING);
    if (slotmachine_line == NULL)
    {
        printf("No memory to create slotmachine_line\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return;
    }
    do
    {
        rewind(slotmachine_log);
        rewind(blackjack_log);
        CLEAR_SCREEN();
        if (!second_page)
        {

            printf("\033[1;33m----------------------------- Game History (SLOT MACHINE) -----------------------------\033[0m\n");
            printf("\033[1;36mTotal Games Played: %d\t\tWin: %d\t\tLose: %d\033[0m\n", slotMachineGameCount, slotMachineWinCount, slotMachineLoseCount);
            while (fgets(slotmachine_line, MAX_SIZE_STRING, slotmachine_log) != NULL)
            {
                printf("%s", slotmachine_line);
            }
            printf("\nPress [ 1 ] to return to menu.\t\t\tPress [ANY KEY] to go to the next page.\n");
        }
        else
        {
            printf("\033[1;33m------------------------------- Game History (BLACKJACK) ------------------------------\033[0m\n");
            printf("\033[1;36mTotal Games Played: %d\t\tWin: %d\t\tLose: %d\t\tTie: %d\033[0m\n", blackjackGameCount, blackjackWinCount, blackjackLoseCount, blackjackTieCount);
            while (fgets(blackjack_line, MAX_SIZE_STRING, blackjack_log) != NULL)
            {
                printf("%s", blackjack_line);
            }
            printf("\nPress [ 1 ] to go back to the previous page.\n");
        }

        choice = getchar();
        while (getchar() != '\n')
            ;

        if (choice == '1')
        {
            if (second_page)
            {
                second_page = 0;
            }
            else
            {
                break;
            }
        }
        else
        {
            second_page = !second_page;
        }

    } while (1);
    fclose(blackjack_log);
    fclose(slotmachine_log);
    free(blackjack_line);
    free(slotmachine_line);
    free(blackJack);
    free(slotMachine);
}

#define NUM_PROFILE_PICS 2

void displayProfilePic(int picID)
{
    switch (picID)
    {
    case 1:
        printf("\033[1;33m__________________\n");
        printf("|                |\n");
        printf("|     /\\_/\\      |\n");
        printf("|    ( o.o )     |\n");
        printf("|     > ^ <      |\n");
        printf("|                |\n");
        printf("__________________\033[0m\n");
        break;

    case 2:
        printf("\033[1;33m__________________\n");
        printf("|    / \\__       |\n");
        printf("|   (    @\\___   |\n");
        printf("|   /         O  |\n");
        printf("|  /   (_____/   |\n");
        printf("| /_____/   U    |\n");
        printf("__________________\033[0m\n");
        break;

    default:
        printf("Invalid profile picture ID\n");
        break;
    }
}
void Profile(const char *playerName, float balance)
{
    int picID = rand() % NUM_PROFILE_PICS + 1;
    displayProfilePic(picID);
    int slotMachineWinCount = 0;
    int slotMachineLoseCount = 0;
    int slotMachineGameCount = 0;
    int slotMachineWinRate = 0;
    int blackjackWinCount = 0;
    int blackjackLoseCount = 0;
    int blackjackTieCount = 0;
    int blackjackGameCount = 0;
    int blackjackWinRate = 0;

    if (getGameCount(playerName, "SlotMachine") != -1)
    {
        slotMachineWinCount = countLinesWithWord("[ WIN ]", playerName, "SlotMachine");
        slotMachineLoseCount = countLinesWithWord("[ LOSE ]", playerName, "SlotMachine");
        slotMachineGameCount = getGameCount(playerName, "SlotMachine");
        slotMachineWinRate = (slotMachineWinCount * 100) / slotMachineGameCount;
    }
    if (getGameCount(playerName, "BlackJack") != -1)
    {
        blackjackWinCount = countLinesWithWord("[ WIN ]", playerName, "BlackJack");
        blackjackLoseCount = countLinesWithWord("[ LOSE ]", playerName, "BlackJack");
        blackjackTieCount = countLinesWithWord("[ TIE ]", playerName, "BlackJack");
        blackjackGameCount = getGameCount(playerName, "BlackJack");
        blackjackWinRate = (blackjackWinCount * 100) / blackjackGameCount;
    }
    int totalPlayed = slotMachineGameCount + blackjackGameCount;
    int totalWin = slotMachineWinCount + blackjackWinCount;
    int totalLose = slotMachineLoseCount + blackjackLoseCount;
    float totalWinrate = (totalWin * 100.0f) / totalPlayed;
    if (getGameCount(playerName, "SlotMachine") == -1 && getGameCount(playerName, "BlackJack") == -1)
    {
        printf("You haven't played anything.\n");
    }
    printf("\n\033[1;37mPlayer: %s Balance: %.2f\033[0m\n", playerName, balance);
    printf("\n-------------------------------- TOTAL --------------------------------\n");
    printf("\033[1;36mTotal played: %d\t\tTotal win: %d\tTotal lose: %d\tTotal winrate: %.2f\033[0m\n", totalPlayed, totalWin, totalLose, totalWinrate);
    printf("\n------------------------------ BLACKJACK ------------------------------\n");
    printf("\033[1;36mBlackjack played: %d\t\tWin: %d\tLose: %d\tTie: %d\tWinRate: %.2f\033[0m\n", blackjackGameCount, blackjackWinCount, blackjackLoseCount, blackjackTieCount, blackjackWinRate);
    printf("\n----------------------------- SLOT MACHINE ----------------------------\n");
    printf("\033[1;36mSlotMachine played: %d\t\tWin: %d\tLose: %d\tWinRate: %.2f\033[0m\n", slotMachineGameCount, slotMachineWinCount, slotMachineLoseCount, slotMachineWinRate);
    printf("\nPress [ANY KEYS] to return to the menu.\n");
    getchar();
}

typedef struct
{
    char playerName[MAX_SIZE_STRING];
    float balance;
} Player;
int compareLines(const void *a, const void *b)
{
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;

    if (playerA->balance < playerB->balance)
    {
        return 1;
    }
    if (playerA->balance > playerB->balance)
    {
        return -1;
    }
    return 0;
}
void Leaderboard()
{
    FILE *player_log = fopen(filename, "r");
    if (!player_log)
    {
        perror("Error opening file");
        return;
    }

    printf("\033[1;33m=================================================\n");
    printf("                   Leaderboard                   \n");
    printf("=================================================\033[0m\n");

    Player players[MAX_PLAYERS];
    int count = 0;

    char line[MAX_SIZE_STRING];
    while (fgets(line, MAX_SIZE_STRING, player_log) && count < MAX_PLAYERS)
    {
        if (sscanf(line, "Player: %s Balance: %f", players[count].playerName, &players[count].balance) == 2)
        {
            count++;
        }
        else
        {
            printf("Warning: Could not parse line: %s\n", line);
        }
    }
    fclose(player_log);

    qsort(players, count, sizeof(Player), compareLines);

    for (int i = 0; i < count; i++)
    {
        printf("%d. Player: %-20s Balance: \033[1;37m%.2f\033[0m\n", i + 1, players[i].playerName, players[i].balance);
    }

    printf("\033[1;33m=================================================\033[0m\n");
    printf("Press [ANY KEY] to return to the menu.\n");
    getchar();
}

void addData_SlotMachine(const char *playerName, int result[], int reel, float balance, float bet, int doWin)
{
    char *filepath = SlotMachine_File(playerName);
    FILE *slotmachine_log = fopen(filepath, "a+");

    if (!slotmachine_log)
    {
        CLEAR_SCREEN();
        printf("Error creating slotmachine_log!\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return;
    }
    fseek(slotmachine_log, 0, SEEK_END);
    int GameCount = getGameCount(playerName, "SlotMachine") + 1;
    fprintf(slotmachine_log, "Game: %d\t [ %s ]\t", GameCount, doWin ? "WIN" : "LOSE");

    for (int i = 0; i < reel; i++)
    {
        fprintf(slotmachine_log, " [ %d ]", result[i]);
    }

    fprintf(slotmachine_log, "\tBet: %.2f  \tBalance: %.2f\n", bet, balance);
    fclose(slotmachine_log);
    free(filepath);
}
int JackpotChecker_IfAllIndexAreEqual(int result[], int size)
{
    if (size == 0)
    {
        return 1;
    }

    int firstElement = result[0];
    for (int i = 1; i < size; i++)
    {
        if (result[i] != firstElement)
        {
            return 0;
        }
    }
    return 1;
}
void SlotMachine(FILE *player_log, const char *playerName, float *balance, int *option)
{
    int doWin = 0;
    float bet = *balance;
    char choice = '1';
    char *slot_buffer = malloc(MAX_SIZE_STRING);
    if (!slot_buffer)
    {
        printf("No memory to create slot_buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return;
    }
    int reel = 0;
    int BET_MULTIPLIER = 0;

    switch (*option)
    {
    case 1:
        reel = 3;
        BET_MULTIPLIER = 15;
        break;
    case 2:
        reel = 5;
        BET_MULTIPLIER = 45;
        break;
    case 3:
        reel = 7;
        BET_MULTIPLIER = 85;
        break;
    case 4:
        reel = 9;
        BET_MULTIPLIER = 150;
        break;
    case 5:
        reel = 15;
        BET_MULTIPLIER = 600;
        break;
    default:
        printf("Invalid option!\n");
        free(slot_buffer);
        return;
    }
    slot_buffer[0] = '\0';
    do
    {
        int *result = malloc(reel * sizeof(int));
        if (!result)
        {
            printf("No memory to create result array\n");
            printf("Press [ENTER] to exit....");
            getchar();
            return;
        }
        float minBet = *balance * MIN_BET_FACTOR;
        do
        {
            do
            {
                CLEAR_SCREEN();
                for (int i = 0; i < reel; i++)
                    result[i] = 9;
                int frameWidth = (reel * 7) + 1;
                for (int i = 0; i <= frameWidth; i++)
                    printf("\033[1;33m=\033[0m");
                printf("\n\033[1;33m|\033[0m");
                for (int i = 0; i < reel; i++)
                    printf("\033[1;32m [ %d ] \033[0m", result[i]);
                printf("|\n");
                for (int i = 0; i <= frameWidth; i++)
                    printf("\033[1;33m=\033[0m");
                printf("\n");

                printf("\n\033[1;33mSlot Machine %d symbols match: %dx bet\033[0m", reel, BET_MULTIPLIER);
                printf("\n\033[1;37mPlayer: %s\tBalance: %.2f\033[0m", playerName, *balance);
                if (choice == '1' || bet < minBet || bet > *balance || !isNumeric(slot_buffer))
                {
                    if (!isNumeric(slot_buffer))
                    {
                        printf("\n\033[1;31mInvalid input! Please enter a valid number.\033[0m");
                    }
                    if (bet < minBet && isNumeric(slot_buffer))
                    {
                        printf("\n\033[1;31mThe bet amount is too low. Please enter at least %.1f%% of your balance.\033[0m", MIN_BET_PERCENTAGE);
                    }
                    if (bet > *balance && isNumeric(slot_buffer))
                    {
                        printf("\n\033[1;31mYou don't have enough money.\033[0m");
                    }
                    printf("\n\033[1;36mEnter your bet amount (minimum %.1f%% of balance: %.2f): \033[0m", MIN_BET_PERCENTAGE, minBet);
                    fgets(slot_buffer, MAX_SIZE_STRING, stdin);
                    slot_buffer[strcspn(slot_buffer, "\n")] = '\0';
                }
                else
                {
                    printf("\n\033[1;36mEnter your bet amount (minimum %.1f%% of balance: %.2f): %.2f\033[0m", MIN_BET_PERCENTAGE, minBet, bet);
                }
            } while (sscanf(slot_buffer, "%f", &bet) != 1 || !isNumeric(slot_buffer));
        } while (bet < minBet || bet > *balance);

        *balance -= bet;
        moveCursorTo(6, 0);
        printf("\033[1;37mPlayer: %s\tBalance: %.2f                \033[0m", playerName, *balance);

        for (int i = 0; i < reel; i++)
        {
            result[i] = (rand() % 9) + 1;
        }
        moveCursorTo(9, 0);
        printf("Spinning the slot machine...\n");
        printf("Press any key to stop the slot machine!\n");

        HIDE_CURSOR();
        while (!kbhit())
        {
            for (int i = 0; i < reel; i++)
            {
                result[i] = (rand() % 9) + 1;
                moveCursorTo(2, 5 + (i * 7));
                printf("\033[1;32m%d\033[0m", result[i]);
            }

            fflush(stdout);
            SLEEP(100);
        }
        while (getchar() != '\n')
            ;

        moveCursorTo(9, 0);

        int Jackpot = JackpotChecker_IfAllIndexAreEqual(result, reel);
        if (Jackpot)
        {
            printf("Jackpot! You won: %.2f\n", bet * BET_MULTIPLIER);
            *balance += bet * BET_MULTIPLIER;
            doWin = 1;
        }
        else
        {
            printf("You lost your bet of: %.2f\n", bet);
            doWin = 0;
        }
        moveCursorTo(6, 0);
        printf("\033[1;37mPlayer: %s\tBalance: %.2f                \033[0m", playerName, *balance);
        addData_SlotMachine(playerName, result, reel, *balance, bet, doWin);
        moveCursorTo(9, 0);
        SHOW_CURSOR();
        printf("\nWould you like to play again?                 ");
        printf("\nPress [ENTER] to spin again ");
        printf("\nPress 1 to change the bet: ");
        printf("\nPress 2 to return to the menu: ");
        choice = getchar();
        while (getchar() != '\n')
            ;
    } while (choice != '2' && *balance > 0);
    free(slot_buffer);
    *option = 1;
}

void addData_BlackJack(const char *playerName, int playerValue, int dealerValue, float balance, float bet, int doWin)
{
    char *filepath = BlackJack_File(playerName);

    FILE *blackjack_log = fopen(filepath, "a+");
    if (blackjack_log == NULL)
    {
        CLEAR_SCREEN();
        printf("Error creating blackjack_log!\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return;
    }
    int GameCount = getGameCount(playerName, "BlackJack") + 1;
    fseek(blackjack_log, 0, SEEK_END);
    fprintf(blackjack_log, "Game: %d", GameCount);
    if (doWin)
    {
        fprintf(blackjack_log, " [ WIN ]");
    }
    else if (doWin == -1)
    {
        fprintf(blackjack_log, " [ TIE ]");
    }
    else
    {
        fprintf(blackjack_log, " [ LOSE ]");
    }
    fprintf(blackjack_log, "\tPlayer: [ %d ] \tDealer: [ %d ]", playerValue, dealerValue);
    fprintf(blackjack_log, "\tBet: %.2f  Balance: %.2f\n", bet, balance);
    fflush(blackjack_log);
    fclose(blackjack_log);
    free(filepath);
}
void printBlackjackLogo()
{
    printf("\033[1;33m.______   __          ___       ______  __  ___        __      ___       ______  __  ___            \033[0\n");
    printf("\033[1;33m|   _  \\ |  |        /   \\     /      ||  |/  /       |  |    /   \\     /      ||  |/  /         \033[0m\n");
    printf("\033[1;33m|  |_)  ||  |       /  ^  \\   |  ,----'|  '  /        |  |   /  ^  \\   |  ,----'|  '  /           \033[0m\n");
    printf("\033[1;33m|   _  < |  |      /  /_\\  \\  |  |     |    <   .--.  |  |  /  /_\\  \\  |  |     |    <          \033[0m\n");
    printf("\033[1;33m|  |_)  ||  `----./  _____  \\ |  `----.|  .  \\  |  `--'  | /  _____  \\ |  `----.|  .  \\         \033[0m\n");
    printf("\033[1;33m|______/ |_______/__/     \\__\\ \\______||__|\\__\\  \\______/ /__/     \\__\\ \\______||__|\\__\\ \033[0m\n");
    printf("                                                                                                      \n");
    printf("\033[1;33m                          Blackjack Player EV Average: 0.43                                           \033[0m\n");
    printf("\033[1;33m                          Blackjack Dealer EV Average: 0.57                                           \033[0m\n");
    printf("                                                                                                      \n");
}
void initializeBlackjackDeck(int deck[])
{
    int cardValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10}; // A, 2-10, J, Q, K
    int index = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            deck[index++] = cardValues[j];
        }
    }
}
void shuffleDeck(int deck[])
{
    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}
void dealCard(int *deck, int *index, int *hand, int handSize)
{
    hand[handSize] = deck[(*index)++];
}
int calculateHandValue(int *hand, int handSize)
{
    int value = 0;
    int aces = 0;
    int aces_position = 0;
    for (int i = 0; i < handSize; i++)
    {
        if (hand[i] == 1)
        {
            aces_position = i;
            aces++; // Face cards are worth 10
        }
        else
        {
            value += hand[i];
        }
    }
    while (aces > 0)
    {
        if (value + 11 > BLACKJACK)
        {
            value += 1; // Aces are worth 1
        }
        else
        {
            hand[aces_position] = 11;
            value += 11; // Aces are worth 11 initially
        }
        aces--;
    }

    return value;
}
void initializeBlackjackArea(int PlayerHand[], int DealerHand[])
{
    moveCursorTo(14, 0);
    printf("Shuffling the deck...\n");
    SLEEP(1500);
    moveCursorTo(14, 0);
    printf("Dealing cards...                  \n");
    printf("Dealer Hand:             \n");
    printf("\n\t[ DECKS ]\n");
    printf("\nPlayer Hand:               \n");
    SLEEP(500);
    moveCursorTo(14, 0);
    printf("Dealing cards...                     \n");
    printf("Dealer Hand: \n");
    printf("\n\t[ DECKS ]\n");
    printf("\nPlayer Hand: \033[1;32m[ %d ]\033[0m\n", PlayerHand[0]);
    SLEEP(500);
    moveCursorTo(14, 0);
    printf("Dealing cards...                     \n");
    printf("Dealer Hand: \033[1;32m[ ? ]\033[0m\n");
    printf("\n\t[ DECKS ]\n");
    printf("\nPlayer Hand: \033[1;32m[ %d ]\033[0m\n", PlayerHand[0]);
    SLEEP(500);
    moveCursorTo(14, 0);
    printf("Dealing cards...                        \n");
    printf("Dealer Hand: \033[1;32m[ ? ]\033[0m \n");
    printf("\n\t[ DECKS ]\n");
    printf("\nPlayer Hand: \033[1;32m[ %d ] [ %d ]\033[0m\n", PlayerHand[0], PlayerHand[1]);
    SLEEP(500);
    moveCursorTo(14, 0);
    printf("All card are dealt!         \n");
    printf("Dealer Hand: \033[1;32m[ ? ] [ %d ]\033[0m \n", DealerHand[1]);
    printf("\n\t[ DECKS ]\n");
    printf("\nPlayer Hand: \033[1;32m[ %d ] [ %d ]\033[0m\n", PlayerHand[0], PlayerHand[1]);
}
void BlackJack(FILE *player_log, const char *playerName, float *balance, int *option)
{
    float bet = *balance;
    float minBet = *balance * MIN_BET_FACTOR;
    char choice = '1';
    char *bet_buffer = malloc(MAX_SIZE_STRING);
    if (bet_buffer == NULL)
    {
        printf("No memory to create bet_buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return;
    }
    bet_buffer[0] = '\0';
    do
    {
        int doWin = 0;
        CLEAR_SCREEN();
        minBet = *balance * MIN_BET_FACTOR;
        do
        {
            do
            {

                CLEAR_SCREEN();
                printBlackjackLogo();
                printf("\033[1;37mPlayer: %s\tBalance: %.2f\033[0m", playerName, *balance);
                if (choice == '1' || bet < minBet || bet > *balance || !isNumeric(bet_buffer))
                {
                    if (!isNumeric(bet_buffer))
                    {
                        printf("\n\033[1;31mInvalid input! Please enter a valid number.\033[0m");
                    }
                    if (bet < minBet && isNumeric(bet_buffer))
                    {
                        printf("\n\033[1;31mThe bet amount is too low. Please enter at least %.1f%% of your balance.\033[0m", MIN_BET_PERCENTAGE);
                    }
                    if (bet > *balance && isNumeric(bet_buffer))
                    {
                        printf("\n\033[1;31mYou don't have enough money.\033[0m");
                    }
                    printf("\n\033[1;36mEnter your bet amount (minimum %.1f%% of balance: %.2f): \033[0m", MIN_BET_PERCENTAGE, minBet);
                    fgets(bet_buffer, MAX_SIZE_STRING, stdin);
                    bet_buffer[strcspn(bet_buffer, "\n")] = '\0';
                }
                else
                {
                    printf("\n\033[1;36mEnter your bet amount (minimum %.1f%% of balance: %.2f): %.2f\033[0m", MIN_BET_PERCENTAGE, minBet, bet);
                }
            } while (sscanf(bet_buffer, "%f", &bet) != 1 || !isNumeric(bet_buffer));
        } while (bet < minBet || bet > *balance);

        *balance -= bet;
        HIDE_CURSOR();
        moveCursorTo(11, 0);
        printf("\033[1;37mPlayer: %s\tBalance: %.2f                        \033[0m", playerName, *balance);

        int cardDeck[DECK_SIZE];
        int PlayerHand[10], DealerHand[10];
        int index = 0;
        int dealerHandSize = 0, playerHandSize = 0;
        char gameChoice = '0';

        initializeBlackjackDeck(cardDeck);
        shuffleDeck(cardDeck);
        dealCard(cardDeck, &index, PlayerHand, playerHandSize++);
        dealCard(cardDeck, &index, PlayerHand, playerHandSize++);
        dealCard(cardDeck, &index, DealerHand, dealerHandSize++);
        dealCard(cardDeck, &index, DealerHand, dealerHandSize++);
        calculateHandValue(PlayerHand, playerHandSize);
        initializeBlackjackArea(PlayerHand, DealerHand);

        SHOW_CURSOR();
        moveCursorTo(20, 0);
        printf("\nWhat would you like to do?");
        printf("\nPress [ENTER] or [ANY KEYS] to hit");
        printf("\nPress [S] to stand");
        printf("\nPress [D] to double down\n");
        gameChoice = getchar();
        while (getchar() != '\n')
            ;
        HIDE_CURSOR();
        if (gameChoice == 'D' || gameChoice == 'd')
        {
            *balance -= bet;
            bet *= 2;
            moveCursorTo(11, 0);
            printf("\033[1;37mPlayer: %s\tBalance: %.2f   \033[0m", playerName, *balance);
            printf("\n\033[1;36mEnter your bet amount (minimum %.1f%% of balance: %.2f): %.2f            \033[0m", MIN_BET_PERCENTAGE, minBet, bet);
            printf("\n                                                                          ");
            dealCard(cardDeck, &index, PlayerHand, playerHandSize++);
            moveCursorTo(14, 0);
            printf("Double down! your bet is now x2 and you get one more card.");
            printf("\nDealer Hand: \033[1;32m[ ? ] [ %d ]\033[0m", DealerHand[1]);
            printf("\n\n\t[ DECKS ]\n");
            calculateHandValue(PlayerHand, playerHandSize);
            printf("\nPlayer Hand: \033[1;32m[ %d ] [ %d ] [ %d ]\033[0m", PlayerHand[0], PlayerHand[1], PlayerHand[2]);
            SLEEP(1000);
        }
        else
        {
            while (gameChoice != 'S' && gameChoice != 's' && calculateHandValue(PlayerHand, playerHandSize) < BLACKJACK)
            {
                moveCursorTo(14, 0);
                printf("Player Hit!                                                 ");
                dealCard(cardDeck, &index, PlayerHand, playerHandSize++);
                calculateHandValue(PlayerHand, playerHandSize);
                moveCursorTo(19, 0);
                printf("Player Hand:");
                for (int i = 0; i < playerHandSize; i++)
                {
                    printf("\033[1;32m [ %d ]\033[0m", PlayerHand[i]);
                }
                if (calculateHandValue(PlayerHand, playerHandSize) > BLACKJACK || calculateHandValue(PlayerHand, playerHandSize) == BLACKJACK)
                {
                    break;
                }
                SHOW_CURSOR();
                moveCursorTo(21, 0);
                printf("What would you like to do?\n");
                printf("Press [ENTER] or [ANY KEYS] to hit\n");
                printf("Press S to stand             \n");
                printf("                                                  \n");
                printf("                                                  \n");
                moveCursorTo(26, 0);
                gameChoice = getchar();
                while (getchar() != '\n')
                    ;
                HIDE_CURSOR();
            }
        }
        moveCursorTo(14, 0);
        printf("Player Stand.                                                ");
        SLEEP(1000);
        HIDE_CURSOR();
        while (calculateHandValue(DealerHand, dealerHandSize) < DEALER_HIT)
        {
            dealCard(cardDeck, &index, DealerHand, dealerHandSize++);
        }
        moveCursorTo(14, 0);
        printf("Dealer Hit!                                                  ");
        printf("\nDealer Hand:");
        for (int i = 0; i < dealerHandSize; i++)
        {
            printf("\033[1;32m [ %d ]\033[0m", DealerHand[i]);
            SLEEP(500);
        }

        int playerValue = calculateHandValue(PlayerHand, playerHandSize);
        int dealerValue = calculateHandValue(DealerHand, dealerHandSize);
        moveCursorTo(14, 0);
        if (playerValue == BLACKJACK && dealerValue != BLACKJACK)
        {
            printf("Blackjack! You won: %.2f                                 \n", bet * 2.5);
            doWin = 1;
            *balance += bet * 2.5;
        }
        else if (playerValue > BLACKJACK)
        {

            printf("Player busts! You lost: %.2f                          \n", bet);
            doWin = 0;
        }
        else if (dealerValue > BLACKJACK)
        {
            printf("Dealer busts! You won: %.2f                            \n", bet * 2);
            doWin = 1;
            *balance += bet * 2;
        }
        else if (playerValue > dealerValue)
        {
            printf("You won: %.2f                                   \n", bet);
            doWin = 1;
            *balance += bet * 2;
        }
        else if (playerValue < dealerValue)
        {
            printf("You lost: %.2f                                   \n", bet);
            doWin = 0;
        }
        else
        {
            printf("It's a tie! You get your bet back.\n");
            doWin = -1;
            *balance += bet;
        }
        moveCursorTo(11, 0);
        printf("\033[1;37mPlayer: %s\tBalance: %.2f                        \033[0m", playerName, *balance);
        addData_BlackJack(playerName, playerValue, dealerValue, *balance, bet, doWin);
        SHOW_CURSOR();
        moveCursorTo(21, 0);
        printf("Would you like to play again?\n");
        printf("Press [ENTER] or [ANY KEYS] to play again \n");
        printf("Press [1] to change the bet \n");
        printf("Press [2] to return to the menu \n");
        printf("                                                          ");
        moveCursorTo(26, 0);
        choice = getchar();
        while (getchar() != '\n')
            ;
    } while (choice != '2' && *balance > 0);

    free(bet_buffer);
    *option = 6;
}

int main(int argC, char *argV[])
{
    srand(time(NULL));
    FILE *player_log = fopen(filename, "a+");
    if (player_log == NULL)
    {
        printf("Error creating player_log!\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return 1;
    }
    make_directory("BlackJack_Logs");
    make_directory("SlotMachine_Logs");

    int option = 1;
    char *buffer = malloc(MAX_SIZE_STRING);
    if (buffer == NULL)
    {
        printf("No memory to create buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return 1;
    }

    do
    {
        do
        {
            system("cls");
            printf("\033[1;33m===================================\033[0m\n");
            printf("\033[1;33m       Welcome, Adventurers.       \033[0m\n");
            printf("\033[1;33m      Choose your path below.      \033[0m\n");
            printf("\033[1;33m===================================\033[0m\n");

            printf("1. Start New Game\n");
            printf("2. Load Existing Game\n");
            if (option != 1 && option != 2)
            {
                printf("\033[1;31mInvalid option! Please select again.\033[0m\n");
            }

            printf("\033[1;36mChoose an option: \033[0m");
            fgets(buffer, MAX_SIZE_STRING, stdin);
            option = 0;
        } while (sscanf(buffer, "%d", &option) != 1);
    } while (option != 1 && option != 2);

    free(buffer);

    char *playerName = malloc(MAX_SIZE_STRING);
    if (playerName == NULL)
    {
        printf("No memory to create playerName\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return 1;
    }

    char *playerName_temp = malloc(MAX_SIZE_STRING);
    if (playerName_temp == NULL)
    {
        printf("No memory to create playerName_temp\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return 1;
    }

    int isDuplicate;
    float balance;
    char start_word[] = "Player: ";
    char end_word[] = " ";
    char *start, *end;
    int non_space_count = 0;

    switch (option)
    {
    case 1:
        isDuplicate = 0;
        do
        {
            system("cls");
            printf("\033[1;33m===================================\033[0m\n");
            printf("\033[1;33m        Start your journey!        \033[0m\n");
            printf("\033[1;33m===================================\033[0m\n");
            printf("// Case sensitive\n");
            printf("// Space will be automatically remove\n");
            if (isDuplicate)
            {
                printf("\033[1;31mDuplicate name, please enter another name.\033[0m\n");
                isDuplicate = 0;
            }
            non_space_count = 0;
            printf("\033[1;36mEnter your name to start a new game: \033[0m");
            fgets(playerName, MAX_SIZE_STRING, stdin);

            if ((strlen(playerName) > 0) && (playerName[strlen(playerName) - 1] == '\n'))
            {
                playerName[strlen(playerName) - 1] = '\0';
            }

            for (int i = 0; playerName[i] != '\0'; i++)
            {
                if (playerName[i] != ' ')
                {
                    playerName[non_space_count] = playerName[i];
                    non_space_count++;
                }
            }
            playerName[non_space_count] = '\0';

            rewind(player_log);
            while (fgets(playerName_temp, MAX_SIZE_STRING, player_log))
            {
                if ((strlen(playerName_temp) > 0) && (playerName_temp[strlen(playerName_temp) - 1] == '\n'))
                {
                    playerName_temp[strlen(playerName_temp) - 1] = '\0';
                }
                start = strstr(playerName_temp, start_word);
                if (start != NULL)
                {
                    start += strlen(start_word);

                    end = strstr(start, end_word);
                    if (end != NULL)
                    {
                        *end = '\0';
                        if (strcmp(start, playerName) == 0)
                        {
                            isDuplicate = 1;
                            break;
                        }
                    }
                }
            }

        } while (isDuplicate);
        balance = STARTER_BALANCE;
        break;

    case 2:
        isDuplicate = 1;
        do
        {
            system("cls");
            printf("\033[1;33m===================================\033[0m\n");
            printf("\033[1;33m          Long Time No See!        \033[0m\n");
            printf("\033[1;33m===================================\033[0m\n");
            showPlayerNames(player_log);
            if (!isDuplicate)
            {
                printf("\033[1;31mPlayer not found, please enter another name\033[0m\n");
                isDuplicate = 1;
            }
            memset(playerName, 0, MAX_SIZE_STRING);
            non_space_count = 0;
            printf("\033[1;36mEnter your name to load your game: \033[0m");
            fgets(playerName, MAX_SIZE_STRING, stdin);
            if ((strlen(playerName) > 0) && (playerName[strlen(playerName) - 1] == '\n'))
            {
                playerName[strlen(playerName) - 1] = '\0';
            }

            for (int i = 0; playerName[i] != '\0'; i++)
            {
                if (playerName[i] != ' ')
                {
                    playerName[non_space_count] = playerName[i];
                    non_space_count++;
                }
            }
            playerName[non_space_count] = '\0';

            rewind(player_log);
            isDuplicate = 0;
            rewind(player_log);
            while (fgets(playerName_temp, MAX_SIZE_STRING, player_log))
            {
                if ((strlen(playerName_temp) > 0) && (playerName_temp[strlen(playerName_temp) - 1] == '\n'))
                {
                    playerName_temp[strlen(playerName_temp) - 1] = '\0';
                }
                start = strstr(playerName_temp, start_word);
                if (start != NULL)
                {
                    start += strlen(start_word);

                    end = strstr(start, end_word);
                    if (end != NULL)
                    {
                        *end = '\0';
                        if (strcmp(start, playerName) == 0)
                        {
                            isDuplicate = 1;
                            break;
                        }
                        else
                        {
                            isDuplicate = 0;
                        }
                    }
                }
            }
        } while (!isDuplicate);
        balance = loadPlayerBalance(player_log, playerName);
        if (balance == -1)
        {
            printf("Error loading player balance!\n");
            printf("Press [ENTER] to exit....");
            getchar();
            return 1;
        }

        break;

    default:
        printf("Error option is not registered.\n");
        printf("Press ENTER key to exit....");
        getchar();
        return 1;
    }
    fclose(player_log);

    playerName = realloc(playerName, strlen(playerName) + 1);
    free(playerName_temp);

    LoadingScreen(playerName, &balance);
    SavePlayerData(playerName, balance);
    option = 6;
    char *option_buffer = malloc(MAX_SIZE_STRING);
    char *slot_option_buffer = malloc(MAX_SIZE_STRING);
    if (option_buffer == NULL)
    {
        printf("No memory to create option_buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return 1;
    }
    if (slot_option_buffer == NULL)
    {
        printf("No memory to create slot_option_buffer\n");
        printf("Press [ENTER] to exit....");
        getchar();
        return 1;
    }
    while (balance > 0)
    {
        switch (option)
        {
        case 1:
            do
            {
                do
                {
                    CLEAR_SCREEN();
                    PrintCasinoLogo();
                    printf("\033[1;37m                   Player: %s\tBalance: %.2f                          \033[0m\n", playerName, balance);
                    printf("\n-------------------------- Slot Machine ------------------------------\n");
                    printf("1. 3 symbols match: 15x bet EV:-0.85\n");
                    printf("2. 5 symbols match: 45x bet EV:-0.9955\n");
                    printf("3. 7 symbols match: 95x bet EV:-0.999905\n");
                    printf("4. 9 symbols match: 150x bet EV:-0.9999985\n");
                    printf("5. 15 symbols match: 600x bet EV:-0.999999999994\n");
                    printf("6. Return to main menu\n");
                    if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6)
                    {
                        printf("\033[1;31mInvalid option! Please select again.\033[0m\n");
                    }
                    printf("\033[1;36mChoose an option: \033[0m");
                    fgets(slot_option_buffer, MAX_SIZE_STRING, stdin);
                    slot_option_buffer[strcspn(slot_option_buffer, "\n")] = '\0';
                } while (sscanf(slot_option_buffer, "%d", &option) != 1);
            } while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6);
            if (option == 6)
            {
                break;
            }
            SlotMachine(player_log, playerName, &balance, &option);
            break;
        case 2:
            CLEAR_SCREEN();
            BlackJack(player_log, playerName, &balance, &option);
            break;
        case 3:
            CLEAR_SCREEN();
            Gamehistory(playerName);
            option = 6;
            break;
        case 4:
            CLEAR_SCREEN();
            Profile(playerName, balance);
            option = 6;
            break;
        case 5:
            CLEAR_SCREEN();
            Leaderboard();
            option = 6;
            break;
        case 6:
            do
            {
                do
                {
                    CLEAR_SCREEN();
                    SavePlayerData(playerName, balance);
                    PrintCasinoLogo();
                    printf("\033[1;37m                   Player: %s\tBalance: %.2f                          \033[0m\n", playerName, balance);
                    printf("\n----------------------------- Menu ---------------------------------\n");
                    printf("1. Play Slot Machine\n");
                    printf("2. Play Blackjack\n");
                    printf("3. Game History\n");
                    printf("4. Profile\n");
                    printf("5. Leaderboard\n");
                    printf("6. Exit\n");
                    if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6)
                    {
                        printf("\033[1;31mInvalid option! Please select again.\033[0m\n");
                    }
                    printf("\033[1;36mChoose an option: \033[0m");
                    fgets(option_buffer, MAX_SIZE_STRING, stdin);
                    option_buffer[strcspn(option_buffer, "\n")] = '\0';
                } while (sscanf(option_buffer, "%d", &option) != 1);
            } while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6);
            if (option == 6)
            {
                CLEAR_SCREEN();
                SavePlayerData(playerName, balance);
                printf("Thank you for playing!\n");
                printf("Press [ENTER] to exit....");
                getchar();
                return 0;
            }
            break;
        default:
            printf("Error option is not registered.\n");
            printf("Press ENTER key to exit....");
            getchar();
            return 1;
        }
    }
    free(option_buffer);
    free(slot_option_buffer);
    CLEAR_SCREEN();
    SavePlayerData(playerName, balance);
    printf("You have run out of money!\n");
    printf("See? Gambling is bad!\n");
    printf("Press [ENTER] to exit....");
    getchar();
    return 0;
}
