#include "door_struct.h"
#ifndef DMANAGER_MODULE_H
#define DMANAGER_MODULE_H
#define DOORS_COUNT 15
#define MAX_ID_SEED 10000
void initialize_doors(struct door* doors);
void sort_doors(struct door* doors);
void close_doors(struct door* doors);
void output_doors(struct door* doors);
#endif
