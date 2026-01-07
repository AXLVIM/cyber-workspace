#include <stdio.h>

int maximum(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int main(void) {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        printf("n/a\n");
        return 0;
    }

    printf("%d\n", maximum(a, b));
    return 0;
}