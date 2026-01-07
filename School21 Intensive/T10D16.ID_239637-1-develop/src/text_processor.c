#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAX_LEN 101

void print_spaces(int n) {
    for (int i = 0; i < n; i++) putchar(' ');
}

void print_line(char **words, int from, int to, int width, int is_last_line) {
    int total_len = 0;
    for (int i = from; i < to; i++) total_len += s21_strlen(words[i]);

    int gaps = to - from - 1;
    int spaces = width - total_len;

    for (int i = from; i < to; i++) {
        printf("%s", words[i]);
        if (i != to - 1) {
            int pad = is_last_line ? 1 : spaces / gaps + (spaces % gaps > 0);
            print_spaces(pad);
            spaces -= pad;
            gaps--;
        }
    }
}

void format_text(int width, char *input) {
    char *words[200];
    int count = 0;

    char *p = input;
    while (*p) {
        while (*p == ' ') p++;
        if (!*p) break;
        words[count++] = p;
        while (*p && *p != ' ') p++;
        if (*p) *p++ = '\0';
    }

    int i = 0;
    while (i < count) {
        int cur_len = 0;
        int start = i;

        while (i < count) {
            int wlen = s21_strlen(words[i]);

            if ((cur_len == 0 && wlen > width)) {
                // длинное слово — переносим по кускам
                const char *w = words[i];
                int offset = 0;

                while (wlen - offset > width) {
                    for (int k = 0; k < width - 1; k++) putchar(w[offset + k]);
                    putchar('-');
                    putchar('\n');
                    offset += width - 1;
                }
                for (int k = offset; k < wlen; k++) putchar(w[k]);
                i++;
                if (i < count) putchar('\n');
                goto next_line;
            }

            if ((cur_len == 0 && wlen <= width) || (cur_len + 1 + wlen <= width)) {
                cur_len += (cur_len ? 1 : 0) + wlen;
                i++;
            } else {
                break;
            }
        }

        // теперь смотрим, влезает ли хотя бы кусок длинного слова
        if (i < count) {
            int wlen = s21_strlen(words[i]);
            int room = width - cur_len - (cur_len > 0 ? 1 : 0);

            if (wlen > width && room >= 2) {
                // печатаем текущую строку + кусок слова
                if (start < i) {
                    print_line(words, start, i, cur_len + room, 0);
                    putchar(' ');
                }

                for (int k = 0; k < room - 1; k++) putchar(words[i][k]);
                putchar('-');

                // смещаем указатель слова
                words[i] += room - 1;
                putchar('\n');
                goto next_line;
            }
        }

        print_line(words, start, i, width, i == count);
        if (i < count) putchar('\n');

    next_line:
        continue;
    }
}

int main(int argc, char **argv) {
    if (argc != 2 || argv[1][0] != '-' || argv[1][1] != 'w' || argv[1][2] != '\0') {
        printf("n/a\n");
        return 0;
    }

    int width;
    if (scanf("%d\n", &width) != 1 || width <= 0) {
        printf("n/a\n");
        return 0;
    }

    char input[MAX_LEN] = {0};
    if (!fgets(input, MAX_LEN, stdin)) {
        printf("n/a\n");
        return 0;
    }

    for (int i = 0; input[i]; i++)
        if (input[i] == '\n') input[i] = '\0';

    format_text(width, input);
    return 0;
}