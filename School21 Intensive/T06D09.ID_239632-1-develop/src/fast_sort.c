#include <stdio.h>

#define SIZE 10

int read_array(int *arr);
void print_array(int *arr);
void quicksort(int *arr, int left, int right);
int partition(int *arr, int left, int right);
void heapsort(int *arr);
void heapify(int *arr, int n, int i);

int main() {
    int arr1[SIZE];
    int arr2[SIZE];

    if (!read_array(arr1)) {
        printf("n/a");
        return 0;
    }

    for (int i = 0; i < SIZE; i++) {
        arr2[i] = arr1[i];
    }

    quicksort(arr1, 0, SIZE - 1);
    heapsort(arr2);

    print_array(arr1);
    printf("\n");
    print_array(arr2);
    printf("\n");

    return 0;
}

int read_array(int *arr) {
    for (int i = 0; i < SIZE; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

void print_array(int *arr) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d", arr[i]);
        if (i < SIZE - 1) {
            printf(" ");
        }
    }
}

/* ---------------- QUICKSORT ---------------- */

void quicksort(int *arr, int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}

int partition(int *arr, int left, int right) {
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
        }
    }

    int tmp = arr[i];
    arr[i] = arr[right];
    arr[right] = tmp;

    return i;
}

/* ---------------- HEAPSORT ---------------- */

void heapsort(int *arr) {
    int size = SIZE;

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        heapify(arr, i, 0);
    }
}

void heapify(int *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;

        heapify(arr, n, largest);
    }
}