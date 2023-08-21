#include "infix_to_postfix.h"

// Функция для определения приоритета оператора
int precedence(const char *operator) {
    int priority = 0;
    if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0) {
        priority = 1;  // Приоритет операторов + и -
    } else if (strcmp(operator, "*") == 0 || strcmp(operator, "/") == 0) {
        priority = 2;  // Приоритет операторов * и /
    } else if (strcmp(operator, "sin") == 0 || strcmp(operator, "cos") == 0 || strcmp(operator, "tan") == 0 ||
               strcmp(operator, "ctg") == 0 || strcmp(operator, "sqrt") == 0 || strcmp(operator, "ln") == 0) {
        priority = 2;  // Приоритет функций
    }
    return priority;  // В остальных случаях
}

void number_or_variable(Token **postfix_tokens, int *num_postfix_tokens, const Token *current_token) {
    (*num_postfix_tokens)++;  // увеличиваем количество лексем
    *postfix_tokens = (Token *)realloc(
        *postfix_tokens, sizeof(Token) * (*num_postfix_tokens));  // выделяем память под новую лексему
    (*postfix_tokens)[(*num_postfix_tokens) - 1] =
        *current_token;  // копирование значения текущей лексемы в массив postfix_tokens
}

void unary_minus_2(const Token *infix_tokens, Token **postfix_tokens, int *num_postfix_tokens, int *i) {
    const Token *next_token = &infix_tokens[*i + 1];  // указатель на следующий за унарным минусом элемент
    if (next_token->type == TOKEN_LEFT_PAREN &&
        infix_tokens[*i + 2].value[0] == '#') {  // если за унарным минусом стоит (  и после нее
        // унарный минус, мы их игнорируем
        *i = *i + 2;
    } else if (next_token->type == TOKEN_LEFT_PAREN &&
               (infix_tokens[*i + 2].type == TOKEN_NUMBER ||
                infix_tokens[*i + 2].type ==
                    TOKEN_VARIABLE)) {  // если за унарным минусом стоит скобка и за ней
        // положительное число
        char new_value[50];
        new_value[0] = '-';
        for (int j = 1; infix_tokens[*i + 2].value[j - 1] != '\0'; j++) {
            new_value[j] = infix_tokens[*i + 2].value[j - 1];
            if (infix_tokens[*i + 2].value[j - 1] == '\0') {
                new_value[j + 1] = '\0';
            }
        }
        // snprintf(new_value, sizeof(new_value), "-%s",
        //          infix_tokens[*i + 2].value);  // копируем старое значение добавляя перед ним знак минус
        (*num_postfix_tokens)++;  // увеличиваем количество лексем
        *postfix_tokens =
            (Token *)realloc(*postfix_tokens,
                             sizeof(Token) * (*num_postfix_tokens));  // выделяем память под новую лексему
        (*postfix_tokens)[(*num_postfix_tokens) - 1].type =
            infix_tokens[*i + 2].type;  // устанавливаем тип лексемы соответствующий типу следующей лексемы
        strcpy((*postfix_tokens)[(*num_postfix_tokens) - 1].value,
               new_value);  // копируем новое значения в поле value последней лексемы в массиве
        // postfix_tokens
        *i = *i + 2;  // пропускаем следующий токен, так как он уже добавлен
    } else if (next_token->value[0] == '#') {
        *i = *i + 1;
    }
    if (next_token->type == TOKEN_NUMBER ||
        next_token->type == TOKEN_VARIABLE) {  // если это число или переменная
        char new_value[50];
        new_value[0] = '-';
        for (int j = 1; next_token->value[j - 1] != '\0'; j++) {
            new_value[j] = next_token->value[j - 1];
            if (next_token->value[j - 1] == '\0') {
                new_value[j + 1] = '\0';
            }
        }
        // snprintf(new_value, sizeof(new_value), "-%s",
        //          next_token->value);  // копируем старое значение добавляя перед ним знак минус
        (*num_postfix_tokens)++;  // увеличиваем количество лексем
        *postfix_tokens =
            (Token *)realloc(*postfix_tokens,
                             sizeof(Token) * (*num_postfix_tokens));  // выделяем память под новую лексему
        (*postfix_tokens)[(*num_postfix_tokens) - 1].type =
            next_token->type;  // устанавливаем тип лексемы соответствующий типу следующей лексемы
        strcpy((*postfix_tokens)[(*num_postfix_tokens) - 1].value,
               new_value);  // копируем новое значения в поле value последней лексемы в массиве
        // postfix_tokens
        *i = *i + 1;  // пропускаем следующий токен, так как он уже добавлен
    }
}

void non_unary_minus(Stack *operator_stack, Token **postfix_tokens, int *num_postfix_tokens,
                     const Token *current_token) {
    // Обработка операторов, пока стек не пустой и пока приоритет верхнего оператора в стеке
    // больше или равен приоритету текущего оператора (current_token->value) и пока верхний
    // оператор в стеке не является открывающей скобкой.
    while (!stack_empty(operator_stack) &&
           precedence(stack_top(operator_stack)) >= precedence(current_token->value) &&
           strcmp(stack_top(operator_stack), "(") != 0) {
        char *operator= stack_pop(operator_stack);  // переносим операторы из стека в выходную очередь
        (*num_postfix_tokens)++;  // увеличиваем количество лексем
        *postfix_tokens =
            (Token *)realloc(*postfix_tokens,
                             sizeof(Token) * (*num_postfix_tokens));  // выделяем память под новую лексему
        (*postfix_tokens)[(*num_postfix_tokens) - 1].type = TOKEN_OPERATOR;  // устанавливаем тип оператор
        strcpy((*postfix_tokens)[(*num_postfix_tokens) - 1].value,
               operator);  // копируем значение оператора
        free(operator);
    }
    // Добавляем текущий оператор в стек
    stack_push(operator_stack, current_token->value);
}

