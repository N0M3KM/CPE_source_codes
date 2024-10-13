// 67070501016 & 67070501037

#include <stdio.h>

int fibonacci(int n) {
    if (n==0) return 0; // If n is 0, return 0
    else if (n==1) return 1; // If n is the first order, return 1
    else return fibonacci(n-1) + fibonacci(n-2); // Return the sum of the preceding two numbers
}

void main() {
    int n = 0; 
    scanf("%d", &n); // Get the sequence of Fibonacci series

    // Print each value of Fibonacci recurrence, until it reaches 'n' 
    for (int i=1; i<=n; i++) { 
        printf("%d ", fibonacci(i));
    }
}