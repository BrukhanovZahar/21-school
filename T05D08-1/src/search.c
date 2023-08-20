#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int* a, int* n);
double mean(int* a, int n);
double variance(int* a, int n);
int search(int* a, int n);

int main() {
    int n, data[NMAX];
    int sucsess = input(data, &n);
    if (sucsess == 0) {
        return 0;
    }
    printf("%d\n", search(data, n));
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

double mean(int* a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

double variance(int* a, int n) {
    double num = 0;
    double mn = mean(a, n);
    for (int i = 0; i < n; i++) {
        num += (a[i] - mn) * (a[i] - mn);
    }
    return num / n;
}

int search(int* a, int n) {
    int ans = 0;
    double mn = mean(a, n);
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0 && a[i] >= mn && a[i] <= mn + 3 * sqrt(variance(a, n)) && a[i] != 0) {
            ans = a[i];
            return ans;
        }
    }
    return ans;
}