void right_bracket(Stack *operator_stack, Token **postfix_tokens, int *num_postfix_tokens) {
    // Если это правая скобка, выталкиваем операторы из стека в выходную очередь до левой скобки
    while (!stack_empty(operator_stack) &&
           strcmp(stack_top(operator_stack), "(") !=
               0) {  // пока в стек не пустой и пока верхний оператор не является (
        char *operator= stack_pop(operator_stack);  // извлекаем оператор из вершины стека операторов
        (*num_postfix_tokens)++;  // увеличиваем количество лексем
        *postfix_tokens = (Token *)realloc(
            *postfix_tokens, sizeof(Token) * (*num_postfix_tokens));  // выделяем память под новую лексему
        (*postfix_tokens)[(*num_postfix_tokens) - 1].type = TOKEN_OPERATOR;  // устанавливаем тип оператор
        strcpy((*postfix_tokens)[(*num_postfix_tokens) - 1].value, operator);  // копируем значение оператора
        free(operator);
    }
    // Удаляем левую скобку из стека
    char *operator= stack_pop(operator_stack);
    free(operator);
    if (!stack_empty(operator_stack) &&
        stack_top(operator_stack)[0] !=
            '(') {  // если в стеке операторов не пусто и верхний элемент не открывающаяся скобка
        // если следуйщий элемент в стеке функция, добавляем ее в выходную очередь
        if (strcmp(stack_top(operator_stack), "sin") == 0 || strcmp(stack_top(operator_stack), "cos") == 0 ||
            strcmp(stack_top(operator_stack), "tan") == 0 || strcmp(stack_top(operator_stack), "ctg") == 0 ||
            strcmp(stack_top(operator_stack), "sqrt") == 0 || strcmp(stack_top(operator_stack), "ln") == 0) {
            char *function = stack_pop(operator_stack);  // извлекаем функцию из вершины стека операторов
            (*num_postfix_tokens)++;  // увеличиваем количество лексем
            *postfix_tokens = (Token *)realloc(
                *postfix_tokens, sizeof(Token) * (*num_postfix_tokens));  // выделяем память под новую лексему
            (*postfix_tokens)[(*num_postfix_tokens) - 1].type = TOKEN_FUNCTION;  // устанавливаем тип функция
            strcpy((*postfix_tokens)[(*num_postfix_tokens) - 1].value,
                   function);  // копируем значение функции
            free(function);
        }
    }
}

// Функция для преобразования инфиксной нотации в польскую нотацию
void infix_to_postfix(const Token *infix_tokens, int num_infix_tokens, Token **postfix_tokens,
                      int *num_postfix_tokens) {
    *num_postfix_tokens = 0;  // переменная для хранения количества лексем
    *postfix_tokens = NULL;  // переменная для хранения операторов и открывающихся скобок
    Stack operator_stack;
    stack_init(&operator_stack, num_infix_tokens);
    // Проходим по каждой лексеме выражения в инфиксной записи
    for (int i = 0; i < num_infix_tokens; i++) {
        const Token *current_token = &infix_tokens[i];
        if (current_token->type == TOKEN_NUMBER ||
            current_token->type == TOKEN_VARIABLE) {  // если число или переменная
            number_or_variable(postfix_tokens, num_postfix_tokens, current_token);
        } else if (current_token->type == TOKEN_OPERATOR) {  // если оператор
            if (current_token->value[0] == '#') {            // если унарный минус
                unary_minus_2(infix_tokens, postfix_tokens, num_postfix_tokens, &i);
            } else {  // если не унарный минус
                non_unary_minus(&operator_stack, postfix_tokens, num_postfix_tokens, current_token);
            }
        } else if (current_token->type == TOKEN_FUNCTION) {
            // Если это функция, добавляем в стек
            stack_push(&operator_stack, current_token->value);
        } else if (current_token->type == TOKEN_LEFT_PAREN) {
            // Если это левая скобка, добавляем в стек
            stack_push(&operator_stack, current_token->value);
        } else if (current_token->type == TOKEN_RIGHT_PAREN) {
            right_bracket(&operator_stack, postfix_tokens, num_postfix_tokens);
        }
    }
    // Выталкиваем оставшиеся операторы из стека в выходную очередь
    while (!stack_empty(&operator_stack)) {          // пока стек не пустой
        char *operator= stack_pop(&operator_stack);  // извлекаем верхний элемент
        (*num_postfix_tokens)++;  // увеличиваем количество лексем
        *postfix_tokens = (Token *)realloc(
            *postfix_tokens, sizeof(Token) * (*num_postfix_tokens));  // выделяем память под новую лексему
        (*postfix_tokens)[(*num_postfix_tokens) - 1].type = TOKEN_OPERATOR;  // устанавливаем тип оператор
        strcpy((*postfix_tokens)[(*num_postfix_tokens) - 1].value, operator);  // копируем значение оператора
        free(operator);
    }
    // Очищаем память, занимаемую стеком
    stack_free(&operator_stack);
}