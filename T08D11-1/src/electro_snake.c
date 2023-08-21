#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix);

void sort_horizontal(int **matrix, int n, int m, int **result_matrix);

int input(int **matrix, int *n, int *m);

void output(int **matrix, int n, int m);

int main() {
    int **matrix, **result;
    int n, m, flag = 1;
    int count = scanf("%d%d", &n, &m);
    if (count != 2 || n < 1 || m < 1) {
        printf("n/a");
        flag = 0;
    }
    if (flag != 0) {
        matrix = malloc(n * m * sizeof(int *) + m * sizeof(int *));
        int *p = (int *)(matrix + n);
        for (int i = 0; i < n; ++i) {
            matrix[i] = p + m * i;
        }
        count = input(matrix, &n, &m);
        if (count == 0) {
            free(matrix);
            flag = 0;
        }
        if (flag != 0) {
            result = malloc(n * m * sizeof(int *) + m * sizeof(int *));
            p = (int *)(result + n);
            for (int i = 0; i < n; ++i) {
                result[i] = p + m * i;
            }
            sort_vertical(matrix, n, m, result);
            output(result, n, m);
            printf("\n");
            printf("\n");
            sort_horizontal(matrix, n, m, result);
            output(result, n, m);
            free(matrix);
            free(result);
        }
    }
    return 0;
}

int input(int **matrix, int *n, int *m) {
    int count;
    for (int i = 0; i < *n; ++i) {
        for (int j = 0; j < *m - 1; j++) {
            count = scanf("%d", &matrix[i][j]);
            if (count != 1) {
                printf("n/a");
                return 0;
            }
        }
        count = scanf("%d", &matrix[i][*m - 1]);
        if (count != 1) {
            printf("n/a");
            return 0;
        }
    }
    return 1;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("%d\n", matrix[i][m - 1]);
    }
    for (int j = 0; j < m - 1; j++) {
        printf("%d ", matrix[n - 1][j]);
    }
    printf("%d", matrix[n - 1][m - 1]);
}

// Функция сравнения элементов при сортировке
int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int *temp_array = (int *)malloc(n * m * sizeof(int));

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp_array[k++] = matrix[i][j];
        }
    }

    // Сортируем массив
    qsort(temp_array, n * m, sizeof(int), compare);

    // Заполняем результирующую матрицу отсортированными значениями из временного массива
    k = 0;
    for (int j = 0; j < m; j++) {
        if (j % 2 == 0) {
            for (int i = 0; i < n; i++) {
                result_matrix[i][j] = temp_array[k++];
            }
        } else {
            for (int i = n - 1; i >= 0; i--) {
                result_matrix[i][j] = temp_array[k++];
            }
        }
    }

    free(temp_array);
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int *temp_array = (int *)malloc(n * m * sizeof(int));

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp_array[k++] = matrix[i][j];
        }
    }

    // Сортируем массив
    qsort(temp_array, n * m, sizeof(int), compare);

    // Заполняем результирующую матрицу отсортированными значениями из временного массива
    k = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                result_matrix[i][j] = temp_array[k++];
            }
        } else {
            for (int j = m - 1; j >= 0; j--) {
                result_matrix[i][j] = temp_array[k++];
            }
        }
    }

    free(temp_array);
}