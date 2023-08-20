#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define PADDLE_SIZE 3
#define BALL_SIZE 1
#define PADDLE_CHAR '|'
#define BALL_CHAR 'o'

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25

int leftPaddleY = FIELD_HEIGHT / 2;
int rightPaddleY = FIELD_HEIGHT / 2;
int ballX = FIELD_WIDTH / 2;
int ballY = FIELD_HEIGHT / 2;
int ballSpeedX = -1;
int ballSpeedY = 1;

int leftScore = 0;
int rightScore = 0;

void drawField() {
    clear();

    // Отрисовка верхней границы поля
    mvhline(0, 0, '#', FIELD_WIDTH);

    // Отрисовка вертикальной полоски посередине поля
    mvvline(0, FIELD_WIDTH / 2, '|', FIELD_HEIGHT);

    // Отрисовка нижней границы поля
    mvhline(FIELD_HEIGHT - 1, 0, '#', FIELD_WIDTH);

    // Рисуем ракетки
    for (int i = 0; i < PADDLE_SIZE; i++) {
        mvprintw(leftPaddleY + i, 2, "%c", PADDLE_CHAR);
        mvprintw(rightPaddleY + i, FIELD_WIDTH - 3, "%c", PADDLE_CHAR);
    }

    // Рисуем мяч
    mvprintw(ballY, ballX, "%c", BALL_CHAR);

    // Выводим счет
    mvprintw(0, FIELD_WIDTH / 2 - 5, "Score: %d - %d", leftScore, rightScore);

    // Обновляем экран
    refresh();
}

void processInput() {
    int paddleMove = getch();

    if (paddleMove == 'a' && leftPaddleY > 1) {
        leftPaddleY--;
    } else if (paddleMove == 'z' && leftPaddleY < FIELD_HEIGHT - PADDLE_SIZE - 1) {
        leftPaddleY++;
    }

    if (paddleMove == 'k' && rightPaddleY > 1) {
        rightPaddleY--;
    } else if (paddleMove == 'm' && rightPaddleY < FIELD_HEIGHT - PADDLE_SIZE - 1) {
        rightPaddleY++;
    }
}

void updateBall() {
    // Предполагаем следующие координаты мяча
    int nextBallX = ballX + ballSpeedX;
    int nextBallY = ballY + ballSpeedY;

    // Проверяем столкновение с верхней и нижней границами поля
    if (nextBallY <= 1 && ballSpeedY < 0) {
        ballSpeedY = -ballSpeedY;
    }
    if (nextBallY >= FIELD_HEIGHT - BALL_SIZE - 1 && ballSpeedY > 0) {
        ballSpeedY = -ballSpeedY;
    }

    // Проверяем столкновение с ракетками
    if ((nextBallX == 3 && nextBallY >= leftPaddleY && nextBallY <= leftPaddleY + PADDLE_SIZE - 1) ||
        (nextBallX == FIELD_WIDTH - 4 && nextBallY >= rightPaddleY &&
         nextBallY <= rightPaddleY + PADDLE_SIZE - 1)) {
        // Изменяем направление мяча отскока по горизонтали
        ballSpeedX = -ballSpeedX;

        // Изменяем направление мяча отскока по вертикали, основываясь на центре ракетки
        if (nextBallX == 3) {                // попали в левую ракетку
            if (nextBallY == leftPaddleY) {  // попали в верхнюю часть
                if (ballSpeedY == 0) {       // если мяч не двигается вертикально
                    ballSpeedY--;
                }
            } else if (nextBallY == leftPaddleY + 1) {  // попали в середину
                ballSpeedY = ballSpeedY / 2;
            } else if (nextBallY == leftPaddleY + 2) {  // попали в нижнюю часть
                if (ballSpeedY == 0) {  // если мяч не двигается вертикально
                    ballSpeedY++;
                }
            }
        } else {                              // попали в правую ракетку
            if (nextBallY == rightPaddleY) {  // попали в верхнюю часть
                if (ballSpeedY == 0) {  // если мяч не двигается вертикально
                    ballSpeedY--;
                }
            } else if (nextBallY == rightPaddleY + 1) {  // попали в середину
                ballSpeedY = ballSpeedY / 2;
            } else if (nextBallY == rightPaddleY + 2) {  // попали в нижнюю часть
                if (ballSpeedY == 0) {  // если мяч не двигается вертикально
                    ballSpeedY++;
                }
            }
        }
    }

    // Проверяем забитие гола
    if (nextBallX <= 1) {
        rightScore++;
        ballX = FIELD_WIDTH / 2;
        ballY = FIELD_HEIGHT / 2;
        int randomNum = rand() % 3;  // Генерируем случайное число от 0 до 2
        randomNum--;
        ballSpeedX = 1;
        ballSpeedY = randomNum;
    } else if (nextBallX >= FIELD_WIDTH - 2) {
        leftScore++;
        ballX = FIELD_WIDTH / 2;
        ballY = FIELD_HEIGHT / 2;
        int randomNum = rand() % 3;  // Генерируем случайное число от 0 до 2
        randomNum--;
        ballSpeedX = -1;
        ballSpeedY = randomNum;
    } else {
        // Если мяч не столкнулся с границами, обновляем его координаты
        ballX = nextBallX;
        ballY = nextBallY;
    }
}

void showWinner() {
    clear();
    if (leftScore >= 21) {
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 15, "Player on the left wins!");
    } else if (rightScore >= 21) {
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 15, "Player on the right wins!");
    }
    mvprintw(FIELD_HEIGHT / 2 + 2, FIELD_WIDTH / 2 - 15, "Press 'q' to quit.");
    refresh();

    // Ожидаем, пока игрок нажмет клавишу 'q'
    while (getch() != 'q') {
        // Ждем нажатия клавиши 'q'
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while (leftScore < 21 && rightScore < 21) {
        processInput();
        updateBall();
        drawField();
        usleep(100000);
    }

    // Игра закончилась, показываем победителя
    showWinner();

    // Завершение работы с ncurses
    endwin();

    return 0;
}
