#include <stdio.h>

void maxmin(int prob1, int prob2, int prob3, int *max, int *min);

/* Find a max & min probabilities */
int main() {
    int x, y, z;

    // Correct input validation
    if (scanf("%d %d %d", &x, &y, &z) != 3) {
        printf("n/a");
        return 0;
    }

    int max, min;

    // Pass pointers correctly
    maxmin(x, y, z, &max, &min);

    printf("%d %d\n", max, min);

    return 0;
}

/* This function should be kept !!! (Your AI) */
/* But errors & bugs should be fixed         */
void maxmin(int prob1, int prob2, int prob3, int *max, int *min) {
    // Initialize both through pointers
    *max = prob1;
    *min = prob1;

    // Compare prob2
    if (prob2 > *max) *max = prob2;
    if (prob2 < *min) *min = prob2;

    // Compare prob3
    if (prob3 > *max) *max = prob3;
    if (prob3 < *min) *min = prob3;
}