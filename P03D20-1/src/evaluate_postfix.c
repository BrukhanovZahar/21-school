#include "evaluate_postfix.h"

// Функция преобразует double в строку
char *ftos(double num) {
    char *str = (char *)malloc(20);  // выделяем память под строку
    snprintf(str, 20, "%lf", num);   // записываем число в строку
    return str;                      // возвращаем указатель на строку
}

void function_variable(const Token *current_token, Stack *operand_stack, double x) {
    if (current_token->value[0] == '-') {  // если переменная отрицательная, помещаем отрицательное значение
        char *ccc = ftos(-x);
        stack_push(operand_stack, ccc);
        free(ccc);
    } else {  // если переменная не отрицательная, помещаем исходное значение
        char *ccc = ftos(x);
        stack_push(operand_stack, ccc);
        free(ccc);
    }
}

void function_operator(const Token *current_token, Stack *operand_stack) {
    double operand2 = atof(stack_top(operand_stack));
    char *o1 = stack_pop(operand_stack);
    free(o1);
    double operand1 = atof(stack_top(operand_stack));
    char *o2 = stack_pop(operand_stack);
    free(o2);
    // Выполняем определенную операцию и помещаем результат в operand_stack
    if (strcmp(current_token->value, "+") == 0) {
        char *ccc = ftos(operand1 + operand2);
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "-") == 0) {
        char *ccc = ftos(operand1 - operand2);
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "*") == 0) {
        char *ccc = ftos(operand1 * operand2);
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "/") == 0) {
        char *ccc = ftos(operand1 / operand2);
        stack_push(operand_stack, ccc);
        free(ccc);
    }
}

void function_function(const Token *current_token, Stack *operand_stack) {
    double operand = atof(stack_top(operand_stack));
    char *c = stack_pop(operand_stack);
    free(c);
    // Выполняем определенную операцию и помещаем результат в operand_stack
    if (strcmp(current_token->value, "sin") == 0) {
        char *ccc = ftos(sin(operand));
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "cos") == 0) {
        char *ccc = ftos(cos(operand));
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "tan") == 0) {
        char *ccc = ftos(tan(operand));
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "ctg") == 0) {
        char *ccc = ftos(1.0 / tan(operand));
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "sqrt") == 0) {
        char *ccc = ftos(sqrt(operand));
        stack_push(operand_stack, ccc);
        free(ccc);
    } else if (strcmp(current_token->value, "ln") == 0) {
        char *ccc = ftos(log(operand));
        stack_push(operand_stack, ccc);
        free(ccc);
    }
}

// Функция для вычисления значения выражения по обратной польской записи
double evaluate_postfix(const Token *postfix_tokens, int num_postfix_tokens, double x) {
    Stack operand_stack;  // стек для хранения операндов и результатов вычислений
    stack_init(&operand_stack, num_postfix_tokens);
    // Проходимся по каждому токену в массиве
    for (int i = 0; i < num_postfix_tokens; i++) {
        const Token *current_token = &postfix_tokens[i];
        if (current_token->type == TOKEN_NUMBER) {
            // Если токен это число, помещаем в стек операндов
            stack_push(&operand_stack, current_token->value);
        } else if (current_token->type == TOKEN_VARIABLE) {
            // Если токен это переменная, помещаем в стек значение переменной x
            function_variable(current_token, &operand_stack, x);
        } else if (current_token->type == TOKEN_OPERATOR) {
            // Если токен это оператор, извлекаем два операнда из стека и выполняем операцию
            function_operator(current_token, &operand_stack);
        } else if (current_token->type == TOKEN_FUNCTION) {
            // Если токен это функция, извлекаем операнд из стека и вычисляем функцию
            function_function(current_token, &operand_stack);
        }
    }
    // Получаем конечный результат из стека
    double result = atof(stack_top(&operand_stack));
    char *c = stack_pop(&operand_stack);
    free(c);
    // Очищаем память, занимаемую стеком
    stack_free(&operand_stack);
    return result;
}

// Обертка функции evaluate_postfix
double evaluate_postfix_function(const Token *postfix_tokens, int num_postfix_tokens, double x) {
    return evaluate_postfix(postfix_tokens, num_postfix_tokens, x);
}