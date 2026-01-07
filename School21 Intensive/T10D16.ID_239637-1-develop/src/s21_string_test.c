#include "s21_string.h"

#include <stdio.h>

// ==== STRLEN ====
void s21_strlen_test(const char *str, size_t expected) {
    size_t result = s21_strlen(str);
    printf("[s21_strlen] Input: \"%s\"\n", str ? str : "NULL");
    printf("Output: %zu | Expected: %zu | Result: %s\n\n", result, expected,
           result == expected ? "SUCCESS" : "FAIL");
}

void s21_strlen_test_suite() {
    s21_strlen_test("hello", 5);
    s21_strlen_test("school21", 8);
    s21_strlen_test("", 0);
    s21_strlen_test("a", 1);
    s21_strlen_test(NULL, 0);  // NULL test
}

// ==== STRCMP ====
void s21_strcmp_test(const char *str1, const char *str2, int expected_sign) {
    int result = s21_strcmp(str1, str2);
    int sign = (result == 0) ? 0 : (result > 0 ? 1 : -1);
    int expected = (expected_sign == 0) ? 0 : (expected_sign > 0 ? 1 : -1);

    printf("[s21_strcmp] Input: \"%s\" vs \"%s\"\n", str1 ? str1 : "NULL", str2 ? str2 : "NULL");
    printf("Output: %d | Expected: %d | Result: %s\n\n", result, expected_sign,
           sign == expected ? "SUCCESS" : "FAIL");
}

void s21_strcmp_test_suite() {
    s21_strcmp_test("abc", "abc", 0);
    s21_strcmp_test("abc", "abd", -1);
    s21_strcmp_test("abcd", "abc", 1);
    s21_strcmp_test("", "", 0);
    s21_strcmp_test("a", "", 1);
    s21_strcmp_test("", "a", -1);
}

// ==== STRCPY ====
void s21_strcpy_test(const char *src, const char *expected) {
    char buffer[1024] = {0};
    s21_strcpy(buffer, src);
    int result = s21_strcmp(buffer, expected) == 0;
    printf("[s21_strcpy] Source: \"%s\"\n", src ? src : "NULL");
    printf("Output: \"%s\" | Expected: \"%s\" | Result: %s\n\n", buffer, expected,
           result ? "SUCCESS" : "FAIL");
}

void s21_strcpy_test_suite() {
    s21_strcpy_test("hello", "hello");
    s21_strcpy_test("school21", "school21");
    s21_strcpy_test("", "");
}

// ==== STRCAT ====
void s21_strcat_test(const char *s1, const char *s2, const char *expected) {
    char buffer[1024] = {0};
    s21_strcpy(buffer, s1);
    s21_strcat(buffer, s2);
    int result = s21_strcmp(buffer, expected) == 0;
    printf("[s21_strcat] \"%s\" + \"%s\"\n", s1, s2);
    printf("Output: \"%s\" | Expected: \"%s\" | Result: %s\n\n", buffer, expected,
           result ? "SUCCESS" : "FAIL");
}

void s21_strcat_test_suite() {
    s21_strcat_test("hello", "world", "helloworld");
    s21_strcat_test("", "data", "data");
    s21_strcat_test("X", "", "X");
}

// ==== STRCHR ====
void s21_strchr_test(const char *str, int ch, const char *expected) {
    char *result = s21_strchr(str, ch);
    int match = (result && expected && s21_strcmp(result, expected) == 0) || (!result && !expected);
    printf("[s21_strchr] \"%s\", '%c'\n", str, ch);
    printf("Output: %s | Expected: %s | Result: %s\n\n", result ? result : "NULL",
           expected ? expected : "NULL", match ? "SUCCESS" : "FAIL");
}

void s21_strchr_test_suite() {
    s21_strchr_test("hello", 'e', "ello");
    s21_strchr_test("school21", '2', "21");
    s21_strchr_test("abc", 'x', NULL);
    s21_strchr_test("", 'a', NULL);
}

// ==== STRSTR ====
void s21_strstr_test(const char *haystack, const char *needle, const char *expected) {
    char *result = s21_strstr(haystack, needle);
    int match = (result && expected && s21_strcmp(result, expected) == 0) || (!result && !expected);
    printf("[s21_strstr] \"%s\" find \"%s\"\n", haystack, needle);
    printf("Output: %s | Expected: %s | Result: %s\n\n", result ? result : "NULL",
           expected ? expected : "NULL", match ? "SUCCESS" : "FAIL");
}

void s21_strstr_test_suite() {
    s21_strstr_test("hello world", "world", "world");
    s21_strstr_test("abcdabc", "bc", "bcdabc");
    s21_strstr_test("abcdef", "gh", NULL);
    s21_strstr_test("abc", "", "abc");
}

// ==== STRTOK ====
void s21_strtok_test(const char *input_str, const char *delim, const char *expected_tokens[],
                     int expected_count) {
    char buffer[1024];
    s21_strcpy(buffer, input_str);
    char *token = s21_strtok(buffer, delim);
    int success = 1;
    int index = 0;

    while (token && index < expected_count) {
        if (s21_strcmp(token, expected_tokens[index]) != 0) {
            success = 0;
            break;
        }
        index++;
        token = s21_strtok(NULL, delim);
    }

    if (index != expected_count) success = 0;

    printf("[s21_strtok] Input: \"%s\" | Delim: \"%s\"\n", input_str, delim);
    printf("Result: %s\n\n", success ? "SUCCESS" : "FAIL");
}

void s21_strtok_test_suite() {
    const char *tokens1[] = {"a", "b", "c"};
    s21_strtok_test("a,b,c", ",", tokens1, 3);

    const char *tokens2[] = {"abc"};
    s21_strtok_test("abc", ",", tokens2, 1);

    const char *tokens3[] = {NULL};
    s21_strtok_test(",", ",", tokens3, 0);
}

// ==== MAIN ====
int main() {
#ifdef TEST_STRLEN
    s21_strlen_test_suite();
#elif defined(TEST_STRCMP)
    s21_strcmp_test_suite();
#elif defined(TEST_STRCPY)
    s21_strcpy_test_suite();
#elif defined(TEST_STRCAT)
    s21_strcat_test_suite();
#elif defined(TEST_STRCHR)
    s21_strchr_test_suite();
#elif defined(TEST_STRSTR)
    s21_strstr_test_suite();
#elif defined(TEST_STRTOK)
    s21_strtok_test_suite();
#else
    printf("No test defined. Use -DTEST_XXX during compilation.\n");
#endif
    return 0;
}
