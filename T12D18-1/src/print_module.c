#include "print_module.h"

#include <stdio.h>
#include <time.h>

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char *message) {
    for (int i = 0; Log_prefix[i] != '\0'; ++i) {
        print(Log_prefix[i]);
    }
    print(' ');
    // Получение текущего времени
    time_t t;
    struct tm *time_info;
    time(&t);
    time_info = localtime(&t);
    char time_str[9];  // "ЧЧ:ММ:СС\0"
    strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);
    for (int i = 0; time_str[i] != '\0'; ++i) {
        print(time_str[i]);
    }
    print(' ');
    for (int i = 0; message[i] != '\0'; ++i) {
        print(message[i]);
    }
}
