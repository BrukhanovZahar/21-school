#include <stdio.h>
#include <string.h>

struct Record {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
};

int main() {
    char file_path[100] = "../";
    char tmp_path[100];
    scanf("%s", tmp_path);
    strcat(file_path, tmp_path);
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("n/a");
    } else {
        char search_date[11];
        scanf("%s", search_date);
        struct Record record;
        int found = 0;
        while (fread(&record, sizeof(struct Record), 1, file) == 1) {
            char date[11];
            snprintf(date, sizeof(date), "%02d.%02d.%04d", record.day, record.month, record.year);
            if (strcmp(date, search_date) == 0) {
                printf("%d", record.code);
                found = 1;
                break;
            }
        }
        fclose(file);
        if (!found) {
            printf("n/a");
        }
    }
    return 0;
}
