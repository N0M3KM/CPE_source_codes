//67070501016 Drarun Yookphan
#include <stdio.h>

int main() {
    char word[10];
    int count;

    printf("Enter a word: ");
    scanf("%s", word);
    count = 0;
    while (word[count] != '\0') {
        count++;
    }

    printf("Total alphabets in '%s' = %d.", word, count);

    return 0;
}