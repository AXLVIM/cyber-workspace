#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_TOKEN 3  // 2 chars + null terminator

// Helper: check if string is a valid hex number (2 chars)
int is_valid_hex(const char *s) {
    if (strlen(s) != 2) return 0;
    return isxdigit(s[0]) && isxdigit(s[1]);
}

// Encode: characters -> space-separated hex
void encode() {
    char line[MAX_LINE];
    if (!fgets(line, sizeof(line), stdin)) {
        printf("n/a\n");
        return;
    }

    char *token = strtok(line, " \n");
    if (!token) {
        printf("n/a\n");
        return;
    }

    int first = 1;
    while (token) {
        if (strlen(token) != 1) {  // must be a single character
            printf("n/a\n");
            return;
        }
        if (!first) printf(" ");
        printf("%02X", token[0]);
        first = 0;
        token = strtok(NULL, " \n");
    }
    printf("\n");
}

// Decode: space-separated 2-digit hex -> characters
void decode() {
    char line[MAX_LINE];
    if (!fgets(line, sizeof(line), stdin)) {
        printf("n/a\n");
        return;
    }

    char *token = strtok(line, " \n");
    if (!token) {
        printf("n/a\n");
        return;
    }

    int first = 1;
    while (token) {
        if (!is_valid_hex(token)) {  // must be 2-digit hex
            printf("n/a\n");
            return;
        }
        int value;
        sscanf(token, "%2x", &value);
        if (!first) printf(" ");
        printf("%c", value);
        first = 0;
        token = strtok(NULL, " \n");
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("n/a\n");
        return 0;
    }

    int mode = atoi(argv[1]);
    if (mode != 0 && mode != 1) {
        printf("n/a\n");
        return 0;
    }

    if (mode == 0)
        encode();
    else
        decode();

    return 0;
}