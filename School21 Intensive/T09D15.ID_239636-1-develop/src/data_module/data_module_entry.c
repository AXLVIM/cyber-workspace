#include <stdio.h>
#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"

int normalization(double *data, int n) {
    if (n <= 0) return 0;

    double max_val = max(data, n);
    double min_val = min(data, n);

    if (max_val == min_val) return 0;

    for (int i = 0; i < n; i++) {
        data[i] = (data[i] - min_val) / (max_val - min_val);
    }
    return 1;
}

int main(void) {
    int n = 0;
    double data[1000];

    if (!input(data, &n)) {
        printf("ERROR\n");
        return 1;
    }

    if (normalization(data, n)) {
        output(data, n);
        putchar('\n');
    } else {
        printf("ERROR\n");
    }

    return 0;
}