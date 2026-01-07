#include "documentation_module.h"

#include <stdarg.h>
#include <string.h>

int validate(const char *data) { return strcmp(data, AVAILABLE_DOCUMENT) == 0; }

int *check_available_documentation_module(int (*validate)(const char *), int document_count, ...) {
    static int result[DOCUMENTS_COUNT];
    va_list args;
    va_start(args, document_count);

    for (int i = 0; i < document_count; ++i) {
        const char *doc = va_arg(args, const char *);
        result[i] = validate(doc);
    }

    va_end(args);
    return result;
}
