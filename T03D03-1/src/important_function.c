#include <math.h>
#include <stdio.h>

double func(double x);

int main() {
    double x;
    if (scanf("%lf", &x) == 1) {
        printf("%.1lf\n", func(x));
    } else {
        printf("n/a\n");
    }
    return 0;
}

double func(double x) {
    double y =
        7e-3 * pow(x, 4) + ((22.8 * cbrt(x) - 1e3) * x + 3) / (x * x / 2) - x * pow((10 + x), 2 / x) - 1.01;
    return round(y * 10) / 10;
}