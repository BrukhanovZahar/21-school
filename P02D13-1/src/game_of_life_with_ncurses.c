#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_PREVIOUS_STATES 10
#define WIDTH 80
#define HEIGHT 25
#define ALIVE '*'
#define DEAD '-'

// Инициализация ncurses и настроек
void initialize_ncurses() {
    initscr();              // Инициализация ncurses
    cbreak();               // Отключение буферизованного ввода
    noecho();               // Отключение автоотображения ввода
    nodelay(stdscr, TRUE);  // Немедленное чтение ввода
    keypad(stdscr, TRUE);   // Включение обработки специальных клавиш
    curs_set(0);            // Скрыть курсор
    start_color();          // Инициализация цветовых пар
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Цвет для живых клеток (зеленый на черном)
    init_pair(2, COLOR_RED, COLOR_BLACK);  // Цвет для мертвых клеток (красный на черном)
}

// Завершение работы с ncurses
void cleanup_ncurses() {
    curs_set(1);  // Показать курсор перед завершением программы
    endwin();     // Завершение работы с ncurses
}

// Функция для вывода матрицы в терминал
void print_board(char board[HEIGHT][WIDTH]) {
    clear();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == ALIVE) {
                attron(COLOR_PAIR(1));  // Задаем цвет для живых клеток
                mvaddch(i, j, ALIVE);
                attroff(COLOR_PAIR(1));
            } else if (board[i][j] == DEAD) {
                attron(COLOR_PAIR(2));  // Задаем цвет для мертвых клеток
                mvaddch(i, j, DEAD);
                attroff(COLOR_PAIR(2));
            } else {
                mvaddch(i, j, board[i][j]);
            }
        }
    }
    refresh();
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

// Функция для изменения скорости игры
void process_input(int *speed) {
    int ch = getch();
    if (ch == KEY_UP && *speed > 80000) {
        (*speed) -= 70000;  // Увеличить скорость

    } else if (ch == KEY_DOWN && *speed < 500000) {
        (*speed) += 70000;  // Уменьшить скорость
    }
    if (*speed > 500000) {
        *speed = 500000;
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

// Функция вывода завершающего экрана игры
void showEndOfGame(int is_empty, int identical) {
    clear();
    if (is_empty == 1) {
        mvprintw(HEIGHT / 2, WIDTH / 2 - 25,
                 "The game is over: there are no living cells left on the field.");
    } else if (identical == 1) {
        mvprintw(HEIGHT / 2, WIDTH / 2 - 25,
                 "The game is over: a repeating configuration cycle has been reached.");
    }
    mvprintw(HEIGHT / 2 + 2, WIDTH / 2 - 15, "Press 'q' to quit.");
    refresh();
    // Ожидание нажатия клавиши 'q'
    while (getch() != 'q') {
    }
}

int main() {
    initialize_ncurses();
    char board[HEIGHT][WIDTH] = {0};  // Матрица текущего состояния игры
    char previous_boards[MAX_PREVIOUS_STATES][HEIGHT][WIDTH];  // Трехмерный массив для хранения предыдущих
    // состояний игры
    int step = 0;         // Поколение игры
    int stopped = 0;      // Окончание игры
    int is_redirect = 0;  // Переключение потока ввода
    int identical = 0;  // Показывает равенство нескольких последовательных состояний
    int speed = 500000;  // Начальная скорость 0.5 секунды
    // Инициализация значений матрицы из stdin
    int num = init_matrix(board);
    // Возвращения потока ввода в консоль
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        is_redirect = 1;
    }
    // Цикл продолжается пока игра не должна закончиться
    while (stopped == 0 && num != 1 && is_redirect != 1) {
        print_board(board);  // Отрисовка текущего состояния игры

        identical = 0;                                // Сбрасываем флаг
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
            process_input(&speed);
            step++;
            usleep(speed);  // Задержка перед следующим шагом
        }
    }
    showEndOfGame(is_board_empty(board), identical);
    cleanup_ncurses();
    return 0;
}
