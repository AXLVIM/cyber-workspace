#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);

int main(void) {
    int picture_data[N][M];
    int *picture[N];

    transform(&picture_data[0][0], picture, N, M);
    reset_picture(picture, N, M);
    make_picture(picture, N, M);

    // Print the final matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", picture[i][j]);
            if (j < M - 1) printf(" ");
        }
        if (i < N - 1) printf("\n");
    }

    return 0;
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void make_picture(int **picture, int n, int m) {
    // Pre-defined static arrays
    int frame_w[M] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[N] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[4] = {7, 7, 7, 7};
    int tree_foliage[4] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    // Top row (frame_w)
    for (int j = 0; j < m; j++) {
        if (j < M) picture[0][j] = frame_w[j];
    }

    // Left and right columns (frame_h)
    for (int i = 0; i < n; i++) {
        if (i < N) {
            picture[i][0] = frame_h[i];
            picture[i][m - 1] = frame_h[i];
        }
    }

    // Tree trunk
    int trunk_row = n - 5;
    int trunk_col = 2;
    for (int i = 0; i < 4; i++) {
        if (trunk_row + i < n && trunk_col < m) picture[trunk_row + i][trunk_col] = tree_trunk[i];
    }

    // Tree foliage
    int foliage_row = n - 9;
    int foliage_col = 1;
    for (int i = 0; i < 4; i++) {
        if (foliage_row + i < n && foliage_col + i < m)
            picture[foliage_row + i][foliage_col + i] = tree_foliage[i];
    }

    // Sun
    int sun_row = 1;
    int sun_col = m - 6;
    for (int i = 0; i < 6; i++) {
        if (sun_row + i >= n) break;
        for (int j = 0; j < 5; j++) {
            if (sun_col + j >= m) break;
            picture[sun_row + i][sun_col + j] = sun_data[i][j];
        }
    }
}