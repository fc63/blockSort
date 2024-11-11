#include <stdio.h>

void insertionSort(int arr[], int left, int right) {    int key = 0, j = 0, i = 0;

    for (i = left + 1; i <= right; i++) {   key = arr[i], j = i - 1;
        while (j >= left && arr[j] > key)     arr[j-- + 1] = arr[j];
        arr[j + 1] = key;
    }
}

void mergeInPlace(int arr[], int left, int mid, int right) {    int i = left, j = mid + 1, k = 0, temp = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            i++;
        } else {
            temp = arr[j];
            for (k = j++; k > i; k--)   arr[k] = arr[k - 1];
            arr[i++] = temp;
            mid++;
        }
    }
}

void blockSort(int arr[], int left, int right, int blockSize) {     int i = 0 , size = 0;

    for (i = left; i <= right; i += blockSize) insertionSort(arr, i, (i + blockSize - 1 < right) ? i + blockSize - 1 : right);

    for (size = blockSize; size < right - left + 1; size *= 2)
        for (i = left; i <= right - size; i += 2 * size)    mergeInPlace(arr, i, i + size - 1, (i + 2 * size - 1 < right) ? i + 2 * size - 1 : right);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7, 8, 7, 8};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int blockSize = 2; 

    printf("Original: \n");
    printArray(arr, arrSize);

    blockSort(arr, 0, arrSize - 1, blockSize);

    printf("Sorted: \n");
    printArray(arr, arrSize);

    return 0;
}
