#include<stdio.h>

int main() {
    int temp,a,b = 0;
    int hasPrime = 0;;
    scanf("%d %d", &a, &b);
    for (int i = a+1; i<b; i++) {
        temp = 0;
        for (int j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                temp++;
                break;
            }
        } 
        if (temp == 0 && i != 1) {
            hasPrime = 1;
            printf("%d ", i);
        }        
    }
    if (hasPrime == 0) {
        printf("none");
    }
    return 0;
}