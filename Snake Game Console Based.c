#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 60
#define HEIGHT 30

int headX, headY, foodX, foodY;
int direction = 0;  
int gameOver = 0, score = 0;

int tailX[200], tailY[200];
int tailLength = 0;

void setup() {
    headX = WIDTH / 2;
    headY = HEIGHT / 2;

    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;

    score = 0;
    gameOver = 0;
}

void draw() {
    system("cls");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("*");
            }
            else if (i == headY && j == headX) {
                printf("@");
            }
            else if (i == foodY && j == foodX) {
                printf("o");
            }
            else {
                int printed = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tailY[k] == i && tailX[k] == j) {
                        printf("O");
                        printed = 1;
                        break;
                    }
                }
                if (!printed) printf(" ");
            }

        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    if (kbhit()) {
        switch (getch()) {
            case 'w':
                if (direction != 2) direction = 1;
                break;
            case 's':
                if (direction != 1) direction = 2;
                break;
            case 'a':
                if (direction != 4) direction = 3;
                break;
            case 'd':
                if (direction != 3) direction = 4;
                break;
        }
    }
}

void logic() {

    for (int i = tailLength - 1; i > 0; i--) {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    if (tailLength > 0) {
        tailX[0] = headX;
        tailY[0] = headY;
    }

    switch (direction) {
        case 1: headY--; break;
        case 2: headY++; break;
        case 3: headX--; break;
        case 4: headX++; break;
    }

    if (headX == 0 || headX == WIDTH - 1 || headY == 0 || headY == HEIGHT - 1) {
        gameOver = 1;
    }

    for (int i = 0; i < tailLength; i++) {
        if (headX == tailX[i] && headY == tailY[i]) {
            gameOver = 1;
        }
    }

    if (headX == foodX && headY == foodY) {
        score += 5;
        tailLength++;

        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
    }
}

FILE *fp;

void saveScore() {
    fp = fopen("score.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "Score: %d\n", score);
    fclose(fp);
}

int main() {

    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(70);
    }
    saveScore();
    printf("\nGame Over!\n");

    return 0;
}
