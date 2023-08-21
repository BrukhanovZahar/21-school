#ifndef TOKEN_H
#define TOKEN_H
// Определение типов лексем
typedef enum {
    TOKEN_NUMBER,      // числовые значения
    TOKEN_OPERATOR,    // математические операторы
    TOKEN_FUNCTION,    // математические функции
    TOKEN_VARIABLE,    // переменные
    TOKEN_LEFT_PAREN,  // открывающаяся скобка
    TOKEN_RIGHT_PAREN  // закрывающаяся скобка
} TokenType;

// Определение структуры для лексем
typedef struct {
    TokenType type;  // тип лексемы
    char value[50];  // значение лексемы
} Token;
#endif
