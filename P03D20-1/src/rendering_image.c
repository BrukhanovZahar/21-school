#include "rendering_image.h"

// заполняем матрицу символами точка
void fill_graph(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = void_sym;
        }
    }
}

// Функция создает создает графическое представление функции
void create_graphic(int matrix[HEIGHT][WIDTH], const Token *postfix_tokens, int num_postfix_tokens) {
    for (int i = 0; i < WIDTH; i++) {  // проходим по каждому столбцу
        double x = (i * 4.0 * M_PI) / (WIDTH - 1);  // вычисляем x, учитывая область определения [0; 4Pi]
        double res =
            evaluate_postfix_function(postfix_tokens, num_postfix_tokens, x);  // вычисляем результат функции
        int y = round((res + 1) * (HEIGHT - 1) / 2);  // вычисляем y для данного x
        if (y >= 0 && y < HEIGHT) {                   // если не вышли за границы поля
            matrix[y][i] = sym;  // заполняем ячейку символос умножения
        }
    }
}

// Функция для вывода матрицы в терминал
void print_graph(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(matrix[i][j]);
        }
        putchar('\n');
    }
}