#include <stdio.h>

void input(int *arr, int *n, int *c);
void output(int *arr, int n);
void cyclic_shift(int *arr, int n, int c);

/*------------------------------------
        Main function
-------------------------------------*/
int main() {
    int n, c;
    int arr[10];

    input(arr, &n, &c);

    if (n == -1) {
        printf("n/a\n");
        return 0;
    }

    cyclic_shift(arr, n, c);
    output(arr, n);

    return 0;
}

/*------------------------------------
        Function to read array and shift from stdin
-------------------------------------*/
void input(int *arr, int *n, int *c) {
    if (scanf("%d", n) != 1 || *n < 1 || *n > 10) {
        *n = -1;
        return;
    }

    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            *n = -1;
            return;
        }
    }

    if (scanf("%d", c) != 1) {
        *n = -1;
        return;
    }
}

/*------------------------------------
        Function to output array to stdout
-------------------------------------*/
void output(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

/*------------------------------------
        Function to perform cyclic shift
        Left for positive c, right for negative c
-------------------------------------*/
void cyclic_shift(int *arr, int n, int c) {
    if (n <= 0) return;

    // Normalize shift
    if (c < 0)
        c = n + (c % n);  // Right shift -> equivalent left shift
    else
        c = c % n;  // Left shift

    if (c == 0) return;

    int temp[10];  // Max array size 10

    for (int i = 0; i < n; i++) temp[i] = arr[(i + c) % n];

    for (int i = 0; i < n; i++) arr[i] = temp[i];
}