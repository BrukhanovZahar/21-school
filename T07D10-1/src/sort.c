#include <stdio.h>
#include <stdlib.h>

int input(int *a, int *n);

void output(int *a, int n);

void sorting_by_insertion(int *array, int size);

int main() {
    int n;
    int count = scanf("%d", &n);
    if (count != 1 || n < 1) {
        printf("n/a");
        return 0;
    }
    int *data = (int *)malloc(n * sizeof(int));
    if (data == NULL) {
        printf("n/a");
        return 0;
    }
    int sucsess = input(data, &n);
    if (sucsess == 0) {
        free(data);
        return 0;
    }
    sorting_by_insertion(data, n);
    output(data, n);
    free(data);
    return 0;
}

int input(int *a, int *n) {
    int count;
    for (int *p = a; p - a < *n - 1; p++) {
        count = scanf("%d", p);
        if (count != 1) {
            printf("n/a");
            return 0;
        }
    }
    count = scanf("%d", (a + *n - 1));
    if (count != 1) {
        printf("n/a");
        return 0;
    }
    return 1;
}

void output(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", a[i]);
    }
    printf("%d", a[n - 1]);
}

void sorting_by_insertion(int *array, int size) {
    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0 && array[j - 1] > array[j]; --j) {
            int x = array[j - 1];
            array[j - 1] = array[j];
            array[j] = x;
        }
    }
}