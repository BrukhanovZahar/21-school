#include <math.h>
#include <stdio.h>

double ver_agn(double x) { return 1 / (1 + x * x); }

double lem_ber(double x) { return sqrt(sqrt(1 + 4 * x * x) - x * x - 1); }

double qua_hyp(double x) { return 1 / (x * x); }

int main() {
    const int num_values = 42;
    const double pi = M_PI;
    double start = -pi;
    double end = pi;
    double step = (end - start) / (num_values - 1);
    for (int i = 0; i < num_values; i++) {
        double value = start + i * step;
        double lb = lem_ber(value);
        if (lb > 0) {
            printf("%.7f | %.7f | %.7f | %.7f\n", value, ver_agn(value), lb, qua_hyp(value));
        } else {
            printf("%.7f | %.7f | - | %.7f\n", value, ver_agn(value), qua_hyp(value));
        }
    }
    return 0;
}