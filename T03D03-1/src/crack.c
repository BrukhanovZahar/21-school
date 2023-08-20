#include <stdio.h>

int func(double x, double y);

int main() {
    double x, y;
    if (scanf("%lf %lf", &x, &y) == 2) {
        if (func(x, y)) {
            printf("GOTCHA\n");
        } else {
            printf("MISS\n");
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}

int func(double x, double y) {
    double rad = (x * x + y * y) * (x * x + y * y);
    double dist = x * x + y * y;
    return (dist < rad);
}