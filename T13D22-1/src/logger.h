#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum log_level { DEBUG, INFO, WARNING, ERROR };

void log_init(const char *filename, FILE **log_file);

void logcat(FILE *log_file, enum log_level level, const char *message);

void log_close(FILE *log_file);

#endif
