#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-8

int sle(double **matrix, int n, int m, double *roots);

int input(double **matrix, int *n, int *m);

void output(double **matrix, int n, int m);

void output_roots(double *roots, int n);

int main() {
    double **matrix;
    int n, m;
    int count = scanf("%d%d", &n, &m);
    if (count != 2 || n < 1 || m < 1) {
        printf("n/a");
        return 0;
    }
    matrix = malloc(n * m * sizeof(double *) + m * sizeof(double *));
    double *p = (double *)(matrix + n);
    for (int i = 0; i < n; ++i) {
        matrix[i] = p + m * i;
    }
    count = input(matrix, &n, &m);
    if (count == 0) {
        free(matrix);
        return 0;
    }
    double *roots = (double *)malloc(n * sizeof(double));
    count = sle(matrix, n, m, roots);
    if (count == 0) {
        free(matrix);
        free(roots);
        printf("n/a");
        return 0;
    }
    output_roots(roots, n);
    free(matrix);
    free(roots);
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

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            printf("%.6lf ", matrix[i][j]);
        }
        printf("%.6lf\n", matrix[i][m - 1]);
    }
    for (int j = 0; j < m - 1; j++) {
        printf("%.6lf ", matrix[n - 1][j]);
    }
    printf("%.6lf", matrix[n - 1][m - 1]);
}

void output_roots(double *roots, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (fabs(roots[i]) < EPSILON) {
            roots[i] = fabs(roots[i]);
        }
        printf("%.6lf ", roots[i]);
    }
    if (fabs(roots[n - 1]) < EPSILON) {
        roots[n - 1] = fabs(roots[n - 1]);
    }
    printf("%.6lf", roots[n - 1]);
}

// Решение СЛАУ методом Гаусса
int sle(double **matrix, int n, int m, double *roots) {
    for (int i = 0; i < n; i++) {
        // Приведение матрицы к верхнему треугольному виду
        if (fabs(matrix[i][i]) < EPSILON) {
            return 0;  // Матрица вырождена, нет решения
        }
        for (int k = i + 1; k < n; k++) {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < m; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    // Обратный ход, нахождение корней
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += matrix[i][j] * roots[j];
        }
        roots[i] = (matrix[i][m - 1] - sum) / matrix[i][i];
    }

    return 1;
}