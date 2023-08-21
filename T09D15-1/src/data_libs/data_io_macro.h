#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

#include <stdio.h>

#define INIT_ARRAY(data, n, type)   \
    for (int i = 0; i < n; ++i) {   \
        scanf("%" #type, &data[i]); \
    }

#define OUTPUT_ARRAY(data, n, type)     \
    for (int i = 0; i < n - 1; ++i) {   \
        printf("%" #type " ", data[i]); \
    }                                   \
    printf("%" #type, data[n - 1]);

#define input(data, n) INIT_ARRAY(data, n, lf)
#define output(data, n) OUTPUT_ARRAY(data, n, lf)

#endif
