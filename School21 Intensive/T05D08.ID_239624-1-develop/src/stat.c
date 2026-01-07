#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];

    if (input(data, &n) != 0) {
        printf("n/a\n");
        return 0;
    }

    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

// Input function
int input(int *a, int *n) {
    if (scanf("%d", n) != 1) return 1;

    if (*n < 1 || *n > NMAX) return 1;

    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }

    return 0;
}

// Output array
void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

// Maximum value
int max(int *a, int n) {
    int m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > m) m = a[i];
    return m;
}

// Minimum value
int min(int *a, int n) {
    int m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < m) m = a[i];
    return m;
}

// Mean (expected value)
double mean(int *a, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

// Variance (discrete uniform)
double variance(int *a, int n) {
    double m = mean(a, n);
    double var = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = a[i] - m;
        var += diff * diff;
    }
    return var / n;
}

// Output all results
void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f\n", max_v, min_v, mean_v, variance_v);
}