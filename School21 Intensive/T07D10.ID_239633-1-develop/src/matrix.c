#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int read_int(int *x) { return scanf("%d", x) == 1; }

void print_matrix(int **m, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", m[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
}

/* ----- ALLOCATION METHODS ----- */

int **alloc_static(int rows, int cols, int storage[MAX][MAX]) {
    (void)cols;  // suppress unused parameter warning
    int **m = malloc(rows * sizeof(int *));
    if (!m) return NULL;
    for (int i = 0; i < rows; i++) m[i] = storage[i];
    return m;
}

int **alloc_dyn1(int rows, int cols) {
    int *data = malloc(rows * cols * sizeof(int));
    if (!data) return NULL;

    int **m = malloc(rows * sizeof(int *));
    if (!m) {
        free(data);
        return NULL;
    }

    for (int i = 0; i < rows; i++) m[i] = data + i * cols;

    return m;
}

int **alloc_dyn2(int rows, int cols) {
    int **m = malloc(rows * sizeof(int *));
    if (!m) return NULL;

    for (int i = 0; i < rows; i++) {
        m[i] = malloc(cols * sizeof(int));
        if (!m[i]) {
            for (int k = 0; k < i; k++) free(m[k]);
            free(m);
            return NULL;
        }
    }
    return m;
}

int **alloc_dyn3(int rows, int cols) {
    int **m = malloc(rows * sizeof(int *));
    int *data = malloc(rows * cols * sizeof(int));

    if (!m || !data) {
        free(m);
        free(data);
        return NULL;
    }

    for (int i = 0; i < rows; i++) m[i] = data + i * cols;

    return m;
}

/* ----- FREE METHODS ----- */

void free_dyn1(int **m) {
    free(m[0]);  // data block
    free(m);
}

void free_dyn2(int **m, int rows) {
    for (int i = 0; i < rows; i++) free(m[i]);
    free(m);
}

void free_dyn3(int **m) {
    free(m[0]);  // data block
    free(m);
}

/* ----- MAIN LOGIC ----- */

int main() {
    int method;
    if (!read_int(&method) || method < 1 || method > 4) {
        printf("n/a");
        return 0;
    }

    int rows, cols;
    if (!read_int(&rows) || !read_int(&cols) || rows <= 0 || cols <= 0 || rows > MAX || cols > MAX) {
        printf("n/a");
        return 0;
    }

    int static_storage[MAX][MAX];

    int **matrix = NULL;

    switch (method) {
        case 1:
            matrix = alloc_static(rows, cols, static_storage);
            break;
        case 2:
            matrix = alloc_dyn1(rows, cols);
            break;
        case 3:
            matrix = alloc_dyn2(rows, cols);
            break;
        case 4:
            matrix = alloc_dyn3(rows, cols);
            break;
    }

    if (!matrix) {
        printf("n/a");
        return 0;
    }

    /* Read matrix */
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!read_int(&matrix[i][j])) {
                printf("n/a");
                /* Free memory if dynamic or static pointer array */
                if (method == 1)
                    free(matrix);
                else if (method == 2)
                    free_dyn1(matrix);
                else if (method == 3)
                    free_dyn2(matrix, rows);
                else if (method == 4)
                    free_dyn3(matrix);
                return 0;
            }

    print_matrix(matrix, rows, cols);

    /* Free memory based on method */
    if (method == 1)
        free(matrix);  // static pointer array
    else if (method == 2)
        free_dyn1(matrix);
    else if (method == 3)
        free_dyn2(matrix, rows);
    else if (method == 4)
        free_dyn3(matrix);

    return 0;
}