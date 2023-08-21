#include <stdio.h>
#include <stdlib.h>
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

int compare_records(const void *a, const void *b) {
    struct Record *record_a = (struct Record *)a;
    struct Record *record_b = (struct Record *)b;
    int result = 0;
    if (record_a->year != record_b->year) {
        result = record_a->year - record_b->year;
    } else if (record_a->month != record_b->month) {
        result = record_a->month - record_b->month;
    } else if (record_a->day != record_b->day) {
        result = record_a->day - record_b->day;
    } else if (record_a->hour != record_b->hour) {
        result = record_a->hour - record_b->hour;
    } else if (record_a->minute != record_b->minute) {
        result = record_a->minute - record_b->minute;
    } else if (record_a->second != record_b->second) {
        result = record_a->second - record_b->second;
    }
    return result;
}

void print_record(struct Record *record) {
    printf("%d %d %d %d %d %d %d %d\n", record->year, record->month, record->day, record->hour,
           record->minute, record->second, record->status, record->code);
}

int input_record(struct Record *new_record) {
    int res = 0;
    if (scanf("%d", &new_record->year) != 1) {
        printf("n/a");
        res = 1;
    }
    if (scanf("%d", &new_record->month) != 1) {
        printf("n/a");
        res = 1;
    }
    if (scanf("%d", &new_record->day) != 1) {
        printf("n/a");
        res = 1;
    }
    if (scanf("%d", &new_record->hour) != 1) {
        printf("n/a");
        res = 1;
    }
    if (scanf("%d", &new_record->minute) != 1) {
        printf("n/a");
        res = 1;
    }
    if (scanf("%d", &new_record->second) != 1) {
        printf("n/a");
        res = 1;
    }
    if (scanf("%d", &new_record->status) != 1) {
        printf("n/a");
        res = 1;
    }
    if (scanf("%d", &new_record->code) != 1) {
        printf("n/a");
        res = 1;
    }
    if (new_record->year > 2023 || new_record->month < 0 || new_record->month > 12 || new_record->day < 0 ||
        new_record->day > 31 || new_record->hour < 0 || new_record->hour > 23 || new_record->minute < 0 ||
        new_record->minute > 59 || new_record->second < 0 || new_record->second > 59 ||
        new_record->status < 0 || new_record->status > 1) {
        printf("n/a");
        res = 1;
    }
    return res;
}

int main() {
    char file_path[100] = "../";
    char tmp_path[100];
    scanf("%s", tmp_path);
    strcat(file_path, tmp_path);
    FILE *file = fopen(file_path, "r+b");
    if (!file) {
        printf("n/a");
    } else {
        int choice;
        do {
            if (scanf("%d", &choice) != 1) {
                printf("n/a");
                break;
            }
            if (choice == 0) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                if (file_size == 0) {
                    printf("n/a");
                    fclose(file);
                    break;
                }
                fseek(file, 0, SEEK_SET);
                struct Record record;
                while (fread(&record, sizeof(struct Record), 1, file) == 1) {
                    print_record(&record);
                }
                break;
            } else if (choice == 1) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                if (file_size == 0) {
                    printf("n/a");
                    fclose(file);
                    break;
                }
                fseek(file, 0, SEEK_END);
                long size = ftell(file);
                int num_records = size / sizeof(struct Record);
                struct Record *records = malloc(size);
                if (!records) {
                    printf("n/a");
                    fclose(file);
                    break;
                }
                fseek(file, 0, SEEK_SET);
                fread(records, sizeof(struct Record), num_records, file);
                qsort(records, num_records, sizeof(struct Record), compare_records);
                for (int i = 0; i < num_records; i++) {
                    print_record(&records[i]);
                }
                free(records);
                break;
            } else if (choice == 2) {
                struct Record new_record;
                if (input_record(&new_record) != 0) {
                    break;
                }
                fseek(file, 0, SEEK_END);
                fwrite(&new_record, sizeof(struct Record), 1, file);
                fseek(file, 0, SEEK_END);
                long size = ftell(file);
                int num_records = size / sizeof(struct Record);
                struct Record *records = malloc(size);
                if (!records) {
                    perror("n/a");
                    fclose(file);
                    break;
                }
                fseek(file, 0, SEEK_SET);
                fread(records, sizeof(struct Record), num_records, file);
                qsort(records, num_records, sizeof(struct Record), compare_records);
                for (int i = 0; i < num_records; i++) {
                    print_record(&records[i]);
                }
                free(records);
                break;
            } else if (choice == -1) {
                break;
            } else {
                printf("n/a");
                break;
            }
        } while (choice != -1);
        fclose(file);
    }
    return 0;
}
