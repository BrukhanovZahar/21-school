#include <stdio.h>
#include <stdlib.h>

#define NMAX 100

int input_din(int **arr, int n, int m);

void output_din(int **a, int n, int m);

void free_second(int **a, int n);

int main() {
    int n, m, mode;
    int count = scanf("%d", &mode);
    if (count != 1 || mode < 1 || mode > 4) {
        printf("n/a");
        return 0;
    }
    count = scanf("%d %d", &n, &m);
    if (count != 2 || n < 1 || m < 1) {
        printf("n/a");
        return 0;
    }
    switch (mode) {
        case 1: {
            if (n > 100 || m > 100) {
                printf("n/a");
                break;
            }
            int arr[NMAX][NMAX];
            int *ptr[NMAX];
            for (int i = 0; i < NMAX; ++i) {
                ptr[i] = arr[i];
            }
            int num = input_din(ptr, n, m);
            if (num == 0) {
                break;
            }
            output_din(ptr, n, m);
            break;
        }
        case 2: {
            int **arr = malloc(n * sizeof(int *));
            for (int i = 0; i < n; i++) {
                arr[i] = malloc(m * sizeof(int));
            }
            int num = input_din(arr, n, m);
            if (num == 0) {
                free_second(arr, n);
                break;
            }
            output_din(arr, n, m);
            free_second(arr, n);
            break;
        }
        case 3: {
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
            output_din(arr, n, m);
            free(val_arr);
            free(arr);
            break;
        }
        case 4: {
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