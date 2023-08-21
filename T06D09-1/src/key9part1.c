#include <stdio.h>

#define NMAX 10

int input(int* buffer, int* length);
void output(int* buffer, int length);
int sum_numbers(int* buffer, int length);
int find_numbers(int* buffer, int length, int number, int* numbers);

int main() {
    int n, data[NMAX], numbers[NMAX];
    int sucsess = input(data, &n);
    if (sucsess == 0) {
        return 0;
    }
    int sn = sum_numbers(data, n);
    if (sn == -1) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (data[i] != 0) {
                count++;
            }
        }
        printf("%d\n", count);
        for (int i = 0; i < n - 1; i++) {
            if (data[i] == 0) {
                continue;
            }
            printf("%d ", data[i]);
        }
        if (data[n - 1] == 0) {
            printf("\n");
        } else {
            printf("%d\n", data[n - 1]);
        }
        return 0;
    } else if (sn == 0) {
        printf("n/a\n");
        return 0;
    }
    printf("%d\n", sn);
    int len = find_numbers(data, n, sn, numbers);
    output(numbers, len);
    return 0;
}

int input(int* buffer, int* length) {
    char enter;
    int count = scanf("%d%c", length, &enter);
    if (count != 2 || enter != '\n' || *length <= 0 || *length > NMAX) {
        printf("n/a\n");
        return 0;
    }
    for (int* p = buffer; p - buffer < *length - 1; p++) {
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
    return 1;
}

void output(int* buffer, int length) {
    for (int i = 0; i < length - 1; i++) {
        printf("%d ", buffer[i]);
    }
    printf("%d\n", buffer[length - 1]);
}

int sum_numbers(int* buffer, int length) {
    int sum = 0, isChange = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0 && buffer[i] != 0) {
            sum += buffer[i];
            isChange = 1;
        }
    }
    if (isChange == 1 && sum == 0) {
        return -1;
    }
    return sum;
}

int find_numbers(int* buffer, int length, int number, int* numbers) {
    int index = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[index] = buffer[i];
            index++;
        }
    }
    return index;
}
