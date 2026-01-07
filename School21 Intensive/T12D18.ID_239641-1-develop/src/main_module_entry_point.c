#include <stdio.h>

#include "documentation_module.h"
#include "print_module.h"

int main() {
#ifdef Q1
    // Code for Quest_1: Use print_module functionality
    print_log(print_char, Module_load_success_message);
#endif

#ifdef Q2
    // Code for Quest_2: Use documentation_module functionality
    const char *docs[] = {DOCUMENTS};
    int *availability =
        check_available_documentation_module(validate, DOCUMENTS_COUNT, docs[0], docs[1], docs[2], docs[3]);
    for (int i = 0; i < DOCUMENTS_COUNT; ++i) {
        printf("%-15s: %s\n", docs[i], availability[i] ? "available" : "unavailable");
    }
#endif

    return 0;
}
