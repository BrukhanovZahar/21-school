#include "materials.h"
#include "modules.h"
// Работа с базой status_events

// Функция печатает все записи базы, считанные из файла
int print_events(FILE *ptr) {
    int is_error = 0;
    events rec;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, 0, SEEK_SET);
        fread(&rec, sizeof(events), 1, ptr);
        while (!feof(ptr)) {
            printf("%d %d %d %s %s\n", rec.event_id, rec.module_id, rec.status, rec.date, rec.time);
            fread(&rec, sizeof(events), 1, ptr);
        }
    }
    return is_error;
}

// Функция возвращает последний id в базе
int get_last_events_id(FILE *ptr) {
    int id = -1;
    if (ptr != NULL) {
        fseek(ptr, -sizeof(events), SEEK_END);
        fread(&id, sizeof(int), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return id;
}

// Функция проверяет находится ли id в допустимом диапазоне
int check_events_id(FILE *ptr, int id) {
    int res = 0;
    if ((id >= 0) && (id <= get_last_events_id(ptr))) res = 1;
    return res;
}

// Функция считывает строку от пользователя
char *get_str() {
    char *str = (char *)malloc(sizeof(char) * 10);
    int size = 0, k = 1;
    char c = ' ';
    scanf("%c", &c);
    if (c == '\n') scanf("%c", &c);
    while (c != '\n') {
        if (size > k * 10) {
            k++;
            char *tmp = (char *)realloc(str, sizeof(char) * 10 * k);
            if (tmp != NULL)
                str = tmp;
            else
                return NULL;
        }
        str[size++] = c;
        scanf("%c", &c);
    }
    str[size] = '\0';
    return str;
}

// Функция считывает дату от пользователя
int get_date(char *date_out) {
    int is_error = 0;
    char *str = get_str();
    int len = strlen(str);
    char *temp = NULL;
    int date[3];
    date[0] = 0;
    date[1] = 0;
    date[2] = 0;
    for (int i = 2; i >= 0; i--) {
        while (*str) {
            if (((*str >= '0') && (*str <= '9')) || (*str == '.')) {
                if (*str == '.') {
                    str++;
                    break;
                }
                date[i] *= 10;
                date[i] += *str - '0';
            } else {
                is_error = 1;
            }
            str++;
        }
    }
    if (!is_error) {
        if (date[2] > 31 || date[1] > 12 || date[0] == 0 || date[1] == 0 || date[2] == 0) {
            is_error = 1;
        }
    }
    if (is_error) {
        free(str - len);
    } else {
        temp = str - len;
        strcpy(date_out, temp);
    }
    if (temp != NULL) free(temp);
    return is_error;
}

// Функция считывает время от пользователя
int get_time(char *time_out) {
    int is_error = 0;
    char *str = get_str();
    int len = strlen(str);
    char *temp = NULL;
    int date[3];
    date[0] = 0;
    date[1] = 0;
    date[2] = 0;
    for (int i = 2; i >= 0; i--) {
        while (*str) {
            if (((*str >= '0') && (*str <= '9')) || (*str == ':')) {
                if (*str == ':') {
                    str++;
                    break;
                }
                date[i] *= 10;
                date[i] += *str - '0';
            } else {
                is_error = 1;
            }
            str++;
        }
    }
    if (!is_error) {
        if (date[2] > 23 || date[1] > 59 || date[0] > 59) {
            is_error = 1;
        }
    }
    if (is_error) {
        free(str - len);
    } else {
        temp = str - len;
        strcpy(time_out, temp);
    }
    printf("\ntime_error: %d\n", is_error);
    printf("\ntime  m_arr: %d %d %d\n", date[0], date[1], date[2]);
    if (temp != NULL) free(temp);
    return is_error;
}

// Функция собирает данные для новой записи у пользователя
events get_events_record(int id) {
    printf("Enter record (id: %d)\n", id);
    events rec;
    int input = 1;
    rec.event_id = id;
    rec.module_id = 5;
    do {
        printf("> module_id: ");
        if (scanf("%d", &(rec.module_id)) != 1) {
            printf("n/a\n");
        } else {
            input = 0;
        }
    } while (input);
    input = 1;
    do {
        printf("> status (0/1): ");
        if (scanf("%d", &(rec.status)) != 1) {
            printf("n/a\n");
        } else if (rec.status != 0 && rec.status != 1) {
            printf("n/a\n");
        } else {
            input = 0;
        }
    } while (input);
    input = 1;
    do {
        printf("> date (DD.MM.YYYY): ");
        input = get_date(rec.date);
    } while (input);
    input = 1;
    do {
        printf("> time (HH:MM:SS): ");
        input = get_time(rec.time);
    } while (input);
    return rec;
}

// Функция добавляет запись в конец файла
int add_events_record(FILE *ptr, events rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, 0, SEEK_END);
        fwrite(&rec, sizeof(events), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Функция удаляет запись с определенным id
int delete_events_record(FILE *ptr, int id) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        events rec;
        int i = id;
        fseek(ptr, (i + 1) * sizeof(events),
              SEEK_SET);  // устанавливаем указатель на следующую после удаляемой записи
        while (!feof(ptr)) {  // пока не достигнут конец файла сдвигаем все файлы на 1 назад
            fseek(ptr, (i + 1) * sizeof(events), SEEK_SET);
            if (fread(&rec, sizeof(events), 1, ptr) != 1) break;
            fseek(ptr, i * sizeof(events), SEEK_SET);
            rec.event_id--;
            fwrite(&rec, sizeof(events), 1, ptr);
            i++;
        }
        fseek(ptr, 0, SEEK_SET);
        truncate(events_fpath, i * sizeof(events));  // обрезаем файл для уменьшения его размера
    }
    return is_error;
}

// Функция вставляет запись в определенный id
int insert_events_record(FILE *ptr, int id, events new_rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        events rec;
        int i;
        fseek(ptr, -sizeof(events), SEEK_END);  // устанавливаем указатель на последнюю запись в файле
        fread(&i, sizeof(int), 1, ptr);  // считываем значение последнего id
        while (i >= id) {  // двигаем все данные до того места куда будем вставлять
            fseek(ptr, i * sizeof(events), SEEK_SET);
            fread(&rec, sizeof(events), 1, ptr);
            fseek(ptr, (i + 1) * sizeof(events), SEEK_SET);
            rec.event_id++;
            fwrite(&rec, sizeof(events), 1, ptr);
            i--;
        }
        fseek(ptr, (i + 1) * sizeof(events), SEEK_SET);
        fwrite(&new_rec, sizeof(events), 1, ptr);  // вставляем запись
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Функция меняет данные в записи с определенным id
int change_events_record(FILE *ptr, int id, events rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, id * sizeof(events), SEEK_SET);
        //        printf("%d %d %d %s %s\n", rec.event_id, rec.module_id, rec.status, rec.date, rec.time);
        fwrite(&rec, sizeof(events), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Функция выводит на экран определенное количество записей из базы
int select_events(FILE *ptr, int count) {
    int is_error = 0;
    events rec;
    int done = 0;
    int i = 0;
    if (count == 0) {
        print_events(ptr);
        done = 1;
    }
    if (ptr == NULL) {
        is_error = 1;
    } else if (!done) {
        fseek(ptr, 0, SEEK_SET);
        fread(&rec, sizeof(events), 1, ptr);
        while (!feof(ptr)) {
            if (i < count) {
                printf("%d %d %d %s %s\n", rec.event_id, rec.module_id, rec.status, rec.date, rec.time);
                fread(&rec, sizeof(events), 1, ptr);
                i++;
            } else {
                break;
            }
        }
    }
    return is_error;
}
