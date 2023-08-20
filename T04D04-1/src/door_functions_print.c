#include <math.h>
#include <stdio.h>

double ver_agn(double x) { return 1 / (1 + x * x); }

double lem_ber(double x) { return sqrt(sqrt(1 + 4 * x * x) - x * x - 1); }

double qua_hyp(double x) { return 1 / (x * x); }

int main() {
    const int num_values = 42;
    const int num_rows = 21;
    const double pi = M_PI;
    double start = -pi;
    double end = pi;
    double step = (end - start) / (num_values - 1);
    double max_y = 1.0;  // Максимальное значение функции для масштабирования

    // Отрисовка функции Верзьера Аньези
    for (int i = 0; i < num_rows; i++) {
        double y = max_y * (num_rows - 1 - i) / (num_rows - 1);  // Ордината для текущей строки
        for (int j = 0; j < num_values; j++) {
            double value = start + j * step;
            double va = ver_agn(value);
            // Отрисовываем символ '*'
            if (va >= y)
                putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }

    putchar('\n');

    // Отрисовка функции Лемниската Бернулли
    for (int i = 0; i < num_rows; i++) {
        double y = max_y * (num_rows - 1 - i) / (num_rows - 1);  // Ордината для текущей строки
        for (int j = 0; j < num_values; j++) {
            double value = start + j * step;
            double lb = lem_ber(value);
            // Отрисовываем символ '*'
            if (lb >= y)
                putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }

    putchar('\n');

    // Отрисовка функции квадратичной гиперболы
    for (int i = 0; i < num_rows; i++) {
        double y = max_y * (num_rows - 1 - i) / (num_rows - 1);  // Ордината для текущей строки
        for (int j = 0; j < num_values; j++) {
            double value = start + j * step;
            double qh = qua_hyp(value);
            // Отрисовываем символ '*'
            if (qh >= y)
                putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }

    return 0;
}
