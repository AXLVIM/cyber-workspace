#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m) {
    if (n != m) return NAN;  // определитель только для квадратной матрицы

    double **a = malloc(n * sizeof(double *));
    if (!a) return NAN;
    for (int i = 0; i < n; i++) {
        a[i] = malloc(n * sizeof(double));
        if (!a[i]) {
            for (int k = 0; k < i; k++) free(a[k]);
            free(a);
            return NAN;
        }
        for (int j = 0; j < n; j++) a[i][j] = matrix[i][j];
    }

    double det_val = 1.0;
    int sign = 1;

    for (int i = 0; i < n; i++) {
        double maxEl = fabs(a[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(a[k][i]) > maxEl) {
                maxEl = fabs(a[k][i]);
                maxRow = k;
            }
        }

        if (fabs(maxEl) < 1e-12) {
            det_val = 0.0;
            break;
        }

        if (maxRow != i) {
            double *tmp = a[i];
            a[i] = a[maxRow];
            a[maxRow] = tmp;
            sign = -sign;
        }

        det_val *= a[i][i];

        double pivot = a[i][i];
        for (int k = i + 1; k < n; k++) {
            double factor = a[k][i] / pivot;
            for (int j = i; j < n; j++) {
                a[k][j] -= factor * a[i][j];
            }
        }
    }

    det_val *= sign;

    for (int i = 0; i < n; i++) free(a[i]);
    free(a);

    return det_val;
}

void input(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (scanf("%lf", &matrix[i][j]) != 1) {
                matrix[0][0] = NAN;  // флаг ошибки
                return;
            }
}

void output(double det_val) {
    if (isnan(det_val)) {
        printf("n/a");
    } else {
        printf("%.6f", det_val);
    }
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2 || n <= 0 || m <= 0) {
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
            for (int k = 0; k < i; k++) free(matrix[k]);
            free(matrix);
            printf("n/a");
            return 0;
        }
    }

    input(matrix, n, m);
    double det_val = det(matrix, n, m);
    output(det_val);

    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);

    return 0;
}
