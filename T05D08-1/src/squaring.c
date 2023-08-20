#include <stdio.h>
#define NMAX 10

int input(int* a, int* n);
void output(int* a, int n);
void squaring(int* a, int n);

int main() {
    int n, data[NMAX];
    int sucsess = input(data, &n);
    if (sucsess == 0) {
        return 0;
    }
    squaring(data, n);
    output(data, n);

    return 0;
}

int input(int* a, int* n) {
    char enter;
    int count = scanf("%d%c", n, &enter);
    if (count != 2 || enter != '\n' || *n <= 0 || *n > NMAX) {
        printf("n/a\n");
        return 0;
    }
    for (int* p = a; p - a < *n - 1; p++) {
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

void output(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", a[i]);
    }
    printf("%d\n", a[n - 1]);
}

void squaring(int* a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * a[i];
    }
}
