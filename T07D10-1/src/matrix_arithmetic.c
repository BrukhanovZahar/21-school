#include <stdio.h>
#include <stdlib.h>

int input(int **matrix, int *n, int *m);

void output(int **matrix, int n, int m);

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);

int transpose(int **matrix, int n, int m);

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);

int main() {
    int n1, n2, m1, m2, mode, **arr1, **arr2;
    int count = scanf("%d", &mode);
    if (count != 1 || mode < 1 || mode > 3) {
        printf("n/a");
        return 0;
    }
    count = scanf("%d%d", &n1, &m1);
    if (count != 2 || n1 < 1 || m1 < 1) {
        printf("n/a");
        return 0;
    }
    arr1 = malloc(n1 * m1 * sizeof(int *) + m1 * sizeof(int *));
    int *p = (int *)(arr1 + n1);
    for (int i = 0; i < n1; ++i) {
        arr1[i] = p + m1 * i;
    }
    int num = input(arr1, &n1, &m1);
    if (num == 0) {
        free(arr1);
        return 0;
    }
    if (mode == 3) {
        if (n1 != m1) {
            printf("n/a");
            free(arr1);
            return 0;
        }
        transpose(arr1, n1, m1);
        output(arr1, n1, m1);
        free(arr1);
        return 0;
    }
    count = scanf("%d%d", &n2, &m2);
    if (count != 2 || n2 < 1 || m2 < 1) {
        printf("n/a");
        free(arr1);
        return 0;
    }
    arr2 = malloc(n2 * m2 * sizeof(int *) + m2 * sizeof(int *));
    p = (int *)(arr2 + n2);
    for (int i = 0; i < n2; ++i) {
        arr2[i] = p + m2 * i;
    }
    num = input(arr2, &n2, &m2);
    if (num == 0) {
        free(arr1);
        free(arr2);
        return 0;
    }
    switch (mode) {
        case 1: {
            int n_result = n1;
            int m_result = m1;
            int **matrix_result = malloc(n_result * m_result * sizeof(int *) + m_result * sizeof(int *));
            p = (int *)(matrix_result + n_result);
            for (int i = 0; i < n_result; ++i) {
                matrix_result[i] = p + m_result * i;
            }
            num = sum(arr1, n1, m1, arr2, n2, m2, matrix_result, &n_result, &m_result);
            if (num == 0) {
                free(arr1);
                free(arr2);
                free(matrix_result);
                return 0;
            }
            output(matrix_result, n_result, m_result);
            free(matrix_result);
            break;
        }
        case 2: {
            int n_result;
            int m_result;
            int **matrix_result = malloc(n1 * m2 * sizeof(int *) + m2 * sizeof(int *));
            p = (int *)(matrix_result + n1);
            for (int i = 0; i < n1; ++i) {
                matrix_result[i] = p + m2 * i;
            }
            num = mul(arr1, n1, m1, arr2, n2, m2, matrix_result, &n_result, &m_result);
            if (num == 0) {
                free(arr1);
                free(arr2);
                free(matrix_result);
                return 0;
            }
            output(matrix_result, n_result, m_result);
            free(matrix_result);
            break;
        }
    }
    free(arr1);
    free(arr2);
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

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (n_first != n_second || m_first != m_second) {
        printf("n/a");
        return 0;
    }
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return 1;
}

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (m_first != n_second) {
        printf("n/a");
        return 0;
    }
    *n_result = n_first;
    *m_result = m_second;
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = 0;
            for (int k = 0; k < m_first; k++) {
                matrix_result[i][j] += matrix_first[i][k] * matrix_second[k][j];
            }
        }
    }
    return 1;
}

int transpose(int **matrix, int n, int m) {
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < m; j++) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
    return 1;
}