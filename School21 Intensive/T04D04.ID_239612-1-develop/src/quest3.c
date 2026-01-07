#include <stdio.h>
#include <stdlib.h>

// Recursive Fibonacci function
int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("n/a\n");
        return 0;
    }

    printf("%d\n", fibonacci(n));
    return 0;
}