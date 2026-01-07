#include "s21_string.h"

size_t s21_strlen(const char *str) {
    if (!str) return 0;
    size_t len = 0;
    while (*str++) len++;
    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    if (!str1 || !str2) return -1;
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

char *s21_strcpy(char *dest, const char *src) {
    if (!dest || !src) return NULL;
    char *tmp = dest;
    while ((*dest++ = *src++));
    return tmp;
}

char *s21_strcat(char *dest, const char *src) {
    if (!dest || !src) return NULL;
    char *tmp = dest;
    while (*dest) dest++;
    while ((*dest++ = *src++));
    return tmp;
}

char *s21_strchr(const char *str, int ch) {
    if (!str) return NULL;
    while (*str && *str != (char)ch) str++;
    return (*str == (char)ch) ? (char *)str : NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (!haystack || !needle) return NULL;
    if (!*needle) return (char *)haystack;

    for (; *haystack; haystack++) {
        const char *h = haystack, *n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        if (!*n) return (char *)haystack;
    }
    return NULL;
}

char *s21_strtok(char *str, const char *delim) {
    static char *last = NULL;
    if (!delim) return NULL;

    if (str) last = str;
    if (!last) return NULL;

    while (*last && s21_strchr(delim, *last)) last++;
    if (!*last) return NULL;

    char *token = last;
    while (*last && !s21_strchr(delim, *last)) last++;

    if (*last) {
        *last = '\0';
        last++;
    } else {
        last = NULL;
    }

    return token;
}
