#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);

int **alloc_matrix(int n, int m) {
    int **a = malloc(n * sizeof(int *));
    if (!a) return NULL;

    for (int i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
        if (!a[i]) return NULL;
    }
    return a;
}

void free_matrix(int **a, int n) {
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
}

int cmp_int(const void *a, const void *b) { return (*(const int *)a - *(const int *)b); }

int skip_empty_lines() {
    int c;
    do {
        c = getchar();
        if (c == EOF) return EOF;
        if (c != '\n' && c != ' ' && c != '\t' && c != '\r') {
            ungetc(c, stdin);
            return 1;
        }
    } while (1);
}

void input(int ***matrix, int *n, int *m) {
    *n = -1;

    if (skip_empty_lines() == EOF) return;

    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) {
        *n = -1;
        return;
    }

    if (skip_empty_lines() == EOF) {
        *n = -1;
        return;
    }

    *matrix = alloc_matrix(*n, *m);
    if (!(*matrix)) {
        *n = -1;
        return;
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &((*matrix)[i][j])) != 1) {
                *n = -1;
                return;
            }
        }
    }
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j + 1 < m) printf(" ");
        }
        if (i + 1 < n) printf("\n");
    }
}

/* ====================== ЗМЕЙКА ПО ГОРИЗОНТАЛИ ======================= */
void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int size = n * m;
    int *flat = malloc(size * sizeof(int));
    if (!flat) return;

    int k = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) flat[k++] = matrix[i][j];

    qsort(flat, size, sizeof(int), cmp_int);

    k = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) result_matrix[i][j] = flat[k++];
        } else {
            for (int j = m - 1; j >= 0; j--) result_matrix[i][j] = flat[k++];
        }
    }

    free(flat);
}

/* ====================== ЗМЕЙКА ПО ВЕРТИКАЛИ ======================= */
void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int size = n * m;
    int *flat = malloc(size * sizeof(int));
    if (!flat) return;

    int k = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) flat[k++] = matrix[i][j];

    qsort(flat, size, sizeof(int), cmp_int);

    k = 0;
    for (int j = 0; j < m; j++) {
        if (j % 2 == 0) {
            for (int i = 0; i < n; i++) result_matrix[i][j] = flat[k++];
        } else {
            for (int i = n - 1; i >= 0; i--) result_matrix[i][j] = flat[k++];
        }
    }

    free(flat);
}

/* ========================= MAIN ============================= */

int main() {
    int **matrix = NULL, **result = NULL;
    int n, m;

    input(&matrix, &n, &m);

    if (n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }

    result = alloc_matrix(n, m);
    if (!result) {
        printf("n/a");
        free_matrix(matrix, n);
        return 0;
    }

    sort_vertical(matrix, n, m, result);
    output(result, n, m);

    printf("\n\n");

    sort_horizontal(matrix, n, m, result);
    output(result, n, m);

    free_matrix(matrix, n);
    free_matrix(result, n);
    return 0;
}