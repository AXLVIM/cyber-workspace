#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int method;
    if (scanf("%d", &method) != 1 || method < 1 || method > 3) {
        printf("n/a");
        return 0;
    }

    int N, M;
    if (scanf("%d %d", &N, &M) != 2 || N <= 0 || M <= 0) {
        printf("n/a");
        return 0;
    }

    int **matrix = NULL;
    int *buf = NULL;  // for contiguous storage in method 1 or 3

    // Allocate memory based on method
    if (method == 1 || method == 3) {
        buf = malloc(N * M * sizeof(int));
        if (!buf) {
            printf("n/a");
            return 0;
        }

        matrix = malloc(N * sizeof(int *));
        if (!matrix) {
            free(buf);
            printf("n/a");
            return 0;
        }

        for (int i = 0; i < N; i++) matrix[i] = buf + i * M;
    } else if (method == 2) {
        matrix = malloc(N * sizeof(int *));
        if (!matrix) {
            printf("n/a");
            return 0;
        }

        for (int i = 0; i < N; i++) {
            matrix[i] = malloc(M * sizeof(int));
            if (!matrix[i]) {
                for (int j = 0; j < i; j++) free(matrix[j]);
                free(matrix);
                printf("n/a");
                return 0;
            }
        }
    }

    // Read matrix elements
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a");
                if (method == 1 || method == 3) {
                    free(buf);
                    free(matrix);
                } else if (method == 2) {
                    for (int k = 0; k < N; k++) free(matrix[k]);
                    free(matrix);
                }
                return 0;
            }

    // Sort rows by sum using simple bubble-like approach
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            int sum1 = 0, sum2 = 0;
            for (int k = 0; k < M; k++) {
                sum1 += matrix[j][k];
                sum2 += matrix[j + 1][k];
            }
            if (sum1 > sum2) {
                int *tmp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = tmp;
            }
        }
    }

    // Print sorted matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", matrix[i][j]);
            if (j < M - 1) printf(" ");
        }
        if (i < N - 1) printf("\n");
    }

    // Free memory
    if (method == 1 || method == 3) {
        free(buf);
        free(matrix);
    } else if (method == 2) {
        for (int i = 0; i < N; i++) free(matrix[i]);
        free(matrix);
    }

    return 0;
}