#include <stdio.h>

static inline int isint(float d);
int max(int a, int b);

int main() {
    float n, m;
    int x, y;
    scanf("%f %f", &n, &m);
    if (isint(n) == 1 && isint(m) == 1) {
        x = (int)n;
        y = (int)m;
        printf("%d\n", max(x, y));
        return 1;
    } else {
        printf("n/a\n");
        return 0;
    }
}

static inline int isint(float d) { return d == (int)d; }

int max(int a, int b) { return a > b ? a : b; }