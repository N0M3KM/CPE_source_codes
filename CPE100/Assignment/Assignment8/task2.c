#include <stdio.h>
#include <string.h>

typedef struct studentInfo { 
    char name[20];
    int score;
} studentInfo;

void addNewData(studentInfo student[], int *i) {
    char newName[20];
    int newScore;

    while (1) {
        printf("Enter new student name (type \"END\" to sort student score and end the program): ");
        fflush(stdout);
        scanf("%19s", newName);
        if (strcmp(newName, "END") == 0) {
            break;
        }

        printf("Enter %s's score: ", newName);
        fflush(stdout);
        scanf("%d", &newScore);

        strcpy(student[*i].name, newName);
        student[*i].score = newScore;
        (*i)++;
    }
}

void swap(studentInfo *a, studentInfo *b) {
    studentInfo temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sort(studentInfo student[], int count) {
    int minPos;
    for (int i = 0; i < count - 1; i++) {
        minPos = i;
        for (int j = i + 1; j < count; j++) {
            if (student[j].score < student[minPos].score) {
                minPos = j;
            }
        }
        swap(&student[i], &student[minPos]);
    }
}

int main() { 
    studentInfo student[20];   
    char fileName[20];
    FILE *input; 
    int i = 0;

    printf("Enter a file name to load student scores: ");
    scanf("%19s", fileName);

    input = fopen(fileName, "r");

    while (fscanf(input, "%19s %d", student[i].name, &student[i].score) == 2) {
        printf("Student %d: %s, Score = %d\n", i + 1, student[i].name, student[i].score);
        i++;
    }
    fclose(input);

    getchar();

    addNewData(student, &i);

    printf("---------------Sort students by scores---------------\n");
    sort(student, i);

    for (int c = 0; c < i; c++) {
        printf("Student %d: %s, Score = %d\n", c + 1, student[c].name, student[c].score);
    }
    
    printf("End of program. Goodbye.\n");
    return 0;
}