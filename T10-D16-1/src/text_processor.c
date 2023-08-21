#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TEXT_LENGTH 100

int input(char *text, int *n) {
    if (scanf("%d", n) != 1) {
        printf("n/a");
        return 1;
    }
    if (*n <= 0) {
        printf("n/a");
        return 1;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    if (fgets(text, MAX_TEXT_LENGTH, stdin) == NULL) {
        printf("n/a");
        return 1;
    }
    return 0;
}

void output(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        printf("%c", str[i]);
    }
}

void clear_string(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        str[i] = '\0';
    }
}

void first_check(char *str, char *text, int *index, int *remains, int *width, int *i) {
    output(str);
    *remains -= *index;
    if (*remains > 1 && text[*i + 1] != '\0' && text[*i + 1] != '\n') {
        int size = 0;
        for (int j = *i + 2; text[j] != ' ' && text[j] != '\0' && text[j] != '\n'; ++j) {
            size++;
        }
        if ((size < *remains - 1 || size > *width) && (*remains - 2 != 0)) {
            printf(" ");
            *remains = *remains - 1;
        } else if ((size < *remains - 1 || size > *width) && (*remains - 2 == 0)) {
            printf("\n");
            *remains = *width;
        }
    }
}

void second_check(char *str, int *remains, int *width) {
    output(str);
    printf("\n");
    *remains = *width;
}

void third_check(char *str, char *text, int *index, int *remains, int *width, int *i) {
    printf("\n");
    output(str);
    *remains = *width - *index;
    int size = 0;
    for (int j = *i + 2; text[j] != ' ' && text[j] != '\0' && text[j] != '\n'; ++j) {
        size++;
    }
    if (size < *remains - 1 || size > *width) {
        printf(" ");
        *remains = *remains - 1;
    }
}

void fourth_check(char *str, int *remains, int *width) {
    printf("\n");
    output(str);
    printf("\n");
    *remains = *width;
}

void five_check(char *str, int *index, int *remains, int *width) {
    for (int j = 0; str[j] != '\0'; ++j) {
        if (*remains - 2 == 0 && j + 2 != *index) {
            printf("%c", str[j]);
            if (j + 1 != *index) {
                printf("-");
                printf("\n");
                *remains = *width;
            }
        } else {
            printf("%c", str[j]);
            *remains = *remains - 1;
        }
    }
}

void text_formatting(char *text, char *str, int width) {
    int remains = width, index = 0;
    for (int i = 0; text[i] != '\0' && text[i] != '\n'; ++i) {
        // Делим строку на слова
        if (text[i + 1] == ' ' || text[i + 1] == '\0' || text[i + 1] == '\n') {
            if (text[i] != ' ') {
                str[index] = text[i];
                index++;
            }
            if (index < remains) {
                first_check(str, text, &index, &remains, &width, &i);
            } else if (index == remains) {
                second_check(str, &remains, &width);
            } else if (index > remains && index < width) {
                third_check(str, text, &index, &remains, &width, &i);
            } else if (index > remains && index == width) {
                fourth_check(str, &remains, &width);
            } else if (index > remains && index > width) {
                five_check(str, &index, &remains, &width);
            }
            fflush(stdout);
            clear_string(str);
            index = 0;
        } else {
            if (text[i] != ' ') {
                str[index] = text[i];
                index++;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Проверяем флаг с которым запущенна программа
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'w' && argv[1][2] == '\0') {
        int width;
        char text[MAX_TEXT_LENGTH + 1];
        char str[MAX_TEXT_LENGTH + 1] = {0};
        // Считывание данных с клавиатуры
        if (input(text, &width) != 1) {
            text_formatting(text, str, width);
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}
