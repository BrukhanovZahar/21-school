#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
struct stack_node {
    int data;
    struct stack_node *next;
};

struct stack {
    struct stack_node *top;
};

struct stack *init();

void push(struct stack *s, int data);

int pop(struct stack *s);

void destroy(struct stack *s);

#endif
