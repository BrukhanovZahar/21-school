#ifndef S21_STRING_H
#define S21_STRING_H

unsigned int s21_strlen(const char *str);
int s21_strcmp(char *str1, char *str2);
void s21_strcpy(char *str1, char *str2);
void s21_strcat(char *str1, const char *str2);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *str1, const char *substr);
char *s21_strtok(char *str, const char *delim);

#endif
