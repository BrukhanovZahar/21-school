#include "levels.h"
#include "materials.h"
#include "modules.h"
#include "shared.h"
#include "status_events.h"

void perform_task() {
    FILE *modules_db = fopen(modules_fpath, "rb+");
    FILE *levels_db = fopen(levels_fpath, "rb+");
    FILE *status_events_db = fopen(events_fpath, "rb+");
    if (!modules_db || !levels_db || !status_events_db) {
        printf("Error opening database files.\n");
    } else {
        int module_count = get_last_id(modules_db) + 1;
        fseek(modules_db, 0, SEEK_SET);
        fseek(status_events_db, 0, SEEK_SET);
        for (int id = 0; id < module_count; id++) {
            modules module;
            events event;
            fseek(modules_db, id * sizeof(modules), SEEK_SET);
            fseek(status_events_db, id * sizeof(event), SEEK_SET);
            fread(&module, sizeof(modules), 1, modules_db);
            fread(&event, sizeof(event), 1, status_events_db);
            if (module.id == 0) {
                delete_levels_record(levels_db, id);
                levels new_level;
                new_level.level = 1;
                new_level.cells_num = 1;
                new_level.pr_flag = 20;
                insert_levels_record(levels_db, 1, new_level);
                module.level = 1;
                module.cell = 1;
                change_modules_record(modules_db, id, module);
            }
            if (event.status == 1) {
                event.status = 0;
                module.flag = 1;
                change_events_record(status_events_db, id, event);
                change_modules_record(modules_db, id, module);
            }
        }
        fclose(modules_db);
        fclose(levels_db);
        fclose(status_events_db);
        printf("Task completed successfully.\n");
    }
}

int main() {
    int is_error = 0;
    int flag = 1;
    while (flag) {
        printf(
            "==============================\nMENU:\n"
            "  0. SELECT TABLE\n  1. SHOW TABLES\n  2. PERFORM TASK\n -1. EXIT\n"
            "==============================\n");
        int choice = get_choice(-1, 2);
        switch (choice) {
            case 0:
                printf("Choose the table:\n");
                printf("  0. MODULES\n  1. LEVELS\n  2. EVENTS\n");
                choice = get_choice(0, 2);
                if (choice == 0) is_error = modules_control();
                if (choice == 1) is_error = levels_control();
                if (choice == 2) is_error = events_control();
                break;
            case 1:
                is_error = show_tables();
                break;
            case 2:
                perform_task();
                break;
            case -1:
                flag = 0;
                break;
        }
        if (is_error) {
            flag = 0;
            printf("Error\n");
        }
    }
    return 0;
}
