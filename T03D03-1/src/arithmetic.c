#include <stdio.h>

static inline int isint(float d);
int sum(int a, int b);
int mul(int a, int b);
int min(int a, int b);
int div(int a, int b);

int main() {
    float n, m;
    int x, y;
    scanf("%f %f", &n, &m);
    if (isint(n) == 1 && isint(m) == 1) {
        x = (int)n;
        y = (int)m;
    } else {
        printf("n/a\n");
        return 0;
    }
    if (y == 0) {
        printf("%d %d %d n/a\n", sum(x, y), min(x, y), mul(x, y));
    } else {
        printf("%d %d %d %d\n", sum(x, y), min(x, y), mul(x, y), div(x, y));
    }
    return 1;
}

static inline int isint(float d) { return d == (int)d; }

int sum(int a, int b) { return a + b; }

int mul(int a, int b) { return a * b; }

int min(int a, int b) { return a - b; }

int div(int a, int b) { return a / b; }