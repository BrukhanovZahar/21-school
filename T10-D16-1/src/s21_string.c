#include "s21_string.h"

#include <stdio.h>

unsigned int s21_strlen(const char *str) {
    unsigned int length = 0;
    for (; *(str + length); length++)
        ;
    return length;
}

int s21_strcmp(char *str1, char *str2) {
    for (; *str1 && *str1 == *str2; str1++, str2++)
        ;
    if ((*str1 - *str2) > 0) {
        return 1;
    } else if ((*str1 - *str2) < 0) {
        return -1;
    } else {
        return 0;
    }
}

void s21_strcpy(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0') {
        str2[i] = str1[i];
        i++;
    }
    str2[i] = str1[i];
}

void s21_strcat(char *str1, const char *str2) {
    int i = 0;
    for (; str1[i] != '\0'; i++)
        ;
    for (int j = 0; str2[j] != '\0'; j++, i++) {
        str1[i] = str2[j];
    }
    str1[i] = '\0';
}

char *s21_strchr(const char *str, int c) {
    while (*str != '\0') {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    if (c == '\0') {
        return (char *)str;
    }
    return NULL;
}

char *s21_strstr(const char *str1, const char *substr) {
    while (*str1 != '\0') {
        const char *s1 = str1;
        const char *s2 = substr;
        while (*s2 != '\0' && *s1 == *s2) {
            s1++;
            s2++;
        }
        if (*s2 == '\0') {
            return (char *)str1;
        }
        str1++;
    }
    return NULL;
}

char *s21_strtok(char *str, const char *delim) {
    static char *lastToken = NULL;
    char *token = NULL;
    if (str != NULL) {
        lastToken = str;
    } else if (lastToken == NULL) {
        return NULL;
    }
    token = lastToken;
    while (*lastToken != '\0') {
        if (s21_strchr(delim, *lastToken)) {
            *lastToken = '\0';
            lastToken++;
            return token;
        }
        lastToken++;
    }
    return (*token != '\0') ? token : NULL;
}