// 67070501016 & 67070501037 //

#include <stdio.h>
#include <math.h>

/* Insertion sort algorithm  */ 
void insertionSort(int array[], int n) {
    float tempValue;
    int i, j, k;
    // loop index from 1 to n-1
    for (i=1; i < n; i++) { 
        j = 0;
        tempValue = array[i];
        // start the loop at j which is 0 at the first time. if j is lower than i and the value of the array at j
        // is lower than the value of the array at i, add j by 1.
        while (j<i && array[j]<tempValue)
        {
            j++;
        }

        // start the loop at k which is i by now and keep changing the value of array at k to the value at k-1
        // as long as k is more than j
        for (k=i; k>j; k--) {
            array[k]=array[k-1];
        }
        // after all, set the value of array at j to the value of the initialized array at i which is stored in tempValue
        array[j]=tempValue;
    }
}

/* Bubble sort algorithm  */ 
void bubbleSort(int array[], int n) {
    float tempValue;
    int i, j;
    // loop i index from 0 to n-1
    for (i = 0; i < n - 1; i++) {
        // loop j index from 0 to n-i-1
        for (j = 0; j < n - i - 1; j++) {
            // if value of array at j is greater than value of array at j+1, then interchange value of- 
            // arrray at j and j+1
            if (array[j] > array[j + 1]) {
                tempValue = array[j]; // we temporarily store the value of array at j in a variable called 'tempValue'
                array[j] = array[j + 1];
                array[j + 1] = tempValue;  
            }
        }
    }
}

/* Binary search algorithm  */ 
int binarySearch(int array[], int n, int x) {
    int i = 0; // i is the mostleft position of the array, the first index equals to 0
    int j = n - 1; // j is the mostright postion of the array, the last index equals to its size substract 1 as it starts from 0
    while (j >= i) {
        int m = floor((i + j) / 2); // use floor function from <math.h> library to get middle value, splice an array in half
        // if x equals to the middle value of the array, return its middle location
        if (x==array[m]) {
            return m; 
        } 
        // if x is greater than the value of the array at middle, ignore left-half array
        else if (x > array[m]) {
            i = m + 1; 
        } 
        // if x is greater than the value of the array at middle, ignore right-half array
        else if (x < array[m]) {
            j = m - 1;  
        }
    }
    // if the x value doesn't exist in the array, return -1
    return -1;
}

/* Greatest common divisor */ 
int GCD(int i, int j) {
    // loop until j equals to 0 when j is the value of i mod j. in each loop, we set the value of j equals to i mod j
    // after that adjust i to the previous j value which is 'tempValue' by now. 
    while (j != 0) {
        int tempValue = j;
        j = i % j;
        i = tempValue;
    }
    return i;
}

// print output
void printArray(char str[], int array[], int n) {
    puts(str);
    for (int l=0; l < n; l++) {
        printf("%d ", array[l]);
    }
    printf("\n");
}

// test bubble algorithm function
void testBubbleSort(int n) {
    int testCase1[11] = {11,8,1,9,21,5,7,32,6,20,10};
    int testCase2[11] = {3,5,7,9,29,33,17,41,26,2,8};

    bubbleSort(testCase1, n); // sort the array with bubble sort algorithm using testcase 1
    bubbleSort(testCase2, n); // sort the array with bubble sort algorithm using testcase 2

    printArray("Bubble Sorting Result1 :", testCase1, n);
    printArray("Bubble Sorting Result2 :", testCase2, n);
}

// test insertion algorithm function
void testInsertionSort(int n) {
    int testCase1[11] = {11,8,1,9,21,5,7,32,6,20,10};
    int testCase2[11] = {3,5,7,9,29,33,17,41,26,2,8};

    insertionSort(testCase1, n); // sort the array with insertion sort algorithm using testcase 1
    insertionSort(testCase2, n); // sort the array with insertion sort algorithm using testcase 2

    printArray("Insertion Sorting Result1 :", testCase1, n);
    printArray("Insertion Sorting Result2 :", testCase2, n);
}

// test binary algorithm function
void testBinarySearch(int n) {
    int testCase1[11] = {11,8,1,9,21,5,7,32,6,20,10}; 
    int testCase2[11] = {3,5,7,9,29,33,17,41,26,2,8}; 

    int target1 = 41; // determinated to search for 41
    int target2 = 11; // determinated to search for 11

    bubbleSort(testCase1, n); // sort the array with bubble sort algorithm using testcase 1
    bubbleSort(testCase2, n); // sort the array with bubble sort algorithm using testcase 2

    printf("Search for %d  in the first array, its index is : %d \n", target1, binarySearch(testCase1, n, target1));  // print out the result of binary search algorithm
    printf("Search for %d  in the second array, its index is : %d \n", target1, binarySearch(testCase2, n, target1));  // print out the result of binary search algorithm
    printf("Search for %d  in the first array, its index is : %d \n", target2, binarySearch(testCase1, n, target2));  // print out the result of binary search algorithm
    printf("Search for %d  in the second array, its index is : %d \n", target2, binarySearch(testCase2, n, target2));  // print out the result of binary search algorithm
}

void testGCD() {
    int num1, num2, i;
    int GCDTestCase1[3][2] = {{12,36},{51,27},{19,100}};
    int GCDTestCase2[3][2] = {{25,75},{39,15},{17,50}};

    printf("GCD of case1 : ");

    for (i=0; i < 3; i++) {
        num1 = GCDTestCase1[i][0];
        num2 = GCDTestCase1[i][1];
        printf("%d ", GCD(num1, num2));
    }

    printf("\n");
    printf("GCD of case2 : ");

    for (i=0; i < 3; i++) {
        num1 = GCDTestCase2[i][0];
        num2 = GCDTestCase2[i][1];
        printf("%d ", GCD(num1, num2));
    }
}

int main() {
    /* SORTING AND SEARCHING ALGORITHM */
    int n = 11;             // length of array
    testInsertionSort(n);   // run test function (Insertion)
    testBubbleSort(n);      // run test function (Bubble)
    testBinarySearch(n);    // run test function (Binary Search)
    testGCD();              // run test function (GCD)
    /* ======================================= */
    return 0;
}

