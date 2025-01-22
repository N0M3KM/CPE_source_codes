//67070501016 Drarun Yookphan
#include <stdio.h>

int main() {
    char con = 'y';
    while (con == 'y') {
        int s, e;
        printf("Enter start number: ");
        scanf("%d", &s);
        printf("Enter end number: ");
        scanf("%d", &e);

        for (int i=1;i<=s;i++) {
            for (int j=s;j<=e;j++) {
                printf("%d ", j*i);
            }
            printf("\n");
        }

        printf("Do you want to continue (y/n)? ");
        scanf(" %c", &con);
    }
    printf("End of program. Goodbye.\n");
    return 0;
}
