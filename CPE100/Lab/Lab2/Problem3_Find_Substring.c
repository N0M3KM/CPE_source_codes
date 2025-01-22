#include <stdio.h>

int findStringLength (char str[])
{
    int c = 0, i = 0;
    while (str[i]!='\0') {
        if (str[i]!=' ') {
            c++;
        }
        i++;
    }

    return c;
}

int findSubString (char* str1, char* str2)
{   
    int index = 0, replicatedCount = 0;
    int subStringLength = findStringLength(str2);

    while (*str1 != '\0') {
        if (str2[replicatedCount] == *str1) {
            replicatedCount++;
            if (replicatedCount == subStringLength) {
                return index;
            }
        } else {
            index += 1;
            str1 -= replicatedCount;
            replicatedCount = 0;
        }
        str1++;
    }
    
    return -1;
}

int main() 
{ 
    char *string1, *string2;
    string1 = "I love CPE";
    string2 = "love";

    int c = findStringLength(string1);
    int output = findSubString(string1, string2);

    if (output!=-1) {
        printf("Index of the first occurrence = %d", output);
    } else {
        printf("string2 is not a substring of string1");
    }

    return 0; 
}
