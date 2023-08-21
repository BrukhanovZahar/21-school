#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include "materials.h"

int print_events(FILE* ptr);
int get_last_events_id(FILE* ptr);
int check_events_id(FILE* ptr, int id);
events get_events_record(int id);
int add_events_record(FILE* ptr, events rec);
int delete_events_record(FILE* ptr, int id);
int insert_events_record(FILE* ptr, int id, events rec);
int change_events_record(FILE* ptr, int id, events rec);
int select_events(FILE* ptr, int count);
char* get_str();
int get_date(char* date);
int get_time(char* time);

#endif
