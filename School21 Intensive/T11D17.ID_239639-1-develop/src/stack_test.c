#include "stack.h"

#include <stdio.h>

int test_stack_push_pop(void) {
    int result = SUCCESS;
    Stack* s = init();

    if (s == NULL) return FAIL;

    result |= push(s, 10);
    result |= push(s, 20);
    result |= push(s, 30);

    int val = 0;
    result |= pop(s, &val);
    if (val != 30) result = FAIL;
    result |= pop(s, &val);
    if (val != 20) result = FAIL;
    result |= pop(s, &val);
    if (val != 10) result = FAIL;

    int check_empty = pop(s, &val);
    if (check_empty != FAIL) result = FAIL;

    destroy(s);
    return result == SUCCESS ? SUCCESS : FAIL;
}

int main(void) {
    int res = test_stack_push_pop();
    if (res == SUCCESS) {
        printf("[stack_push_pop] SUCCESS\n");
        return 0;
    } else {
        printf("[stack_push_pop] FAIL\n");
        return 1;
    }
}