#include <stdio.h>

static inline int isint(float d) { return d == (int)d; }

int customDiv(int dividend, int divisor) {
    if (divisor == 0) {
        // Обработка деления на ноль
        return 0;
    }

    int quotient = 0;
    int remainder = dividend;

    while (remainder >= divisor) {
        remainder -= divisor;
        quotient++;
    }

    return quotient;
}

int customMod(int dividend, int divisor) {
    if (divisor == 0) {
        // Обработка деления на ноль
        return 0;
    }

    int quotient = customDiv(dividend, divisor);
    int remainder = dividend - (quotient * divisor);

    return remainder;
}

int is_prime(int num) {
    if (num < 2) {
        return 0;
    }

    for (int i = 2; i * i <= num; i++) {
        if (customMod(num, i) == 0) {
            return 0;
        }
    }

    return 1;
}

int largest_prime_divisor(int num) {
    int largest_divisor = -1;

    if (num < 0) {
        num = -num;
    }

    for (int i = 2; i <= num; i++) {
        if (customMod(num, i) == 0 && is_prime(i)) {
            largest_divisor = i;
        }
    }

    return largest_divisor;
}

int main() {
    int number;
    float x;
    scanf("%f", &x);
    if (isint(x) == 1) {
        number = (int)x;
        int c = largest_prime_divisor(number);
        if (c == -1) {
            printf("n/a\n");
        } else {
            printf("%d\n", c);
        }
        return 0;
    } else {
        printf("n/a\n");
    }
}