#include <stdio.h>

char ans = 'y';

void find_largest(int a, int b, int c) {
  if (a > b) {
    if (a > c) {
      printf("%d is the largest number.\n", a);
    } else {
      printf("%d is the largest number.\n", c);
    }
  } else {
    if (b > c) {
      printf("%d is the largest number.\n", b);
    } else {
      printf("%d is the largest number.\n", c);
    }
  }
}

int main() {
  while (ans == 'y') {
    int a, b, c;
    printf("Enter 3 numbers :");
    scanf("%d %d %d", &a, &b, &c);
    find_largest(a, b, c);

    printf("Would you like to continue (y/n) :");
    scanf(" %c", &ans);
  }
  return 0;
}
