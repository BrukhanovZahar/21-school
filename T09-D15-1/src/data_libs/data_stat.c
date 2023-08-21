#include "data_stat.h"

double max(double *data, int n) {
    double mx = data[0];
    for (int i = 0; i < n; ++i) {
        mx = mx > data[i] ? mx : data[i];
    }
    return mx;
}

double min(double *data, int n) {
    double mn = data[0];
    for (int i = 0; i < n; ++i) {
        mn = mn < data[i] ? mn : data[i];
    }
    return mn;
}

double mean(double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += data[i];
    }
    return sum / n;
}

double variance(double *data, int n) {
    double num = 0;
    double mn = mean(data, n);
    for (int i = 0; i < n; ++i) {
        num += (data[i] - mn) * (data[i] - mn);
    }
    return num / n;
}

void sort(double *data, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i; j > 0 && data[j - 1] > data[j]; --j) {
            double x = data[j - 1];
            data[j - 1] = data[j];
            data[j] = x;
        }
    }
}