#include <stdio.h>

int main(void) {
    double x, y;

    if (scanf("%lf %lf", &x, &y) != 2) {
        printf("n/a\n");
        return 0;
    }

    double dist2 = x * x + y * y;
    if (dist2 < 25.0) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }

    return 0;
}