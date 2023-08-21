#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m);

int input(double **matrix, int *n, int *m);

void output(double det);

int main() {
    double **matrix;
    int n, m, flag = 1;
    int count = scanf("%d%d", &n, &m);
    if (count != 2 || n < 1 || m < 1 || n != m) {
        printf("n/a");
        flag = 0;
    }
    if (flag != 0) {
        matrix = malloc(n * m * sizeof(double *) + m * sizeof(double *));
        double *p = (double *)(matrix + n);
        for (int i = 0; i < n; ++i) {
            matrix[i] = p + m * i;
        }
        count = input(matrix, &n, &m);
        if (count == 0) {
            free(matrix);
            flag = 0;
        }
        if (flag != 0) {
            output(det(matrix, n, m));
            free(matrix);
        }
    }
    return 0;
}

int input(double **matrix, int *n, int *m) {
    int count;
    for (int i = 0; i < *n; ++i) {
        for (int j = 0; j < *m - 1; j++) {
            count = scanf("%lf", &matrix[i][j]);
            if (count != 1) {
                printf("n/a");
                return 0;
            }
        }
        count = scanf("%lf", &matrix[i][*m - 1]);
        if (count != 1) {
            printf("n/a");
            return 0;
        }
    }
    return 1;
}

void output(double det) { printf("%.6lf", det); }

double det(double **matrix, int n, int m) {
    // Базовый случай: для матрицы 1x1 определитель равен единственному элементу
    if (n == 1) {
        return matrix[0][0];
    }
    double determinant = 0.0;
    double **submatrix;  // Подматрица, полученная после удаления первой строки и j-го столбца
    for (int j = 0; j < n; j++) {
        submatrix = malloc((n - 1) * (m - 1) * sizeof(double *) + (m - 1) * sizeof(double *));
        double *p = (double *)(submatrix + (n - 1));
        for (int i = 0; i < n - 1; ++i) {
            submatrix[i] = p + (m - 1) * i;
        }
        // Заполняем подматрицу значениями, исключая первую строку и j-ый столбец
        int sub_i = 0;
        for (int i = 1; i < n; i++) {
            int sub_j = 0;
            for (int k = 0; k < n; k++) {
                if (k != j) {
                    submatrix[sub_i][sub_j] = matrix[i][k];
                    sub_j++;
                }
            }
            sub_i++;
        }

        // Вычисляем дополнение и добавляем его к определителю
        determinant += matrix[0][j] * ((j % 2 == 0) ? 1 : -1) * det(submatrix, n - 1, m - 1);
        free(submatrix);
    }

    return determinant;
}