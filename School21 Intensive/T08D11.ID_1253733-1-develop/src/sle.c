#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int sle(double **matrix, int n, int m, double *roots) {
    // Прямой ход метода Гаусса
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int r = i + 1; r < n; r++)
            if (fabs(matrix[r][i]) > fabs(matrix[pivot][i])) pivot = r;

        if (fabs(matrix[pivot][i]) < 1e-12) return 0;  // нельзя решить

        if (pivot != i) {
            double *tmp = matrix[i];
            matrix[i] = matrix[pivot];
            matrix[pivot] = tmp;
        }

        double diag = matrix[i][i];
        for (int j = i; j < m; j++) matrix[i][j] /= diag;

        for (int r = i + 1; r < n; r++) {
            double factor = matrix[r][i];
            for (int j = i; j < m; j++) matrix[r][j] -= factor * matrix[i][j];
        }
    }

    // Обратный ход
    for (int i = n - 1; i >= 0; i--) {
        roots[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) roots[i] -= matrix[i][j] * roots[j];
    }

    return 1;  // успех
}

void input(double **matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0 || *m != *n + 1) {
        *n = 0;
        *m = 0;
        return;
    }

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            if (scanf("%lf", &matrix[i][j]) != 1) {
                *n = 0;
                *m = 0;
                return;
            }
}

void output_roots(double *roots, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%.6f", roots[i]);
        if (i + 1 < n) printf(" ");
    }
    printf("\n");
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0 || m != n + 1) {
        printf("n/a");
        return 0;
    }

    double **matrix = malloc(n * sizeof(double *));
    if (!matrix) {
        printf("n/a");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(m * sizeof(double));
        if (!matrix[i]) {
            printf("n/a");
            return 0;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (scanf("%lf", &matrix[i][j]) != 1) {
                printf("n/a");
                return 0;
            }

    double *roots = malloc(n * sizeof(double));
    if (!roots) {
        printf("n/a");
        return 0;
    }

    if (!sle(matrix, n, m, roots)) {
        printf("n/a");
    } else {
        output_roots(roots, n);
    }

    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
    free(roots);

    return 0;
}
