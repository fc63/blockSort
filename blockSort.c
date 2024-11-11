#include <stdio.h>

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void mergeInPlace(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            i++;
        } else {
            int temp = arr[j];

            for (int k = j; k > i; k--) {
                arr[k] = arr[k - 1];
            }
            arr[i] = temp;

            i++;
            mid++;
            j++;
        }
    }
}

void blockSort(int arr[], int left, int right, int blockSize) {

    for (int i = left; i <= right; i += blockSize) {
        int end = (i + blockSize - 1 < right) ? i + blockSize - 1 : right;
        insertionSort(arr, i, end);
    }

    for (int size = blockSize; size < right - left + 1; size *= 2) {
        for (int i = left; i <= right - size; i += 2 * size) {
            int mid = i + size - 1;
            int end = (i + 2 * size - 1 < right) ? i + 2 * size - 1 : right;
            mergeInPlace(arr, i, mid, end);
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int blockSize = 2; 

    printf("Orijinal dizi: \n");
    printArray(arr, arrSize);

    blockSort(arr, 0, arrSize - 1, blockSize);

    printf("Sıralanmış dizi: \n");
    printArray(arr, arrSize);

    return 0;
}
