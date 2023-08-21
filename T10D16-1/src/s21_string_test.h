#ifndef S21_STRING_TEST_H
#define S21_STRING_TEST_H

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

void output_strlen_test(char *input, int output, int result);
void output_strcmp_test(char *input1, char *input2, int output, int result);
void output_strcpy_test(char *input, char *result);
void output_strcat_test(char *input, char *result);
void output_strchr_test(char *input, char c, char *result);
void output_strstr_test(char *input1, char *input2, char *result);
void output_strtok_test(char *ans, char *result);
#endif
