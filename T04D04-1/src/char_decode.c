#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("n/a\n");
        return 0;
    }
    if (argv[1][0] == '0') {
        //кодирование
        while (1) {
            char c = getchar();
            char space = getchar();
            if (space != ' ' && space != '\n') {
                printf("n/a\n");
                return 0;
            }
            if (space == '\n') {
                printf("%X\n", c);
                break;
            } else {
                printf("%X ", c);
            }
        }
    } else if (argv[1][0] == '1') {
        //декодирование
        int c;
        char space;
        while (scanf("%x%c", &c, &space) != EOF) {
            if (space != ' ' && space != '\n') {
                printf("n/a\n");
                return 0;
            }

            if (c > 127) {
                printf("n/a\n");
                return 0;
            }

            if (space == '\n') {
                printf("%C\n", c);
                break;
            } else {
                printf("%C ", c);
            }
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}