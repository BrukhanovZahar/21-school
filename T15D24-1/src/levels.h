#ifndef LEVELS_H
#define LEVELS_H

#include "materials.h"

int print_levels(FILE* ptr);
levels get_levels_record();
int check_levels_id(FILE* ptr, int id);
int add_levels_record(FILE* ptr, levels rec);
int delete_levels_record(FILE* ptr, int id);
int insert_levels_record(FILE* ptr, int id, levels new_rec);
int change_levels_record(FILE* ptr, int id, levels rec);
int select_levels(FILE* ptr, int id);

#endif
