#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "token.h"

int precedence(const char *operator);
void number_or_variable(Token **postfix_tokens, int *num_postfix_tokens, const Token *current_token);
void unary_minus_2(const Token *infix_tokens, Token **postfix_tokens, int *num_postfix_tokens, int *i);
void non_unary_minus(Stack *operator_stack, Token **postfix_tokens, int *num_postfix_tokens,
                     const Token *current_token);
void right_bracket(Stack *operator_stack, Token **postfix_tokens, int *num_postfix_tokens);
void infix_to_postfix(const Token *infix_tokens, int num_infix_tokens, Token **postfix_tokens,
                      int *num_postfix_tokens);

#endif
