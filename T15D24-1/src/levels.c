#include "levels.h"
// Работа с базой levels

// Функция печатает все записи базы, считанные из файла
int print_levels(FILE *ptr) {
    int is_error = 0;
    levels rec;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        printf("LEVELS\n");
        fseek(ptr, 0, SEEK_SET);
        fread(&rec, sizeof(levels), 1, ptr);
        while (!feof(ptr)) {
            printf("%d %d %d\n", rec.level, rec.cells_num, rec.pr_flag);
            fread(&rec, sizeof(levels), 1, ptr);
        }
    }
    return is_error;
}

// Функция получает данные для новой записи от пользователя
levels get_levels_record() {
    levels rec;
    while (1) {
        printf("Enter: level, number of cells on level, protection flag\n");
        if (scanf("%d %d %d", &(rec.level), &(rec.cells_num), &(rec.pr_flag)) == 3) {
            break;
        } else {
            printf("n/a\n");
        }
    }
    return rec;
}

// Функция проверяет находится ли id в допустимом диапазоне
int check_levels_id(FILE *ptr, int id) {
    int res = 0;
    fseek(ptr, 0, SEEK_END);
    int size = ftell(ptr) / sizeof(levels);  // количество записей в файле
    if ((id >= 0) && (id < size)) res = 1;
    return res;
}

// Функция добавляет новую запись в базу в конец файла
int add_levels_record(FILE *ptr, levels rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, 0, SEEK_END);
        fwrite(&rec, sizeof(levels), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Функция удаляет запись с заданным id
int delete_levels_record(FILE *ptr, int id) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        levels rec;
        int i = id;
        fseek(ptr, (i + 1) * sizeof(levels),
              SEEK_SET);  // устанавливаем указатель на следующую после удаляемой записи
        while (!feof(ptr)) {  // пока не достигнут конец файла сдвигаем все файлы на 1 назад
            fseek(ptr, (i + 1) * sizeof(levels), SEEK_SET);
            if (fread(&rec, sizeof(levels), 1, ptr) != 1) break;
            fseek(ptr, i * sizeof(levels), SEEK_SET);
            fwrite(&rec, sizeof(levels), 1, ptr);
            i++;
        }
        fseek(ptr, 0, SEEK_SET);
        truncate(levels_fpath, i * sizeof(levels));  // обрезаем файл для уменьшения его размера
    }
    return is_error;
}

// Функция добавляет запись на место id
int insert_levels_record(FILE *ptr, int id, levels new_rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        levels rec;
        int i;
        fseek(ptr, -sizeof(levels), SEEK_END);  // устанавливаем указатель на полседнюю запись в файле
        fread(&i, sizeof(int), 1, ptr);  // считываем значение последнего id
        while (i >= id) {  // двигаем все данные до того места куда будем вставлять
            fseek(ptr, i * sizeof(levels), SEEK_SET);
            fread(&rec, sizeof(levels), 1, ptr);
            fseek(ptr, (i + 1) * sizeof(levels), SEEK_SET);
            fwrite(&rec, sizeof(levels), 1, ptr);
            i--;
        }
        fseek(ptr, (i + 1) * sizeof(levels), SEEK_SET);
        fwrite(&new_rec, sizeof(levels), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Функция изменяет данные в базе с определенным id
int change_levels_record(FILE *ptr, int id, levels rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, id * sizeof(levels), SEEK_SET);
        fwrite(&rec, sizeof(levels), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Выводит заданное количество записей базы
int select_levels(FILE *ptr, int count) {
    int is_error = 0;
    int i = 0;
    int done = 0;
    levels rec;
    if (count == 0) {
        print_levels(ptr);
        done = 1;
    }
    if (ptr == NULL) {
        is_error = 1;
    } else if (!done) {
        printf("LEVELS\n");
        fseek(ptr, 0, SEEK_SET);
        fread(&rec, sizeof(levels), 1, ptr);
        while (!feof(ptr)) {
            if (i < count) {
                printf("%d %d %d\n", rec.level, rec.cells_num, rec.pr_flag);
                fread(&rec, sizeof(levels), 1, ptr);
                i++;
            } else {
                break;
            }
        }
    }
    return is_error;
}