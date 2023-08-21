#include "s21_string_test.h"

#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

int main() {
#ifdef Q1
    s21_strlen_test();
#endif
#ifdef Q2
    s21_strcmp_test();
#endif
#ifdef Q3
    s21_strcpy_test();
#endif
#ifdef Q4
    s21_strcat_test();
#endif
#ifdef Q5
    s21_strchr_test();
#endif
#ifdef Q6
    s21_strstr_test();
#endif
#ifdef Q7
    s21_strtok_test();
#endif
    return 0;
}

void s21_strlen_test() {
    int test = 16, result;
    char input1[] = "Hello, School21!";
    result = s21_strlen(input1);
    output_strlen_test(input1, result, test);
    printf("\n");
    char input2[16] = "Hello, School21!";
    result = s21_strlen(input2);
    output_strlen_test(input2, result, test);
    printf("\n");
    char input3[] = "Привет, Школа21!";
    result = s21_strlen(input3);
    output_strlen_test(input3, result, test);
    printf("\n");
    test = 0;
    char input4[] = "";
    result = s21_strlen(input4);
    output_strlen_test(input4, result, test);
    printf("\n");
    test = 5;
    char input5[] = "12345";
    result = s21_strlen(input5);
    output_strlen_test(input5, result, test);
}

void output_strlen_test(char *input, int output, int result) {
    printf("%s\n%d\n", input, output);
    if (output == result) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strcmp_test() {
    int test = 0, result;
    char input1[] = "Hello, School21!";
    char input2[] = "Hello, School21!";
    result = s21_strcmp(input1, input2);
    output_strcmp_test(input1, input2, result, test);
    printf("\n");
    test = -1;
    char input3[] = "Hello";
    char input4[] = "Help";
    result = s21_strcmp(input3, input4);
    output_strcmp_test(input3, input4, result, test);
    printf("\n");
    test = 1;
    char input5[] = "1234";
    char input6[] = "12315";
    result = s21_strcmp(input5, input6);
    output_strcmp_test(input5, input6, result, test);
    printf("\n");
    test = -1;
    char input7[] = "";
    char input8[] = "!@'/";
    result = s21_strcmp(input7, input8);
    output_strcmp_test(input7, input8, result, test);
}

void output_strcmp_test(char *input1, char *input2, int output, int result) {
    printf("%s\n%s\n%d\n", input1, input2, output);
    if (output == result) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strcpy_test() {
    char input1[] = "Hello, School21!", input2[30];
    s21_strcpy(input1, input2);
    output_strcpy_test(input1, input2);
    printf("\n");
    char input3[16] = "Hello, School21!", input4[30];
    s21_strcpy(input3, input4);
    output_strcpy_test(input3, input4);
    printf("\n");
    char input5[] = "Привет, Школа21!", input6[30];
    s21_strcpy(input5, input6);
    output_strcpy_test(input5, input6);
    printf("\n");
    char input7[] = "", input8[30];
    s21_strcpy(input7, input8);
    output_strcpy_test(input7, input8);
    printf("\n");
}

void output_strcpy_test(char *input, char *result) {
    printf("%s\n%s\n", input, result);
    int success = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != result[i]) {
            success = 0;
            break;
        }
    }
    if (success == 1) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strcat_test() {
    char input1[30] = "Hello, ", input2[] = "School21!", result1[] = "Hello, School21!";
    s21_strcat(input1, input2);
    output_strcpy_test(input1, result1);
    printf("\n");
    char input3[30] = "Hello, ", input4[9] = "School21!", result2[] = "Hello, School21!";
    s21_strcat(input3, input4);
    output_strcpy_test(input3, result2);
    printf("\n");
    char input5[30] = "Привет, ", input6[] = "Школа21!", result3[] = "Привет, Школа21!";
    s21_strcat(input5, input6);
    output_strcpy_test(input5, result3);
    printf("\n");
    char input7[30] = "", input8[] = "123", result4[] = "123";
    s21_strcat(input7, input8);
    output_strcpy_test(input7, result4);
    printf("\n");
}

void output_strcat_test(char *input, char *result) {
    printf("%s\n%s\n", input, result);
    int success = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != result[i]) {
            success = 0;
            break;
        }
    }
    if (success == 1) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}

