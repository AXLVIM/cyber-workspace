#include <stdio.h>

#define SIZE 10

int read_array(int *arr);
void sort_array(int *arr);
void print_array(int *arr);

int main() {
    int arr[SIZE];

    if (!read_array(arr)) {
        printf("n/a\n");
        return 0;
    }

    sort_array(arr);
    print_array(arr);

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

void sort_array(int *arr) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void print_array(int *arr) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d", arr[i]);
        if (i < SIZE - 1) {
            printf(" ");
        }
    }
    printf("\n");
}