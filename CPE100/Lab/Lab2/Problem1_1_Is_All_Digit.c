#include <stdio.h>

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

int main() {
    char arr[101] = "0009999";
    if (isAllDigit(arr)) {
        printf("Is all digit\n");
    } else {
        printf("Is not all digit\n");
    }
    return 0;
}