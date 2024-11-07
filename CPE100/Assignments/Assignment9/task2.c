#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LENGTH 20

typedef struct studentInfo { 
    char name[NAME_LENGTH];
    int score;
} studentInfo;

void addNewData(studentInfo student[], int *i, int *count) {
    char newName[NAME_LENGTH];
    int newScore;

    while (1) {
        printf("Enter new student name (type \"END\" to sort student score and end the program): ");
        fflush(stdout);
        scanf("%s", newName);
        if (strcmp(newName, "END") == 0) {
            break;
        }
        if ((*i)+1 > *count) {
            printf("Cannot add %s into the student list. The number of students cannot exceed %d. Please type \"END\" to sort student score and end the program\n", newName, *count);
            continue;
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
    char fileName[NAME_LENGTH];
    int count=0, i=0;

    printf("Enter a number of students in the class: ");
    scanf("%d", &count);

    if (count < 5) {
        printf("<Error> The student amount must be equal or higher than 5");
        return 0;
    }

    studentInfo *student = (studentInfo*)malloc(count * sizeof(studentInfo));
    FILE *input; 

    printf("Enter a file name to load student scores: ");
    scanf("%s", fileName);

    input = fopen(fileName, "r");

    while (fscanf(input, "%s %d", (student+i)->name, &(student+i)->score) == 2) {
        printf("Student %d: %s, Score = %d\n", i + 1, (student+i)->name, (student + i)->score);
        i++;
    }
    fclose(input);

    addNewData(student, &i, &count);

    printf("---------------Sort students by scores---------------\n");
    sort(student, i);

    for (int c = 0; c < i; c++) {
        printf("Student %d: %s, Score = %d\n", c + 1, (student + c)->name, (student + c)->score);
    }
    
    free(student);

    printf("End of program. Goodbye.\n");
    return 0;
}