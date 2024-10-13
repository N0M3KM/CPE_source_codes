// 67070501016 Drarun Yookphan
#include <stdio.h>
#include <string.h>

void getTheFirstAlphabet(char array[10][8], int count) {
    char firstOrder[8];
    strcpy(firstOrder, array[0]);
    for (int i=1;i<count;i++) {
        if (strcmp(array[i], firstOrder)<0) {
            strcpy(firstOrder, array[i]);
        }
    }
    printf("\nThe first order name sorted alphabetically: %s", firstOrder);
}

int main() 
{ 
    char students[10][8];
    int count = 0;

    printf("Enter student names (type END to print all names)\n");
    while (1) {
        printf("Enter name of student %d: ", count+1);
        scanf("%s", &students[count]);
        if (strlen(students[count])>8) {
            printf("The name is too long. Please try again.\n");
            continue;
        }
        if (strcmp(students[count], "END") == 0) {
            break;
        }
        count += 1;
    }

    printf("Name list: ");
    for (int i=0; i<count; i++) {
        printf("%s ", students[i]);
    }

    getTheFirstAlphabet(students, count);
    return 0;
}