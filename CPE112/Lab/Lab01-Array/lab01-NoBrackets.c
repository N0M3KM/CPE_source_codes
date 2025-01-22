#include <stdio.h>
#include <stdlib.h>

int main() {
    int boolean = 0;
    int size=0;
    scanf("%d", &size);
    int* array = (int*)malloc(sizeof(int)*size);
    for (int i=0; i<size; i++) {
        scanf("%d", array+i);
    }
    int choice;
    scanf("%d", &choice);
    for (int i=0; i<size; i++) {
        if (choice==0){
            if (i%2==0) {
                printf("%d ", *(array+i));
                boolean = 1;
            }
        } else if (choice==1) {
            if (i%2!=0) {
                printf("%d ", *(array+i));
                boolean = 1;
            }
        }
    }    
    
    free(array);

    if (boolean==0) {
        printf("none");
    }
    return 0;
}