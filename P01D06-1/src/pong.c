#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define PADDLE_SIZE 3
#define BALL_SIZE 1

// Отрисовка интерфейса
void drawField(int ballX, int ballY, int player1Y, int player2Y, int score1, int score2) {
    // Вывод счета
    printf("Player 1: %d                                Player 2: %d\n", score1, score2);

    // Верхняя рамка
    for (int i = 0; i < FIELD_WIDTH + 2; i++) {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < FIELD_HEIGHT; i++) {
        printf("|");  // Левая рамка
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (j == FIELD_WIDTH / 2) {
                printf("|");  // Серединая линия
            }
            if (i == ballY && j == ballX) {
                printf("o");  // Отрисовка мяча
            } else if ((j > 1 && j < PADDLE_SIZE && i >= player1Y && i < player1Y + PADDLE_SIZE) ||
                       (j < FIELD_WIDTH - 2 && j >= FIELD_WIDTH - PADDLE_SIZE && i >= player2Y &&
                        i < player2Y + PADDLE_SIZE)) {
                printf("|");  // Отрисовка ракеток
            } else {
                printf(" ");  // Отрисовка пустых мест
            }
        }
        printf("|");  // Правая рамка
        printf("\n");
    }

    // Нижняя рамка
    for (int i = 0; i < FIELD_WIDTH + 2; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    int ballX = FIELD_WIDTH / 2 - 1;  // Положение мяча по X
    int ballY = FIELD_HEIGHT / 2;     // Положение мяча по Y
    int ballDirX = -1;                // Направление движения мяча по X
    int ballDirY = 1;                 // Направление движения мяча по Y

    int player1Y = FIELD_HEIGHT / 2;  // Положение левой ракетки по Y
    int player2Y = FIELD_HEIGHT / 2;  // Положение правой ракетки по Y

    int player1Score = 0;
    int player2Score = 0;

    int isGameOver = 0;

    while (!isGameOver) {
        drawField(ballX, ballY, player1Y, player2Y, player1Score, player2Score);

        // Ввод действий
        char player1Move, player2Move, enter;
        printf("Enter player's motions: ");
        scanf("%c%c%c", &player1Move, &player2Move, &enter);
        while (!((player1Move == 'a' || player1Move == 'z' || player1Move == 32) &&
                 (player2Move == 'k' || player2Move == 'm' || player2Move == 32) && enter == 10)) {
            printf("Error. Please enter again: ");
            scanf("%c%c%c", &player1Move, &player2Move, &enter);
        }

        // Управление ракетками игроков
        if (player1Move == 'a' && player1Y > 0 && player1Y <= FIELD_HEIGHT) {
            player1Y--;
        } else if (player1Move == 'z' && player1Y < FIELD_HEIGHT - PADDLE_SIZE && player1Y >= 0) {
            player1Y++;
        }
        if (player2Move == 'k' && player2Y > 0 && player2Y <= FIELD_HEIGHT) {
            player2Y--;
        } else if (player2Move == 'm' && player2Y < FIELD_HEIGHT - PADDLE_SIZE && player2Y >= 0) {
            player2Y++;
        }
        // Движения мяча
        ballX += ballDirX;
        ballY += ballDirY;

        // Проверка столкновения с верхней и нижней стенкой
        if (ballY <= 0 || ballY >= FIELD_HEIGHT - BALL_SIZE) {
            ballDirY = -ballDirY;
        }

        // Проверка столкновения с ракетками
        if ((ballX == PADDLE_SIZE && ballY >= player1Y && ballY < player1Y + PADDLE_SIZE) ||
            (ballX == FIELD_WIDTH - PADDLE_SIZE - BALL_SIZE && ballY >= player2Y &&
             ballY < player2Y + PADDLE_SIZE) ||
            (ballX == PADDLE_SIZE && (ballY + 1 == player1Y || ballY == player1Y + PADDLE_SIZE)) ||
            (ballX == FIELD_WIDTH - PADDLE_SIZE - BALL_SIZE &&
             (ballY + 1 == player2Y || ballY == player2Y + PADDLE_SIZE))) {
            ballDirX = -ballDirX;
        }

        // Проверка забития гола
        if (ballX <= 0) {
            player2Score++;
            if (player2Score >= 21) {
                printf("Congratulations! Player 2 is winner!\n");
                isGameOver = 1;
            }
            ballX = FIELD_WIDTH / 2 - 1;
            ballY = FIELD_HEIGHT / 2;
        } else if (ballX >= FIELD_WIDTH - BALL_SIZE) {
            player1Score++;
            if (player1Score >= 21) {
                printf("Congratulations! Player 1 is winner!\n");
                isGameOver = 1;
            }
            ballX = FIELD_WIDTH / 2;
            ballY = FIELD_HEIGHT / 2;
        }
    }

    return 0;
}
