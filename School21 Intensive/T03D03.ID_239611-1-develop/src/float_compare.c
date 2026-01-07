#include <math.h>
#include <stdio.h>

int main(void) {
    double x = 0.0;
    const double EPSILON = 1e-6;

    if (fabs(x) < EPSILON) {
    }

    printf("OK!\n");
    return 0;
}