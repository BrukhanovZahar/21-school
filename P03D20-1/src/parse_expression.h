#ifndef PARSE_EXPRESSION_H
#define PARSE_EXPRESSION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "token.h"

int is_operator(char c);
int my_isdigit(char c);
int my_isalpha(char c);
void processing_numbers(const char *expression, Token **tokens, int *num_tokens, int *i);
void unary_minus(Token **tokens, int *num_tokens, int *i);
void processing_operators(const char *expression, Token **tokens, int *num_tokens, int *i);
void processing_the_left_bracket(Token **tokens, int *num_tokens, int *i);
void processing_the_right_bracket(Token **tokens, int *num_tokens, int *i);
void processing_functions_or_variables(const char *expression, Token **tokens, int *num_tokens, int *i);
void parse_expression(const char *expression, Token **tokens, int *num_tokens);

#endif
