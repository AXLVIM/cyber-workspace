#include <math.h>
#include <stdio.h>

int main() {
    double pi = 3.14159265358979323846;
    int n = 42;
    double step = 2 * pi / (n - 1);

    for (int i = 0; i < n; i++) {
        double x = -pi + i * step;

        // Witch of Agnesi: y = 1 / (1 + x^2)
        double y_agnesi = 1.0 / (1.0 + x * x);

        // Lemniscate of Bernoulli: y^2 = 1 - x^2 => y = sqrt(1 - x^2) if x in [-1,1]
        double y_lemniscate;
        if (x >= -1.0 && x <= 1.0) {
            y_lemniscate = sqrt(1.0 - x * x);
        }

        // Quadratic hyperbola: y = 1 / x
        double y_hyperbola;
        if (x != 0.0) {
            y_hyperbola = 1.0 / x;
        }

        // Print row with 7 decimals
        printf("%.7f|%.7f|", x, y_agnesi);
        if (x >= -1.0 && x <= 1.0)
            printf("%.7f|", y_lemniscate);
        else
            printf("-|");

        if (x != 0.0)
            printf("%.7f\n", y_hyperbola);
        else
            printf("-\n");
    }

    return 0;
}