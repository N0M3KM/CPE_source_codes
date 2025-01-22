#include <stdio.h>

long int factorial(int n)
{
     int i;
     long int product = 1;
     for (i = n; i>1; i--)
          product *= i;
     return product;
}

long int combination(int n, int r)
{
    long int fn = factorial(n);
    long int fr = factorial(r);
    long int fnr = factorial(n-r);
    
    return fn/(fr*fnr);
}

int main() 
{ 
     int n, r;
     int ans;
     printf("To calculate nCr, enter n and r: "); 
     scanf("%d %d", &n, &r); 
     ans = combination(n, r); 
     printf("\n%dC%d = %d", n, r, ans);
     return 0; 
}