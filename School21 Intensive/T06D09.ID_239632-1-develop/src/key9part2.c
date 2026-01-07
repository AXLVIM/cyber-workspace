#include <stdio.h>

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int compare(int *a, int len_a, int *b, int len_b);
int read_number(int *arr);

int main() {
    int a[LEN], b[LEN];
    int len_a = read_number(a);
    int len_b = read_number(b);

    if (len_a == -1 || len_b == -1) {
        printf("n/a\n");
        return 0;
    }

    int sum_res[LEN + 1], sub_res[LEN];
    int sum_len, sub_len;

    sum(a, len_a, b, len_b, sum_res, &sum_len);
    for (int i = 0; i < sum_len; i++) {
        if (i > 0) printf(" ");
        printf("%d", sum_res[i]);
    }
    printf("\n");

    if (compare(a, len_a, b, len_b) < 0) {
        printf("n/a\n");
    } else {
        sub(a, len_a, b, len_b, sub_res, &sub_len);
        for (int i = 0; i < sub_len; i++) {
            if (i > 0) printf(" ");
            printf("%d", sub_res[i]);
        }
        printf("\n");
    }

    return 0;
}

int read_number(int *arr) {
    char ch;
    int len = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == ' ') continue;
        if (ch < '0' || ch > '9') return -1;
        if (len >= LEN) return -1;
        arr[len++] = ch - '0';
    }
    if (len == 0) return -1;
    return len;
}

int compare(int *a, int len_a, int *b, int len_b) {
    int i = 0, j = 0;
    while (i < len_a && a[i] == 0) i++;
    while (j < len_b && b[j] == 0) j++;

    int effective_len_a = len_a - i;
    int effective_len_b = len_b - j;

    if (effective_len_a > effective_len_b) return 1;
    if (effective_len_a < effective_len_b) return -1;

    for (; i < len_a && j < len_b; i++, j++) {
        if (a[i] > b[j]) return 1;
        if (a[i] < b[j]) return -1;
    }
    return 0;
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int temp[LEN + 1] = {0};
    int i = len1 - 1, j = len2 - 1, k = (len1 > len2 ? len1 : len2);
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int d1 = i >= 0 ? buff1[i] : 0;
        int d2 = j >= 0 ? buff2[j] : 0;
        int s = d1 + d2 + carry;
        temp[k] = s % 10;
        carry = s / 10;
        i--;
        j--;
        k--;
    }

    int start = 0;
    if (temp[0] == 0) start = 1;
    *result_length = (len1 > len2 ? len1 : len2) + 1 - start;

    for (int m = 0; m < *result_length; m++) result[m] = temp[start + m];
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int temp[LEN] = {0};
    int i = len1 - 1, j = len2 - 1, k = len1 - 1;
    int borrow = 0;

    while (i >= 0) {
        int d1 = buff1[i];
        int d2 = j >= 0 ? buff2[j] : 0;
        int s = d1 - d2 - borrow;
        if (s < 0) {
            s += 10;
            borrow = 1;
        } else
            borrow = 0;
        temp[k] = s;
        i--;
        j--;
        k--;
    }

    int start = 0;
    while (start < len1 - 1 && temp[start] == 0) start++;
    *result_length = len1 - start;

    for (int m = 0; m < *result_length; m++) result[m] = temp[start + m];
}