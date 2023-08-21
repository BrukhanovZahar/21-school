#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *f;
    if ((f = fopen("input5.txt", "w")) == NULL)
        printf("File does not exist or open.");
    else {
        srand(time(NULL));
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < 81; ++j) {
                char s[81];
                s[i] = rand() % 4 + '*';
                if (s[i] == '+') s[i] = '*';
                if (s[i] == ',') s[i] = '-';
                if (j == 80) {
                    fprintf(f, "\n");
                } else
                    fprintf(f, "%c", s[i]);
            }
        }
        fclose(f);
    }
    return 0;
}
