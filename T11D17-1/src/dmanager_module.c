#include "dmanager_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

int main() {
    struct door doors[DOORS_COUNT];
    initialize_doors(doors);
    sort_doors(doors);
    close_doors(doors);
    output_doors(doors);
    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
    srand(time(0));
    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void sort_doors(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT; ++i) {
        for (int j = i; j > 0 && doors[j - 1].id > doors[j].id; --j) {
            struct door x = doors[j - 1];
            doors[j - 1] = doors[j];
            doors[j] = x;
        }
    }
}

void close_doors(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT; ++i) {
        doors[i].status = 0;
    }
}

void output_doors(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT - 1; ++i) {
        printf("%d, %d\n", doors[i].id, doors[i].status);
    }
    printf("%d, %d", doors[DOORS_COUNT - 1].id, doors[DOORS_COUNT - 1].status);
}