#include <stdio.h>

unsigned int fib_rec(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fib_rec(n - 1) + fib_rec(n - 2);
}

int main() {
    int x;
    scanf("%d", &x);
    printf("%d\n", fib_rec(x));
}