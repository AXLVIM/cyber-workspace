#include <stdio.h>

int main(void) {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        printf("n/a\n");
        return 0;
    }

    int sum = a + b;
    int diff = a - b;
    int prod = a * b;

    printf("%d %d %d ", sum, diff, prod);

    if (b == 0) {
        printf("n/a\n");
    } else {
        printf("%d\n", a / b);
    }

    return 0;
}
