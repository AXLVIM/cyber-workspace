#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0 || n != m) {
        printf("n/a");
        return 0;
    }

    double **a = malloc(n * sizeof(double *));
    double **inv = malloc(n * sizeof(double *));
    if (!a || !inv) {
        printf("n/a");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        a[i] = malloc(n * sizeof(double));
        inv[i] = malloc(n * sizeof(double));
        if (!a[i] || !inv[i]) {
            printf("n/a");
            return 0;
        }
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &a[i][j]) != 1) {
                printf("n/a");
                return 0;
            }
            inv[i][j] = (i == j ? 1.0 : 0.0);
        }
    }

    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int r = i + 1; r < n; r++)
            if (fabs(a[r][i]) > fabs(a[pivot][i])) pivot = r;

        if (fabs(a[pivot][i]) < 1e-12) {
            printf("n/a");
            return 0;
        }

        if (pivot != i) {
            double *tmp = a[i];
            a[i] = a[pivot];
            a[pivot] = tmp;
            tmp = inv[i];
            inv[i] = inv[pivot];
            inv[pivot] = tmp;
        }

        double diag = a[i][i];
        for (int c = 0; c < n; c++) {
            a[i][c] /= diag;
            inv[i][c] /= diag;
        }

        for (int r = 0; r < n; r++) {
            if (r == i) continue;
            double factor = a[r][i];
            for (int c = 0; c < n; c++) {
                a[r][c] -= factor * a[i][c];
                inv[r][c] -= factor * inv[i][c];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.6f", inv[i][j]);
            if (j + 1 < n) printf(" ");
        }
        if (i + 1 < n) printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(a[i]);
        free(inv[i]);
    }
    free(a);
    free(inv);

    return 0;
}
