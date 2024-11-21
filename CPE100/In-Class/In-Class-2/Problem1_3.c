#include <stdio.h>
#include <string.h>

int isAllDigitPtr(char* arr) {
    while (*arr!='\0') {
        if ((*arr < '0' || *arr > '9')) {
            return 0;
        }
        arr++;
    }
    return 1;
}

int isAllDigit(char arr[]) {
    int i = 0;
    while (arr[i]!='\0') {
        if ((arr[i] < '0' || arr[i] > '9')) {
            return 0;
        }
        i++;
    }
    return 1;
}

void getInput() {
    while (1) {
        char arr[100];
        printf("Enter a string (Insert END to stop the program) : ");
        scanf("%s", arr);

        if (strcmp(arr, "END")==0) {
            break;
        }

        if (isAllDigit(arr)) {
            printf("Is all digit\n");
        } else {
            printf("Is not all digit\n");
        }
    }
}

int main() {
    getInput();
    return 0;
}