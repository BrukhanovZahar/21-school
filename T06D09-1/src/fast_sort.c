#include <stdio.h>

#define NMAX 10

int input(int *a, int *n);

void output(int *a, int n);

int min(int x, int y);

void merge(int *array, int n, int m);

void sorting_by_insertion(int *array, int n);

void merge_sorting(int *array, int n);

void timSort(int *array, int n);

int main() {
    int n = 10, data1[NMAX], data2[NMAX];
    int sucsess = input(data1, &n);
    if (sucsess == 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        data2[i] = data1[i];
    }
    merge_sorting(data1, n);
    output(data1, n);
    timSort(data2, n);
    output(data2, n);

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

int min(int x, int y) { return x < y ? x : y; }

void merge(int *array, int n, int m) {
    int i, j, k;
    int x[n];
    for (i = 0, j = m, k = 0; k < n; k++) {
        x[k] = j == n ? array[i++] : i == m ? array[j++] : array[j] < array[i] ? array[j++] : array[i++];
    }
    for (i = 0; i < n; i++) {
        array[i] = x[i];
    }
}

void merge_sorting(int *array, int n) {
    if (n < 2) {
        return;
    }
    int m = n / 2;
    merge_sorting(array, m);
    merge_sorting(array + m, n - m);
    merge(array, n, m);
}

void sorting_by_insertion(int *array, int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && array[j - 1] > array[j]; --j) {
            int x = array[j - 1];
            array[j - 1] = array[j];
            array[j] = x;
        }
    }
}

void timSort(int *array, int n) {
    const int MIN_MERGE = 10;
    if (n < 2) return;

    int minRun = MIN_MERGE;
    while (minRun < n) {
        minRun = minRun * 2 + 1;
    }
    minRun = min(minRun, n);
    minRun = minRun < n ? minRun : n;
    for (int i = 0; i < n; i += minRun) {
        sorting_by_insertion(array + i, min(i + minRun, n) - i);
    }

    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            merge(array + left, right - left + 1, mid - left + 1);
        }
    }
}
