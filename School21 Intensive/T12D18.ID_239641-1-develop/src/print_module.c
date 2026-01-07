#include "print_module.h"

#include <stdio.h>
#include <time.h>

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), const char *message) {
    time_t rawtime;
    time(&rawtime);
    const struct tm *timeinfo = localtime(&rawtime);

    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);

    const char *prefix = Log_prefix;
    while (*prefix) print(*prefix++);
    print(' ');
    for (int i = 0; buffer[i]; i++) print(buffer[i]);
    print(' ');
    while (*message) print(*message++);
    print('\n');
}
