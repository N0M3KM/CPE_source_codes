// 67070501016 & 67070501037

#include <stdio.h>
#include <math.h>

int fibonacci(int n) {
        if (n==0) return 0; // If n is 0, return 0
        else if (n==1) return 1; // If n is the first order, return 1
        else return fibonacci(n-1) + fibonacci(n-2); // Return the sum of the preceding two numbers
    }

int linearSearch(int arr[],int i,int j, int x)
{
    if (i > j){
        return -1;  //if number not found return -1
    }
    if (arr[i] == x){
        return i+1; //return position+1
    }
    return linearSearch(arr, i + 1, j, x);
}

int binarySearch(int arr[15], int i, int j, int x) {
    int m = floor((i+j)/2); // Get the middle index as 'm'
    // If target value is equal to the value of the middle position of the array, return the next position from the middle
    if (x==arr[m]) {
        return m+1;
    } 
    /* If x is lower than the value of the middle position of the array and the position is on the left side, 
       do recursive binary search in range of i to the left position of the middle */
    else if (x<arr[m] && i<m) {
        return binarySearch(arr, i, m-1, x);
    } 
    /* If x is greater than the value of the middle position of the array and the possition is on the right side,
       do recursive binary search in range of the next position of the middle to j*/
    else if (x>arr[m] && j>m) {
        return binarySearch(arr, m+1, j, x);
    // If not found, return -1
    } else return -1;
}


void main() {
    /* Recursive Fibonacci */
    int n = 0; 
    scanf("%d", &n); // Get the sequence of Fibonacci series
    // Print each value of Fibonacci recurrence, until it reaches 'n' 
    for (int i=1; i<=n; i++) { 
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    /*------------------------*/

    /* Recursive Linear Search */
    int arr1[15] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29};
    int result; //input number from user
    scanf("%d", &n);  
    result = linearSearch(arr1, 0, 14, n);//resalut = position of number in the array 0-14
     if (result != -1) {
        printf("%d",result);//out put result(position)
    } else {
        printf("-1"); //out put -1 if number not found in any position 
    }
    printf("\n");
    /*------------------------*/

    /* Recursive Binary Search */
    int arr2[15] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29};
    int x;
    scanf("%d", &x); // Search for 'x' value
    printf("%d", binarySearch(arr2,0,14,x)); // Return the index from recursive binary search function
    /*------------------------*/
}