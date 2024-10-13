//67070501016 Drarun Yookphan
#include <stdio.h>

int findLetter(char word[]) {
    int i = 0;
    int count = 0;
    while (word[i] != '\0') {
        if (word[i]=='a') {
            count += 1;
        }
        i++;
    }
    return count;
}

int main() {
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);
    int count = findLetter(word);
    printf("Total number of 'a' is %d.\n", count);
}