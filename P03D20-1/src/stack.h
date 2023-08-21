#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <string.h>

// Определение структуры для стека
typedef struct {
    char **data;  // указатель на строку, которая хранит элемент стека
    int size;     // максимальная емкость стека
    int top;      // индекс последнего элемента в стеке
} Stack;

void stack_init(Stack *stack, int size);
int stack_empty(const Stack *stack);
void stack_push(Stack *stack, const char *value);
char *stack_pop(Stack *stack);
char *stack_top(const Stack *stack);
void stack_free(Stack *stack);

#endif
