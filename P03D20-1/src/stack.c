#include "stack.h"

// Инициализация стека
void stack_init(Stack *stack, int size) {
    stack->data = (char **)malloc(sizeof(char *) * size);  // выделяем память для массива указателей на строки
    stack->size = size;  // устанавливаем размер стека
    stack->top = -1;  // устанавливаем начальное значение указателя вершины стека
}

// Проверка, пуст ли стек
int stack_empty(const Stack *stack) { return stack->top == -1; }  // если top == -1, то стек пустой

// Помещение элемента в стек
void stack_push(Stack *stack, const char *value) {
    if (stack->top < stack->size - 1) {  // есть ли еще место в стеке для добавления нового элемента
        stack->top++;  // если место в стеке есть, то увеличиваем переменную top, чтобы указать на следующую
        // свободную ячейку стека
        stack->data[stack->top] =
            (char *)malloc(sizeof(char) * (strlen(value) + 1));  // выделяем память для строки в стеке
        strcpy(stack->data[stack->top], value);  // копируем содержимое строки value в стек
    }
}

// Извлечение элемента из стека
char *stack_pop(Stack *stack) {
    char *value = NULL;
    if (!stack_empty(stack)) {  // если стек не пустой извлекаем значение из вершины стека
        value = stack->data[stack->top];
        stack->top--;
    }
    return value;
}

// Функция для получения верхнего элемента стека
char *stack_top(const Stack *stack) {
    char *value = NULL;
    if (!stack_empty(stack)) {  // если стек не пустой получаем значение из вершины стека
        value = stack->data[stack->top];
    }
    return value;
}

// Освобождение памяти, занятой стеком
void stack_free(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {  // идем по всем элементам с индексами от 0 до stack->top
        free(stack->data[i]);  // освобождаем память выделенную для каждой из строк
    }
    free(stack->data);  // освобождаем память выделенную для массива указателей на строки
}