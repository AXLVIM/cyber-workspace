#ifndef STACK_H
#define STACK_H

#define SUCCESS 0
#define FAIL 1

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

Stack* init();
int push(Stack* s, int value);
int pop(Stack* s, int* value);
void destroy(Stack* s);

#endif  // STACK_H