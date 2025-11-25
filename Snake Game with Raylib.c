#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define CELL_SIZE 20

int snakeX[100], snakeY[100]; 
int tailLength = 0;
int snakeDir = 0; 
int foodX, foodY;
int score = 0;

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

void ResetGame() {
    if (score > 0){
        saveScore();}

    tailLength = 0;
    snakeDir = 0;
    score = 0;

    snakeX[0] = WIDTH / (2 * CELL_SIZE);
    snakeY[0] = HEIGHT / (2 * CELL_SIZE);

    foodX = rand() % (WIDTH / CELL_SIZE);
    foodY = rand() % (HEIGHT / CELL_SIZE);
}


int main() {
    InitWindow(WIDTH, HEIGHT, "Snake Game with Raylib");
    SetTargetFPS(10);

    ResetGame();

    while (!WindowShouldClose()) {
        
        if (IsKeyPressed(KEY_W) && snakeDir != 2) snakeDir = 1;
        if (IsKeyPressed(KEY_S) && snakeDir != 1) snakeDir = 2;
        if (IsKeyPressed(KEY_A) && snakeDir != 4) snakeDir = 3;
        if (IsKeyPressed(KEY_D) && snakeDir != 3) snakeDir = 4;

        for (int i = tailLength; i > 0; i--) {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }

        switch (snakeDir) {
            case 1: snakeY[0]--; break;
            case 2: snakeY[0]++; break;
            case 3: snakeX[0]--; break;
            case 4: snakeX[0]++; break;
        }

        if (snakeX[0] < 0 || snakeX[0] >= WIDTH / CELL_SIZE ||
            snakeY[0] < 0 || snakeY[0] >= HEIGHT / CELL_SIZE) {
            ResetGame();
        }

        for (int i = 1; i <= tailLength; i++) {
            if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
                ResetGame();
            }
        }

        if (snakeX[0] == foodX && snakeY[0] == foodY) {
            tailLength++;
            score += 5;
            foodX = rand() % (WIDTH / CELL_SIZE);
            foodY = rand() % (HEIGHT / CELL_SIZE);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i <= tailLength; i++) {
            DrawRectangle(snakeX[i] * CELL_SIZE, snakeY[i] * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
        }

        
        DrawRectangle(foodX * CELL_SIZE, foodY * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);

        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}
