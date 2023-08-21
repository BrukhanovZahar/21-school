#include "infix_to_postfix.h"
#include "parse_expression.h"
#include "rendering_image.h"

int main() {
    char expression[100];
    printf("Введите выражение: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';
    Token *infix_tokens = NULL;
    int num_infix_tokens = 0;
    parse_expression(expression, &infix_tokens, &num_infix_tokens);
    // // Вывод лексем для проверки
    // printf("Лексемы:\n");
    // for (int i = 0; i < num_infix_tokens; i++) {
    //     printf("Тип: %d, Значение: %s\n", infix_tokens[i].type, infix_tokens[i].value);
    // }
    Token *postfix_tokens = NULL;
    int num_postfix_tokens = 0;
    infix_to_postfix(infix_tokens, num_infix_tokens, &postfix_tokens, &num_postfix_tokens);
    // // Вывод постфиксной записи в консоль
    // printf("Постфиксная запись:\n");
    // for (int i = 0; i < num_postfix_tokens; i++) {
    //     printf("Тип: %d, Значение: %s\n", postfix_tokens[i].type, postfix_tokens[i].value);
    // }
    int graphic_matrix[HEIGHT][WIDTH];
    fill_graph(graphic_matrix);
    create_graphic(graphic_matrix, postfix_tokens, num_postfix_tokens);
    print_graph(graphic_matrix);
    // Очистка памяти
    free(infix_tokens);
    free(postfix_tokens);

    return 0;
}
