//67070501016 & 67070501037

#include <stdio.h>

int search(int arr[],int i,int j, int x)
{
    if (i > j){
        return -1;  //if number not found return -1
    }
    if (arr[i] == x){
        return i+1; //return position+1
    }
    return search(arr, i + 1, j, x);
}

void main() {
    int arr[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    int n, result; //input number from user
    scanf("%d", &n);  

    result = search(arr, 0, 14, n);//resalut = position of number in the array 0-14
     if (result != -1) {
        printf("%d",result);//out put result(position)
    } else {
        printf("-1"); //out put -1 if number not found in any position 
    }
}