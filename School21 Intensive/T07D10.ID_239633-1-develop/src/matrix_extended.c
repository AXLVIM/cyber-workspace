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

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }
}

int **alloc_static(int rows, int cols, int storage[MAX][MAX]) {
    (void)cols;
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

void free_dyn1(int **m) {
    free(m[0]);
    free(m);
}
void free_dyn2(int **m, int rows) {
    for (int i = 0; i < rows; i++) free(m[i]);
    free(m);
}
void free_dyn3(int **m) {
    free(m[0]);
    free(m);
}

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

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!read_int(&matrix[i][j])) {
                printf("n/a");
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

    /* Print matrix */
    print_matrix(matrix, rows, cols);
    printf("\n");

    /* Compute row max */
    int row_max[MAX];
    for (int i = 0; i < rows; i++) {
        int max = matrix[i][0];
        for (int j = 1; j < cols; j++)
            if (matrix[i][j] > max) max = matrix[i][j];
        row_max[i] = max;
    }
    print_array(row_max, rows);
    printf("\n");

    /* Compute column min */
    int col_min[MAX];
    for (int j = 0; j < cols; j++) {
        int min = matrix[0][j];
        for (int i = 1; i < rows; i++)
            if (matrix[i][j] < min) min = matrix[i][j];
        col_min[j] = min;
    }
    print_array(col_min, cols);

    /* Free memory */
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