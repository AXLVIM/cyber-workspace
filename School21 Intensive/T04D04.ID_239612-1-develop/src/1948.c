#include <stdio.h>

int abs_val(int n) { return n < 0 ? -n : n; }

int divides(int a, int b) {
    if (a <= 0) return 0;
    int temp = b;
    while (temp > 0) {
        temp -= a;
    }
    return temp == 0;
}

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (divides(i, n)) return 0;
    }
    return 1;
}

int largest_prime_divisor(int a) {
    int largest = -1;
    for (int i = 2; i <= a; i++) {
        if (divides(i, a) && is_prime(i)) {
            largest = i;
        }
    }
    if (largest == -1 && is_prime(a)) {
        return a;
    }
    return largest;
}

int main() {
    int a;
    if (scanf("%d", &a) != 1) {
        printf("n/a");
        return 0;
    }

    a = abs_val(a);

    if (a <= 1) {
        printf("n/a\n");
        return 0;
    }

    int result = largest_prime_divisor(a);

    if (result == -1) {
        printf("n/a");
    } else {
        printf("%d\n", result);
    }

    return 0;
}