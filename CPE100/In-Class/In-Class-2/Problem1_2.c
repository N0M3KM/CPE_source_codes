#include <stdio.h>

int isAllDigitPtr(char* arr) {
    while (*arr!='\0') {
        if ((*arr < '0' || *arr > '9')) {
            return 0;
        }
        arr++;
    }
    return 1;
}

int main() {
    char* arrPtr =  "1115151";

    if (isAllDigitPtr(arrPtr)) {
        printf("Is all digit\n");
    } else {
        printf("Is not all digit\n");
    }

    return 0;
}