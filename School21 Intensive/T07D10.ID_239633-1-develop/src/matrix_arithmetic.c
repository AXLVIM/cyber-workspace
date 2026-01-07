#include <stdio.h>
#include <stdlib.h>

int input(int ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) return 0;
    *matrix = malloc(*n * sizeof(int *));
    if (!*matrix) return 0;
    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = malloc(*m * sizeof(int));
        if (!(*matrix)[i]) return 0;
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &(*matrix)[i][j]) != 1) return 0;
        }
    }
    return 1;
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j != m - 1) printf(" ");
        }
        if (i != n - 1) printf("\n");
    }
    printf("\n");
}

int sum(int **a, int n1, int m1, int **b, int n2, int m2, int ***res, int *nr, int *mr) {
    if (n1 != n2 || m1 != m2) return 0;
    *nr = n1;
    *mr = m1;
    *res = malloc(n1 * sizeof(int *));
    if (!*res) return 0;
    for (int i = 0; i < n1; i++) {
        (*res)[i] = malloc(m1 * sizeof(int));
        if (!(*res)[i]) return 0;
        for (int j = 0; j < m1; j++) (*res)[i][j] = a[i][j] + b[i][j];
    }
    return 1;
}

int mul(int **a, int n1, int m1, int **b, int n2, int m2, int ***res, int *nr, int *mr) {
    if (m1 != n2) return 0;
    *nr = n1;
    *mr = m2;
    *res = malloc(n1 * sizeof(int *));
    if (!*res) return 0;
    for (int i = 0; i < n1; i++) {
        (*res)[i] = malloc(m2 * sizeof(int));
        if (!(*res)[i]) return 0;
        for (int j = 0; j < m2; j++) {
            (*res)[i][j] = 0;
            for (int k = 0; k < m1; k++) (*res)[i][j] += a[i][k] * b[k][j];
        }
    }
    return 1;
}

int transpose(int **matrix, int n, int m, int ***res, int *nr, int *mr) {
    *nr = m;
    *mr = n;
    *res = malloc(m * sizeof(int *));
    if (!*res) return 0;
    for (int i = 0; i < m; i++) {
        (*res)[i] = malloc(n * sizeof(int));
        if (!(*res)[i]) return 0;
        for (int j = 0; j < n; j++) (*res)[i][j] = matrix[j][i];
    }
    return 1;
}

int main() {
    int op;
    if (scanf("%d", &op) != 1) {
        printf("n/a\n");
        return 0;
    }

    int **a = NULL, **b = NULL, **res = NULL;
    int n1, m1, n2, m2, nr, mr;

    if (!input(&a, &n1, &m1)) {
        printf("n/a\n");
        return 0;
    }

    int ok = 0;
    switch (op) {
        case 1:  // addition
            if (!input(&b, &n2, &m2)) {
                printf("n/a\n");
                free_matrix(a, n1);
                return 0;
            }
            ok = sum(a, n1, m1, b, n2, m2, &res, &nr, &mr);
            break;
        case 2:  // multiplication
            if (!input(&b, &n2, &m2)) {
                printf("n/a\n");
                free_matrix(a, n1);
                return 0;
            }
            ok = mul(a, n1, m1, b, n2, m2, &res, &nr, &mr);
            break;
        case 3:  // transpose
            ok = transpose(a, n1, m1, &res, &nr, &mr);
            break;
        default:
            printf("n/a\n");
            free_matrix(a, n1);
            return 0;
    }

    if (!ok) {
        printf("n/a\n");
        free_matrix(a, n1);
        if (b) free_matrix(b, n2);
        return 0;
    }

    output(res, nr, mr);

    free_matrix(a, n1);
    if (b) free_matrix(b, n2);
    free_matrix(res, nr);

    return 0;
}