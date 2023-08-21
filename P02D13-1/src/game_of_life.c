#include <stdio.h>
#include <unistd.h>

#define MAX_PREVIOUS_STATES 10
#define WIDTH 80
#define HEIGHT 25
#define ALIVE '*'
#define DEAD '-'

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Функция очищает содержимое терминала
void clear_screen() {
    printf("\033[H\033[J");
    fflush(stdout);  // Очистка буфера вывода, чтобы предыдущая команда выполнялась
    // сразу
}

// Функция скрывает курсор
void hide_cursor() {
    printf("\033[?25l");
    fflush(stdout);
}

// Функция возвращает курсор
void show_cursor() {
    printf("\033[?25h");
    fflush(stdout);
}

// Функция для вывода матрицы в терминал
void print_board(char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == ALIVE) {
                printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, board[i][j]);
            } else if (board[i][j] == DEAD) {
                printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, board[i][j]);
            } else {
                printf("%c", board[i][j]);
            }
        }
        printf("\n");
    }
    fflush(stdout);  // Очистка буфера вывода, чтобы вывод символов выполнялся сразу
}

// Считаем количество живых соседей у клетки
int count_neighbors(char board[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    // Проходимся по всем клеткам вокруг (включая ту, у которой считаем количество
    // соседей)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Не учитываем клетку, у которой считаем количество соседей
            if (i == 0 && j == 0) {
                continue;
            }
            // Считаем координаты соседней клетки, учитывая замкнутость поля
            int nx = (x + i + HEIGHT) % HEIGHT;
            int ny = (y + j + WIDTH) % WIDTH;
            // Проверяем состояние клетки по координатам
            if (board[nx][ny] == ALIVE) {
                count++;
            }
        }
    }
    return count;
}

// Функция, которая высчитывает процесс эволюции
void evolve(char board[HEIGHT][WIDTH]) {
    char new_board[HEIGHT][WIDTH];  // Создаем массив в котором будем хранить новые
    // состояния для каждой клетки

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = count_neighbors(board, i, j);

            // Заполняем новый массив по условиям игры
            if (board[i][j] == ALIVE) {
                if (neighbors == 2 || neighbors == 3)
                    new_board[i][j] = ALIVE;
                else
                    new_board[i][j] = DEAD;
            } else {
                if (neighbors == 3)
                    new_board[i][j] = ALIVE;
                else
                    new_board[i][j] = DEAD;
            }
        }
    }

    // Приравниваем элементы старого массива к новому
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = new_board[i][j];
        }
    }
}

// Функция проверяет наличие клеток на игровом поле
int is_board_empty(char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == ALIVE) {
                return 0;  // если хоть одна клетка жива возвращаем 0
            }
        }
    }
    return 1;  // если все клетки мертвые возвращаем 1
}

// Функция сравнивает два состояния игрового поля
int is_identical(char board1[HEIGHT][WIDTH], char board2[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board1[i][j] != board2[i][j]) {
                return 0;  //  Если хоть один элемент в массиве не совпадает
                //  возвращаем 0
            }
        }
    }
    return 1;  // Если массивы совпадают возвращаем 1
}

// Функция для инициализации матрицы начальным состоянием игры
int init_matrix(char board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            char cell;
            if (scanf(" %c", &cell) != 1) {
                printf("Ошибка чтения.\n");
                return 1;
            }
            if (cell == ALIVE || cell == DEAD) {
                board[i][j] = cell;
            } else {
                printf("Неверный символ: %c", cell);
                return 1;
            }
        }
    }
    return 0;
}

int init_speed(int *speed) {
    printf("Введите скорость от 50000 до 1000000: ");
    if (scanf("%d", speed) != 1) {
        printf("Неверная скорость.\n");
        return 1;
    }
    if (*speed < 50000 || *speed > 1000000) {
        printf("Неверная скорость.\n");
        return 1;
    }
    return 0;
}

int main() {
    char board[HEIGHT][WIDTH] = {0};  // Матрица текущего состояния игры
    char previous_boards[MAX_PREVIOUS_STATES][HEIGHT][WIDTH];  // Трехмерный массив для хранения предыдущих
    // состояний игры
    int step = 0;     // Поколение игры
    int stopped = 0;  // Окончание игры
    int speed;
    int is_redirect = 0;  // Переключение потока ввода
    // Инициализация значений матрицы из stdin
    int num = init_matrix(board);
    // Возвращения потока ввода в консоль
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        is_redirect = 1;
    }
    int count = init_speed(&speed);
    hide_cursor();  // Скрыли курсор
    // Цикл продолжается пока игра не должна закончиться
    while (stopped != 1 && num != 1 && count != 1 && is_redirect != 1) {
        clear_screen();  // Очищаем экран перед каждым следующим состоянием игры
        print_board(board);  // Отрисовка текущего состояния игры
        int identical = 0;  // Показывает равенство нескольких последовательных состояний
        int compare_steps = (step > 10) ? 10 : step;  // Сравниваем с 10 предыдущими состояниями
        for (int i = 0; i < compare_steps; i++) {
            if (is_identical(board, previous_boards[i])) {
                identical = 1;  // Если найдено идентичное состояние меняем флаг и
                // выходим из цикла
                break;
            }
        }

        // Если поле мертвое или найдено идентичное состояние завершаем игру
        if (is_board_empty(board) == 1 || identical == 1) {
            stopped = 1;
        } else {
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    previous_boards[step % 10][i][j] =
                        board[i][j];  // Сохраняем текущее состояние в массив последних
                    // состояний
                }
            }
            evolve(board);
            step++;
            usleep(speed);  // Задержка перед следующим шагом
        }

        if (is_board_empty(board) == 1) {
            printf("Игра завершена: на поле не осталось живых клеток.\n");
        } else if (identical == 1) {
            printf("Игра завершена: достигнут цикл повторяющейся конфигурации.\n");
        }
    }
    show_cursor();  // Вернули курсор
    return 0;
}
