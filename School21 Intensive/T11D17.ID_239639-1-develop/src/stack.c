#include "stack.h"

#include <stdlib.h>

Stack* init() {
    Stack* s = malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = NULL;
    }
    return s;
}

int push(Stack* s, int value) {
    int result = FAIL;
    if (s != NULL) {
        StackNode* node = malloc(sizeof(StackNode));
        if (node != NULL) {
            node->data = value;
            node->next = s->top;
            s->top = node;
            result = SUCCESS;
        }
    }
    return result;
}

int pop(Stack* s, int* value) {
    int result = FAIL;
    if (s != NULL && value != NULL && s->top != NULL) {
        StackNode* tmp = s->top;
        *value = tmp->data;
        s->top = tmp->next;
        free(tmp);
        result = SUCCESS;
    }
    return result;
}

void destroy(Stack* s) {
    if (s != NULL) {
        while (s->top != NULL) {
            StackNode* tmp = s->top;
            s->top = tmp->next;
            free(tmp);
        }
        free(s);
    }
}