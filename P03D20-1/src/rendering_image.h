#ifndef RENDERING_IMAGE_H
#define RENDERING_IMAGE_H
#include "evaluate_postfix.h"
#include "token.h"
#define HEIGHT 25
#define WIDTH 80
#define sym '*'
#define void_sym '.'

void fill_graph(int matrix[HEIGHT][WIDTH]);
void create_graphic(int matrix[HEIGHT][WIDTH], const Token *postfix_tokens, int num_postfix_tokens);
void print_graph(int matrix[HEIGHT][WIDTH]);

#endif