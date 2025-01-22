#include <stdio.h>

void main() {
    FILE *input, *output; 
    char fileName[20];
    char name[20][20];
    int score[20];
    int i = 0;

    float avg = 0.0;
    int min = 0, max = 0, sum = 0;
    printf("Enter a file name to load student scores : ");
    scanf("%19s ", fileName);
    input = fopen(fileName, "r");
    output = fopen("stat.txt", "w");

    while (fscanf(input, "%19s %d", name[i], &score[i]) == 2) {
        if (i == 0) {
            min = max = score[i];
        } else {
            if (score[i] > max) {
                max = score[i];
            }
            if (score[i] < min) {
                min = score[i];
            }
        }
        sum += score[i];
        printf("Student %d: %s, Score = %d\n", i + 1, name[i], score[i]);
        i++;
    }
    fclose(input);

    getchar();
    avg = sum / i;
    printf("Average score is %.2f\n", avg);
    printf("Minimum score is %d\n", min);
    printf("Maximum score is %d\n", max);

    fprintf(output, "Average score is %.2f\n", avg);
    fprintf(output, "Minimum score is %d\n", min);
    fprintf(output, "Maximum score is %d\n", max);
    fclose(output);
    printf("Save statistics in file stat.txt successfully.\n");
    printf("End of program. Goodbye.\n");
}
