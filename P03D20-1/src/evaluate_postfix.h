#ifndef EVALUATE_POSTFIX_H
#define EVALUATE_POSTFIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "token.h"

char *ftos(double num);
void function_variable(const Token *current_token, Stack *operand_stack, double x);
void function_operator(const Token *current_token, Stack *operand_stack);
void function_function(const Token *current_token, Stack *operand_stack);
double evaluate_postfix(const Token *postfix_tokens, int num_postfix_tokens, double x);
double evaluate_postfix_function(const Token *postfix_tokens, int num_postfix_tokens, double x);

#endif
