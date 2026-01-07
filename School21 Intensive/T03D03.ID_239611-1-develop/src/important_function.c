#include <math.h>
#include <stdio.h>

int main(void) {
    double x;

    if (scanf("%lf", &x) != 1) {
        printf("n/a\n");
        return 0;
    }

    double y = 0.007 * pow(x, 4) + ((22.8 * cbrt(x) - 1000) * x + 3) / (x * x / 2.0) -
               x * pow(10 + x, 2.0 / x) - 1.01;

    printf("%.1lf\n", y);
    return 0;
}