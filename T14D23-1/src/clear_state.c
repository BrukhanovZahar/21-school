#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} Record;

int compareDates(const Record *record, const int year, const int month, const int day) {
    int res = 0;
    if (record->year < year) {
        res = -1;
    } else if (record->year > year) {
        res = 1;
    } else if (record->month < month) {
        res = -1;
    } else if (record->month > month) {
        res = 1;
    } else if (record->day < day) {
        res = -1;
    } else if (record->day > day) {
        res = 1;
    }
    return res;
}

void print_record(const Record *record) {
    printf("%d %d %d %d %d %d %d %d\n", record->year, record->month, record->day, record->hour,
           record->minute, record->second, record->status, record->code);
}

void print_remaining_records(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        Record record;
        while (fread(&record, sizeof(Record), 1, file) == 1) {
            print_record(&record);
        }
        fclose(file);
    } else {
        printf("n/a");
    }
}

int main() {
    FILE *file, *tempFile;
    char tempFilename[] = "temp.dat";
    Record record;
    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;
    int found = 0;
    char filename[100] = "../";
    char tmp_path[100];
    scanf("%s", tmp_path);
    strcat(filename, tmp_path);
    file = fopen(filename, "rb");
    tempFile = fopen(tempFilename, "wb");
    if (file == NULL || tempFile == NULL) {
        printf("n/a");
        if (file != NULL) {
            fclose(file);
        }
        if (tempFile != NULL) {
            fclose(tempFile);
            remove(tempFilename);
        }
    } else {
        if (scanf("%d.%d.%d %d.%d.%d", &startDay, &startMonth, &startYear, &endDay, &endMonth, &endYear) !=
            6) {
            printf("n/a");
            fclose(file);
            fclose(tempFile);
        } else {
            while (fread(&record, sizeof(Record), 1, file) == 1) {
                if (compareDates(&record, startYear, startMonth, startDay) < 0 ||
                    compareDates(&record, endYear, endMonth, endDay) > 0) {
                    fwrite(&record, sizeof(Record), 1, tempFile);
                } else {
                    found = 1;
                }
            }
            fclose(file);
            fclose(tempFile);
            if (!found) {
                printf("n/a");
                remove(tempFilename);
            } else {
                if (remove(filename) == 0 && rename(tempFilename, filename) == 0) {
                    print_remaining_records(filename);
                } else {
                    printf("n/a");
                }
            }
        }
    }
    return 0;
}
