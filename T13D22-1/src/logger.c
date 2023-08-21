#include "logger.h"

void log_init(const char *filename, FILE **log_file) {
    *log_file = fopen(filename, "a");
    if (!*log_file) {
        printf("n/a");
        exit(EXIT_FAILURE);
    }
}

void logcat(FILE *log_file, enum log_level level, const char *message) {
    const char *level_strings[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    time_t current_time;
    struct tm *time_info;
    char time_string[20];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
    fprintf(log_file, "[%s] %s: %s\n", time_string, level_strings[level], message);
}

void log_close(FILE *log_file) {
    if (log_file) {
        fclose(log_file);
    }
}
