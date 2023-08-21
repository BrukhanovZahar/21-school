#include <stdio.h>

#define NMAX 10

int input(int *a, int *n);

void output(int *a, int n);

void sorting_by_insertion(int *array, int size);

int main() {
    int n = 10, data[NMAX];
    int sucsess = input(data, &n);
    if (sucsess == 0) {
        return 0;
    }
    sorting_by_insertion(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int *n) {
    char enter;
    int count;
    for (int *p = a; p - a < *n - 1; p++) {
        count = scanf("%d%c", p, &enter);
        if (count != 2 || enter != ' ') {
            printf("n/a\n");
            return 0;
        }
    }
    count = scanf("%d%c", (a + *n - 1), &enter);
    if (count != 2 || enter != '\n') {
        printf("n/a\n");
        return 0;
    }
    return 1;
}

void output(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", a[i]);
    }
    printf("%d\n", a[n - 1]);
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