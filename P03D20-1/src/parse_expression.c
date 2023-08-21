#include "parse_expression.h"

// Функция для проверки, является ли символ оператором
int is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

// Функция для проверки, является ли символ числом
int my_isdigit(char c) { return (c >= '0' && c <= '9'); }

// Функция для проверки, является ли символ буквой
int my_isalpha(char c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }

void processing_numbers(const char *expression, Token **tokens, int *num_tokens, int *i) {
    int j = 0;
    // Идем по символам, добавляя их в массив num, пока это цифры или точка (для чисел с плавающей
    // точкой)
    char num[50] = {'\0'};
    while (my_isdigit(expression[*i]) || expression[*i] == '.') {
        num[j++] = expression[*i];
        *i = *i + 1;
    }
    (*num_tokens)++;  // увеличиваем количество лексем
    *tokens = (Token *)realloc(*tokens,
                               sizeof(Token) * (*num_tokens));  // выделяем память под новую лексему
    (*tokens)[(*num_tokens) - 1].type = TOKEN_NUMBER;  // устанавливаем тип число
    strcpy((*tokens)[(*num_tokens) - 1].value,
           num);  // копируем значение из num в поле value структуры Token
}

void unary_minus(Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;  // увеличиваем количество лексем
    *tokens = (Token *)realloc(*tokens,
                               sizeof(Token) * (*num_tokens));  // выделяем память под новую лексему
    (*tokens)[(*num_tokens) - 1].type = TOKEN_OPERATOR;  // устанавливаем тип оператор
    (*tokens)[(*num_tokens) - 1].value[0] = '#';  // записываем в Token унарный минус символом #
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';  // устанавливаем конец строки за оператором
    *i = *i + 1;  // переходим к следующему символу
}

void processing_operators(const char *expression, Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;  // увеличиваем количество лексем
    *tokens = (Token *)realloc(*tokens,
                               sizeof(Token) * (*num_tokens));  // выделяем память под новую лексему
    (*tokens)[(*num_tokens) - 1].type = TOKEN_OPERATOR;  // устанавливаем тип оператор
    (*tokens)[(*num_tokens) - 1].value[0] = expression[*i];  // в Token записываем оператор
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';  // устанавливаем конец строки за оператором
    *i = *i + 1;  // переходим к следующему символу
}

void processing_the_left_bracket(Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;  // увеличиваем количество лексем
    *tokens = (Token *)realloc(*tokens,
                               sizeof(Token) * (*num_tokens));  // выделяем память под новую лексему
    (*tokens)[(*num_tokens) - 1].type = TOKEN_LEFT_PAREN;  // устанавливаем тип открывающаяся скобка
    (*tokens)[(*num_tokens) - 1].value[0] = '(';  // в Token записываем (
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';  // устанавливаем конец строки за оператором
    *i = *i + 1;  // переходим к следующему символу
}

void processing_the_right_bracket(Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;  // увеличиваем количество лексем
    *tokens = (Token *)realloc(*tokens,
                               sizeof(Token) * (*num_tokens));  // выделяем память под новую лексему
    (*tokens)[(*num_tokens) - 1].type = TOKEN_RIGHT_PAREN;  // устанавливаем тип закрывающаяся скобка
    (*tokens)[(*num_tokens) - 1].value[0] = ')';  // в Token записываем )
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';  // устанавливаем конец строки за оператором
    *i = *i + 1;  // переходим к следующему символу
}

void processing_functions_or_variables(const char *expression, Token **tokens, int *num_tokens, int *i) {
    int j = 0;
    // Идем по символам, добавляя их в массив identifier, пока это буквы
    char identifier[50] = {'\0'};
    while (my_isalpha(expression[*i])) {
        identifier[j++] = expression[*i];
        *i = *i + 1;
    }
    (*num_tokens)++;  // увеличиваем количество лексем
    *tokens = (Token *)realloc(*tokens,
                               sizeof(Token) * (*num_tokens));  // выделяем память под новую лексему
    if (strcmp(identifier, "sin") == 0 || strcmp(identifier, "cos") == 0 || strcmp(identifier, "tan") == 0 ||
        strcmp(identifier, "ctg") == 0 || strcmp(identifier, "sqrt") == 0 || strcmp(identifier, "ln") == 0) {
        (*tokens)[(*num_tokens) - 1].type = TOKEN_FUNCTION;  // устанавливаем тип функция
    } else {
        (*tokens)[(*num_tokens) - 1].type = TOKEN_VARIABLE;  // устанавливаем тип переменная
    }
    strcpy((*tokens)[(*num_tokens) - 1].value,
           identifier);  // копируем значение из identifier в поле value структуры Token
}

// Функция для разбора выражения и получения списка лексем
void parse_expression(const char *expression, Token **tokens, int *num_tokens) {
    *num_tokens = 0;  // переменная для хранения количества лексем
    *tokens = NULL;   // переменная для хранения массива лексем
    int i = 0;
    while (expression[i] !=
           '\0') {  // перебираем каждый символ в строке expression, пока не достигнем конца строки
        if (expression[i] == ' ') {  // если текущий символ пробел, переходим к следующей итерации цикла
            i++;
            continue;
        }
        if (my_isdigit(expression[i])) {  // если текущий символ цифра
            // Обработка чисел
            processing_numbers(expression, tokens, num_tokens, &i);
        } else if (expression[i] == '-' && expression[i - 1] != ')' &&
                   (i == 0 || expression[i - 1] !=
                                  my_isdigit(expression[i - 1]))) {  // если знак минус и предыдущий элемент,
            // либо начало строки, либо не цифру
            // Унарный минус
            unary_minus(tokens, num_tokens, &i);
        } else if (is_operator(expression[i])) {  // если текущий символ оператор
            // Обработка операторов
            processing_operators(expression, tokens, num_tokens, &i);
        } else if (expression[i] == '(') {
            // Обработка левой скобки
            processing_the_left_bracket(tokens, num_tokens, &i);
        } else if (expression[i] == ')') {
            // Обработка правой скобки
            processing_the_right_bracket(tokens, num_tokens, &i);
        } else if (my_isalpha(expression[i])) {
            // Обработка функций или переменных
            processing_functions_or_variables(expression, tokens, num_tokens, &i);
        } else {
            // Некорректный символ, пропускаем
            i++;
        }
    }
}