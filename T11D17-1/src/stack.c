#include "stack.h"

struct stack *init() {
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->top = NULL;
    return s;
}

void push(struct stack *s, int data) {
    struct stack_node *new_node = (struct stack_node *)malloc(sizeof(struct stack_node));
    new_node->data = data;
    new_node->next = s->top;
    s->top = new_node;
}

int pop(struct stack *s) {
    int res = INT16_MIN;
    if (s->top == NULL) {
        printf("n/a");
    } else {
        struct stack_node *tmp = s->top;
        res = tmp->data;
        s->top = tmp->next;
        free(tmp);
    }
    return res;
}

void destroy(struct stack *s) {
    while (s->top != NULL) {
        struct stack_node *tmp = s->top;
        s->top = tmp->next;
        free(tmp);
    }
    free(s);
}
