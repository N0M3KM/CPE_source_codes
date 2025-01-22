#include <stdio.h>
#include <stdlib.h>

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int* insertArray(int* arr, int* size, int index, int value) {
    if (index < 0 || index > *size) {
        printf("Index out of bounds\n");
        return arr;
    }
    *size += 1;
    int* newArr = (int*)realloc(arr, sizeof(int) * (*size));
    arr = newArr;
    for (int i = *size - 1; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    printArray(arr, *size);
    return arr;
}

int* deleteArray(int* arr, int* size, int index) {
    if (index >= *size || index < 0) {
        printf("Index out of bounds\n");
        return arr;
    }
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    *size -= 1;
    int* temp = (int*)realloc(arr, sizeof(int) * (*size));
    arr = temp;
    printArray(arr, *size);
    return arr;
}

void mergeArray(int* arr1, int size1, int* arr2, int size2) {
    int* mergedArray = (int*)malloc(sizeof(int)*(size1 + size2));

    for (int i = 0; i < size1; i++) {
        mergedArray[i] = arr1[i];
    }
    for (int i = 0; i < size2; i++) {
        mergedArray[size1 + i] = arr2[i];
    }
    printArray(mergedArray, size1 + size2);
    free(mergedArray);
}

int main() {
    int size1, size2;
    scanf("%d", &size1);
    int* array1 = (int*)malloc(sizeof(int)*size1);
    for (int i = 0; i < size1; i++) {
        scanf("%d", array1+i);
    }
    scanf("%d", &size2);
    int* array2 = (int*)malloc(sizeof(int)*size2);
    for (int i = 0; i < size2; i++) {
        scanf("%d", array2+i);
    }
    int insertIndex, insertValue, deleteIndex;
    scanf("%d", &insertIndex);
    scanf("%d", &insertValue);
    scanf("%d", &deleteIndex);
    
    array1 = insertArray(array1, &size1, insertIndex, insertValue);
    array1 = deleteArray(array1, &size1, deleteIndex);
    mergeArray(array1, size1, array2, size2);
    free(array1);
    free(array2);
    return 0;
}
