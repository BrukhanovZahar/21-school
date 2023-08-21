#include <stdio.h>

#define NMAX 10

int input(int *buffer, int *length, int *number);

void output(int *buffer, int length);

void cycle_shift(int *buffer, int length, int number);

int main() {
    int n, a, data[NMAX];
    int sucsess = input(data, &n, &a);
    if (sucsess == 0) {
        return 0;
    }
    a = a % n;
    cycle_shift(data, n, a);
    output(data, n);
    return 0;
}

int input(int *buffer, int *length, int *number) {
    char enter;
    int count = scanf("%d%c", length, &enter);
    if (count != 2 || enter != '\n' || *length <= 0 || *length > NMAX) {
        printf("n/a\n");
        return 0;
    }
    for (int *p = buffer; p - buffer < *length - 1; p++) {
        count = scanf("%d%c", p, &enter);
        if (count != 2 || enter != ' ') {
            printf("n/a\n");
            return 0;
        }
    }
    count = scanf("%d%c", (buffer + *length - 1), &enter);
    if (count != 2 || enter != '\n') {
        printf("n/a\n");
        return 0;
    }
    count = scanf("%d%c", number, &enter);
    if (count != 2 || enter != '\n') {
        printf("n/a\n");
        return 0;
    }
    return 1;
}

void output(int *buffer, int length) {
    for (int i = 0; i < length - 1; i++) {
        printf("%d ", buffer[i]);
    }
    printf("%d\n", buffer[length - 1]);
}

void cycle_shift(int *buffer, int length, int number) {
    int arr[length];
    for (int i = 0; i < length; i++) {
        int x = i - number;
        if (x < 0) {
            x += length;
        }
        if (x > length - 1) {
            x -= length;
        }
        arr[x] = buffer[i];
    }
    for (int i = 0; i < length; i++) {
        buffer[i] = arr[i];
    }
}