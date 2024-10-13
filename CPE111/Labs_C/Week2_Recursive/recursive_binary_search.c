// 67070501016 & 67070501037

#include <stdio.h>
#include <math.h>

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
    int arr[15] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29};
    int x;
    scanf("%d", &x); // Search for 'x' value

    printf("%d", binarySearch(arr,0,14,x)); // Return the index from recursive binary search function
}