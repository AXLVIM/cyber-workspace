#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int find_number(int *a, int n, double m, double v);

int main() {
    int n, data[NMAX];

    if (input(data, &n) != 0) {
        printf("n/a\n");
        return 0;
    }

    double m = mean(data, n);
    double v = variance(data, n);

    int res = find_number(data, n, m, v);
    printf("%d\n", res);

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) return 1;
    if (*n < 1 || *n > NMAX) return 1;

    for (int i = 0; i < *n; i++)
        if (scanf("%d", &a[i]) != 1) return 1;

    return 0;
}

double mean(int *a, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

double variance(int *a, int n) {
    double m = mean(a, n);
    double var = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = a[i] - m;
        var += diff * diff;
    }
    return var / n;
}

int find_number(int *a, int n, double m, double v) {
    double upper = m + 3.0 * sqrt(v);
    for (int i = 0; i < n; i++) {
        int num = a[i];
        if (num == 0) continue;
        if (num % 2 != 0) continue;
        if (num < m) continue;
        if (num > upper) continue;
        return num;
    }
    return 0;
}