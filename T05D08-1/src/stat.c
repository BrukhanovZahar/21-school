#include <stdio.h>
#define NMAX 10

int input(int* a, int* n);
void output(int* a, int n);
int max(int* a, int n);
int min(int* a, int n);
double mean(int* a, int n);
double variance(int* a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int sucsess = input(data, &n);
    if (sucsess == 0) {
        return 0;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

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

int max(int* a, int n) {
    int ans = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > ans) {
            ans = a[i];
        }
    }
    return ans;
}

int min(int* a, int n) {
    int ans = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] < ans) {
            ans = a[i];
        }
    }
    return ans;
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

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}