void s21_strchr_test() {
    char input1[] = "Hello, School21!", c1 = 'c';
    char *result1 = s21_strchr(input1, c1);
    output_strchr_test(input1, c1, result1);
    printf("\n");
    char input2[16] = "Hello, School21!", c2 = '!';
    char *result2 = s21_strchr(input2, c2);
    output_strchr_test(input2, c2, result2);
    printf("\n");
    char input3[] = "Привет, Школа21!", c3 = ',';
    char *result3 = s21_strchr(input3, c3);
    output_strchr_test(input3, c3, result3);
    printf("\n");
    char input4[] = "12345", c4 = '6';
    char *result4 = s21_strchr(input4, c4);
    output_strchr_test(input4, c4, result4);
}

void output_strchr_test(char *input, char c, char *result) {
    if (result == NULL) {
        printf("%s %c NULL\n", input, c);
        printf("FAIL");
    } else {
        printf("%s %c %c\n", input, c, *result);
        if (c == *result) {
            printf("SUCCESS");
        } else {
            printf("FAIL");
        }
    }
}

void s21_strstr_test() {
    char input1[] = "Hello, School21!", input2[] = "School21!";
    char *result1 = s21_strstr(input1, input2);
    output_strstr_test(input1, input2, result1);
    printf("\n");
    char input3[] = "Привет, Школа21!", input4[] = "вет";
    char *result2 = s21_strstr(input3, input4);
    output_strstr_test(input3, input4, result2);
    printf("\n");
    char input5[] = "12345", input6[] = "abc";
    char *result3 = s21_strstr(input5, input6);
    output_strstr_test(input5, input6, result3);
}

void output_strstr_test(char *input1, char *input2, char *result) {
    if (result == NULL) {
        printf("%s\n%s\nNULL\n", input1, input2);
        printf("FAIL");
    } else {
        printf("%s\n%s\n%s\n", input1, input2, result);
        int success = 1;
        for (int i = 0; input2[i] != '\0'; i++) {
            if (input2[i] != result[i]) {
                success = 0;
                break;
            }
        }
        if (success == 1) {
            printf("SUCCESS");
        } else {
            printf("FAIL");
        }
    }
}

void s21_strtok_test() {
    char input1[] = "Hello, School21!";
    char input2[] = " ";
    char ans1[] = "Hello,School21!";
    printf("%s\n%s\n", input1, input2);
    char *result1 = s21_strtok(input1, input2);
    char new_str1[100] = "";
    while (result1 != NULL) {
        s21_strcat(new_str1, result1);
        result1 = s21_strtok(NULL, input2);
    }
    output_strtok_test(ans1, new_str1);
    printf("\n");
    char input3[] = "При,вет, Шко,ла21!";
    char input4[] = ",";
    char ans2[] = "Привет Школа21!";
    printf("%s\n%s\n", input3, input4);
    char *result2 = s21_strtok(input3, input4);
    char new_str2[100] = "";
    while (result2 != NULL) {
        s21_strcat(new_str2, result2);
        result2 = s21_strtok(NULL, input4);
    }
    output_strtok_test(ans2, new_str2);
    printf("\n");
    char input5[] = "12345";
    char input6[] = "6";
    char ans3[] = "12345";
    printf("%s\n%s\n", input5, input6);
    char *result3 = s21_strtok(input5, input6);
    char new_str3[100] = "";
    while (result3 != NULL) {
        s21_strcat(new_str3, result3);
        result3 = s21_strtok(NULL, input6);
    }
    output_strtok_test(ans3, new_str3);
}

void output_strtok_test(char *ans, char *result) {
    printf("%s\n", result);
    int success = 1;
    for (int i = 0; ans[i] != '\0' && result[i] != '\0'; i++) {
        if (ans[i] != result[i]) {
            success = 0;
            break;
        }
    }
    if (success == 1) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
}