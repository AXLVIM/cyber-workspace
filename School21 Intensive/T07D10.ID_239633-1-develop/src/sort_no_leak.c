#include <stdio.h>
#include <stdlib.h>

int read_array(int *arr, int n);
void sort_array(int *arr, int n);
void print_array(int *arr, int n);

int main() {
    int n;

    // Read array length
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 0;
    }

    // Dynamic allocation
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("n/a");
        return 0;
    }

    // Read values
    if (!read_array(arr, n)) {
        printf("n/a");
        free(arr);
        return 0;
    }

    // Sort
    sort_array(arr, n);

    // Print (no trailing newline!)
    print_array(arr, n);

    free(arr);
    return 0;
}

int read_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

void sort_array(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
}