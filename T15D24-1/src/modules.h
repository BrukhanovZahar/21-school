#ifndef MODULES_H
#define MODULES_H

#include "materials.h"

int check_modules_id(FILE* ptr, int id);
int get_last_id(FILE* ptr);
int print_modules(FILE* ptr);
void get_name(char* name);
modules get_modules_record(int id);
int add_modules_record(FILE* ptr, modules rec);
int delete_modules_record(FILE* ptr, int id);
int change_modules_record(FILE* ptr, int id, modules rec);
int insert_modules_record(FILE* ptr, int id, modules rec);
int select_modules(FILE* ptr, int count);

#endif  // SRC_MODULES_H_
