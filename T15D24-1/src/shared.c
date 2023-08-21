#include "shared.h"

#include "levels.h"
#include "materials.h"
#include "modules.h"
#include "status_events.h"

int get_choice(int gap1, int gap2) {
    int num;
    printf("> ");
    while (1) {
        if (scanf("%d", &num) != 1)
            printf("n/a\n");
        else if ((num > gap2) || (num < gap1))
            printf("n/a\n");
        else
            break;
    }
    return num;
}

int show_tables() {
    int is_error = 0;
    FILE *mptr = fopen(modules_fpath, "rb");
    FILE *lptr = fopen(levels_fpath, "rb");
    FILE *eptr = fopen(events_fpath, "rb");
    if ((mptr == NULL) || (lptr == NULL) || (eptr == NULL)) {
        is_error = 1;
    } else {
        printf("MODULES:\n");
        print_modules(mptr);
        printf("=======================\nLEVELS:\n");
        print_levels(lptr);
        printf("=======================\nEVENTS:\n");
        print_events(eptr);
        fclose(mptr);
        fclose(lptr);
        fclose(eptr);
    }
    return is_error;
}

void print_menu(const char *table_name) {
    printf(
        "==============================\n"
        "    CURRENT TABLE: %7s\n"
        "  0. Show all records\n  1. Add record\n  2. Insert record\n"
        "  3. Update record\n  4. Delete record\n  5. Select record\n"
        "  -1. BACK\n"
        "==============================\n",
        table_name);
}

int modules_control() {
    int is_error = 0;
    int id;
    int flag = 1;
    modules rec;
    FILE *ptr = fopen(modules_fpath, "r+b");
    while (flag) {
        print_menu("MODULES");
        int choice = get_choice(-1, 5);
        switch (choice) {
            case 0:
                print_modules(ptr);
                break;
            case 1:
                id = get_last_id(ptr);
                rec = get_modules_record(id + 1);
                is_error = add_modules_record(ptr, rec);
                print_modules(ptr);
                break;
            case 2:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_modules_id(ptr, id)) {
                    rec = get_modules_record(id);
                    is_error = insert_modules_record(ptr, id, rec);
                    print_modules(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 3:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_modules_id(ptr, id)) {
                    rec = get_modules_record(id);
                    is_error = change_modules_record(ptr, id, rec);
                    print_modules(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 4:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_modules_id(ptr, id)) {
                    delete_modules_record(ptr, id);
                    print_modules(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 5:
                printf("> Specify records count to output (0 for all): ");
                id = get_choice(0, 1000000);
                select_modules(ptr, id);
                break;
            case -1:
                flag = 0;
                break;
        }
        if (is_error) flag = 0;
    }
    return is_error;
}

int levels_control() {
    int is_error = 0;
    int id;
    int flag = 1;
    levels rec;
    FILE *ptr = fopen(levels_fpath, "r+b");
    while (flag) {
        print_menu("LEVELS");
        int choice = get_choice(-1, 5);
        switch (choice) {
            case 0:
                print_levels(ptr);
                break;
            case 1:
                rec = get_levels_record();
                is_error = add_levels_record(ptr, rec);
                print_levels(ptr);
                break;
            case 2:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_levels_id(ptr, id)) {
                    rec = get_levels_record();
                    is_error = insert_levels_record(ptr, id, rec);
                    print_levels(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 3:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_levels_id(ptr, id)) {
                    rec = get_levels_record();
                    is_error = change_levels_record(ptr, id, rec);
                    print_levels(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 4:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_levels_id(ptr, id)) {
                    is_error = delete_levels_record(ptr, id);
                    print_levels(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 5:
                printf("> Specify records count to output (0 for all): ");
                id = get_choice(0, 1000000);
                select_levels(ptr, id);
                break;
            case -1:
                flag = 0;
                break;
        }
        if (is_error) flag = 0;
    }
    return is_error;
}

int events_control() {
    int is_error = 0;
    int id = 0;
    int flag = 1;
    events rec;
    FILE *ptr = fopen(events_fpath, "r+b");
    while (flag) {
        print_menu("EVENTS");
        int choice = get_choice(-1, 5);
        switch (choice) {
            case 0:
                print_events(ptr);
                break;
            case 1:
                id = get_last_events_id(ptr);
                id++;
                rec = get_events_record(id);
                is_error = add_events_record(ptr, rec);
                print_events(ptr);
                break;
            case 2:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_events_id(ptr, id)) {
                    rec = get_events_record(id);
                    is_error = insert_events_record(ptr, id, rec);
                    print_events(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 3:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_events_id(ptr, id)) {
                    rec = get_events_record(id);
                    is_error = change_events_record(ptr, id, rec);
                    print_events(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 4:
                printf("Which one?\n");
                id = get_choice(-1000000, 1000000);
                if (check_events_id(ptr, id)) {
                    is_error = delete_events_record(ptr, id);
                    print_events(ptr);
                } else {
                    printf("Doesn't exist\n");
                }
                break;
            case 5:
                printf("> Specify records count to output (0 for all): ");
                id = get_choice(0, 1000000);
                select_events(ptr, id);
                break;
            case -1:
                flag = 0;
                break;
        }
        if (is_error) flag = 0;
    }
    return is_error;
}