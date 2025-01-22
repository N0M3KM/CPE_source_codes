#include<stdio.h>

int main() {
    int i=0;
    int num, max, min, i_max=0, i_min=0;
    while (1)
    {
        scanf("%d", &num);
        if (num==-9999) {
            if (i==0) {
                printf("None");
                return 0;
            }
            break;
        }
        i++;

        if (i==1){
            max = num;
            min = num;
            i_max = i;
            i_min = i;
        }

        if (num>max) {
            max = num;
            i_max = i;
        }else if (num<min) {
            min = num;
            i_min = i;
        }
    }
    printf("%d %d\n", max, i_max);
    printf("%d %d", min, i_min);
    return 0;
}