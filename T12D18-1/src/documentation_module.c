#include "documentation_module.h"

int validate(char *data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int *check_available_documentation_module(int (*validate)(char *), int document_count, ...) {
    int *data = (int *)malloc(document_count * sizeof(int));
    va_list args;
    va_start(args, document_count);
    for (int i = 0; i < document_count; ++i) {
        char *document_name = va_arg(args, char *);
        data[i] = validate(document_name);
    }
    va_end(args);
    return data;
}

void output_availability(const int *avail, int doc_count, ...) {
    va_list args;
    va_start(args, doc_count);
    for (int i = 0; i < doc_count; i++) {
        char *document_name = va_arg(args, char *);
        printf("[%-*s : %s]\n", 15, document_name, avail[i] ? "available" : "unavailable");
    }
    va_end(args);
}