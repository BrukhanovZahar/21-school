#include <stdio.h>
#include <stdlib.h>

int input_din(int **arr, int n, int m);

void output_din(int **a, int n, int m);

void sort_matrix(int **a, int n, int m);

int sum(int **a, int n, int m);

void free_second(int **a, int n);

int main() {
    int n, m, mode;
    int count = scanf("%d", &mode);
    if (count != 1 || mode < 1 || mode > 3) {
        printf("n/a");
        return 0;
    }
    count = scanf("%d%d", &n, &m);
    if (count != 2 || n < 1 || m < 1) {
        printf("n/a");
        return 0;
    }
    switch (mode) {
        case 1: {
            int **arr = malloc(n * sizeof(int *));
            for (int i = 0; i < n; i++) {
                arr[i] = malloc(m * sizeof(int));
            }
            int num = input_din(arr, n, m);
            if (num == 0) {
                free_second(arr, n);
                break;
            }
            sort_matrix(arr, n, m);
            output_din(arr, n, m);
            free_second(arr, n);
            break;
        }
        case 2: {
            int **arr = malloc(n * sizeof(int *));
            int *val_arr = malloc(n * m * sizeof(int));
            for (int i = 0; i < n; ++i) {
                arr[i] = val_arr + m * i;
            }
            int num = input_din(arr, n, m);
            if (num == 0) {
                free(val_arr);
                free(arr);
                break;
            }
            sort_matrix(arr, n, m);
            output_din(arr, n, m);
            free(val_arr);
            free(arr);
            break;
        }
        case 3: {
            int **arr = malloc(n * m * sizeof(int *) + m * sizeof(int *));
            int *p = (int *)(arr + n);
            for (int i = 0; i < n; ++i) {
                arr[i] = p + m * i;
            }
            int num = input_din(arr, n, m);
            if (num == 0) {
                free(arr);
                break;
            }
            sort_matrix(arr, n, m);
            output_din(arr, n, m);
            free(arr);
            break;
        }
    }
    return 0;
}

int input_din(int **arr, int n, int m) {
    int count;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; j++) {
            count = scanf("%d", &arr[i][j]);
            if (count != 1) {
                printf("n/a");
                return 0;
            }
        }
        count = scanf("%d", &arr[i][m - 1]);
        if (count != 1) {
            printf("n/a");
            return 0;
        }
    }
    return 1;
}

void output_din(int **a, int n, int m) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            printf("%d ", a[i][j]);
        }
        printf("%d\n", a[i][m - 1]);
    }
    for (int j = 0; j < m - 1; j++) {
        printf("%d ", a[n - 1][j]);
    }
    printf("%d", a[n - 1][m - 1]);
}

void free_second(int **a, int n) {
    for (int i = 0; i < n; ++i) {
        free(a[i]);
    }
    free(a);
}

void sort_matrix(int **a, int n, int m) {
    int isChange = 1;
    for (int i = n - 1; i >= 0; i--) {
        isChange = 1;
        for (int j = 0; j < i; j++) {
            if (sum(a, j, m) > sum(a, j + 1, m)) {
                int *tmp = malloc(m * sizeof(int));
                for (int z = 0; z < m; z++) {
                    tmp[z] = a[j][z];
                }
                for (int z = 0; z < m; z++) {
                    a[j][z] = a[j + 1][z];
                }
                for (int z = 0; z < m; z++) {
                    a[j + 1][z] = tmp[z];
                }
                isChange = 0;
                free(tmp);
            }
        }
        if (isChange == 1) {
            break;
        }
    }
}

int sum(int **a, int n, int m) {
    int sm = 0;
    for (int i = 0; i < m; i++) {
        sm += a[n][i];
    }
    return sm;
}