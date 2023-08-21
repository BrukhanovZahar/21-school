#include <stdio.h>

#define LEN 100

int input(int *buff);

void output(int *buffer, int length);

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

int main() {
    int n1, n2, n3, n4, data1[LEN], data2[LEN], result3[LEN], result4[LEN];
    n1 = input(data1);
    if (n1 == -1) {
        return 0;
    }
    n2 = input(data2);
    if (n2 == -1) {
        return 0;
    }
    if (n1 > LEN || n2 > LEN) {
        printf("n/a\n");
        return 0;
    }
    sum(data1, n1, data2, n2, result3, &n3);
    output(result3, n3);
    sub(data1, n1, data2, n2, result4, &n4);
    if (n4 == -1) {
        return 0;
    }
    output(result4, n4);
}

int input(int *buff) {
    char enter;
    int number, index = 0;
    while (1) {
        int count = scanf("%d%c", &number, &enter);
        if (count != 2 || (enter != '\n' && enter != ' ') || number < 0 || number > 9) {
            printf("n/a\n");
            return -1;
        }
        buff[index] = number;
        index++;
        if (enter == '\n') {
            return index;
        }
    }
}

void output(int *buffer, int length) {
    int isStart = 0;
    for (int i = 0; i < length - 1; i++) {
        if (!isStart && buffer[i] == 0) {
            continue;
        }
        printf("%d ", buffer[i]);
        isStart = 1;
    }
    printf("%d\n", buffer[length - 1]);
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int carry = 0;  // Переменная для хранения переноса при сложении цифр
    int max_len = len1 > len2 ? len1 : len2;  // Определение максимальной длины из двух чисел

    // Цикл для каждой цифры с младших разрядов к старшим
    for (int i = 0; i < max_len; i++) {
        int num1 = i < len1 ? buff1[len1 - 1 - i]
                            : 0;  // Получаем текущую цифру первого числа или 0, если число закончилось
        int num2 = i < len2 ? buff2[len2 - 1 - i]
                            : 0;  // Получаем текущую цифру второго числа или 0, если число закончилось

        int sum = num1 + num2 + carry;  // Складываем текущие цифры и перенос
        result[i] = sum % 10;  // Записываем остаток от деления на 10 (единицы) в текущую позицию результата
        carry = sum / 10;      // Получаем перенос для следующей итерации
    }

    // Если после сложения последних цифр остался перенос, добавляем его в последний разряд результата
    if (carry > 0) {
        result[max_len] = carry;
        *result_length = max_len + 1;
    } else {
        *result_length = max_len;
    }

    // Разворачиваем массив с результатом, чтобы получить правильный порядок цифр
    for (int i = 0; i < *result_length / 2; i++) {
        int temp = result[i];
        result[i] = result[*result_length - 1 - i];
        result[*result_length - 1 - i] = temp;
    }
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    if (len1 < len2) {
        printf("n/a\n");
        *result_length = -1;
        return;
    }
    // Проверка что первое число больше второго при равенстве их длин
    int isStart = 0;
    if (len1 == len2) {
        for (int i = 0; i < len1 && isStart == 0; i++) {
            if (buff1[i] < buff2[i]) {
                printf("n/a\n");
                *result_length = -1;
                return;
            }
            if (buff1[i] > buff2[i]) {
                isStart = 1;
            }
        }
    }
    // Удаление незначащих нулей в первом числе
    for (int i = 0; i < len1; i++) {
        if (buff1[i] == 0) {
            buff1 = &buff1[i + 1];
            i--;
            len1--;
            continue;
        } else {
            break;
        }
    }
    // Удаление незначащих нулей во втором числе
    for (int i = 0; i < len2; i++) {
        if (buff2[i] == 0) {
            buff2 = &buff2[i + 1];
            i--;
            len2--;
            continue;
        } else {
            break;
        }
    }

    int borrow = 0;  // Переменная для хранения заема при вычитании цифр
    int i = len1 - 1;  // Индекс последнего элемента первого числа
    int j = len2 - 1;  // Индекс последнего элемента второго числа
    int k = len1 - 1;  // Индекс последнего элемента результата

    // Цикл выполняется для каждой цифры с младших разрядов к старшим первого числа, общее количество итераций
    // равно len1
    while (i >= 0) {
        int num1 = buff1[i];  // Получаем текущую цифру первого числа
        int num2 =
            j >= 0 ? buff2[j] : 0;  // Получаем текущую цифру второго числа или 0, если число закончилось

        // Вычитаем из текущих цифр второго числа заем из предыдущей итерации
        int diff = num1 - num2 - borrow;

        if (diff < 0) {
            // Если результат вычитания отрицателен, запоминаем заем и увеличиваем текущую цифру первого числа
            // на 10
            borrow = 1;
            diff += 10;
        } else {
            borrow = 0;  // Если результат положителен, заем не нужен
        }

        result[k] = diff;  // Записываем результат вычитания в текущую позицию результата
        i--;               // Переходим к следующей цифре первого числа
        j--;  // Переходим к следующей цифре второго числа (если возможно)
        k--;  // Переходим к предыдущей позиции результата
    }

    // Удаление ведущих нулей в результате
    while (len1 > 1 && result[0] == 0) {
        for (int l = 0; l < len1 - 1; l++) {
            result[l] = result[l + 1];
        }
        len1--;
    }
    *result_length = len1;  // Обновляем длину результата (количество цифр)
}