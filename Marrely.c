#include "Marrely.h"
#include <stdlib.h>
#include <time.h>

void GenerateMakanan(Makanan *makanan, Rintangan *rintangan, Snake *snake) {
    int validPosition = 0;
    while (!validPosition) {
        makanan->position.x = rand() % GRID_WIDTH;
        makanan->position.y = rand() % GRID_HEIGHT;
        validPosition = 1;

        for (int i = 0; i < rintangan->count; i++) {
            if (rintangan->rintangan[i].x == makanan->position.x && rintangan->rintangan[i].y == makanan->position.y) {
                validPosition = 0;
                break;
            }
        }
    }
}

void GenerateRintangan(Rintangan *rintangan, int level) {
    rintangan->count = level;
    Position levelRintangan[5][10] = {
        { {5, 5}, {10, 10}, {15, 15} },
        { {3, 4}, {7, 8}, {11, 12}, {15, 16} },
        { {2, 2}, {6, 6}, {10, 10}, {14, 14}, {18, 18} },
        { {1, 3}, {5, 7}, {9, 11}, {13, 15}, {17, 19}, {20, 22} },
        { {0, 0}, {4, 4}, {8, 8}, {12, 12}, {16, 16}, {20, 20}, {24, 24} }
    };

    for (int i = 0; i < rintangan->count; i++) {
        rintangan->rintangan[i] = levelRintangan[level - 1][i];
    }
}

void InitSnake(Snake *snake) {
    snake->length = 1;
    snake->body[0].x = GRID_WIDTH / 2;
    snake->body[0].y = GRID_HEIGHT / 2;
    snake->dx = 1;
    snake->dy = 0;
}

void UpdateSnake(Snake *snake) {
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[0].x += snake->dx;
    snake->body[0].y += snake->dy;
}

int CheckCollision(Snake *snake, Rintangan *rintangan) {
    for (int i = 0; i < rintangan->count; i++) {
        if (snake->body[0].x == rintangan->rintangan[i].x && snake->body[0].y == rintangan->rintangan[i].y) {
            return 1;
        }
    }
    if (snake->body[0].x < 0 || snake->body[0].x >= GRID_WIDTH || snake->body[0].y < 0 || snake->body[0].y >= GRID_HEIGHT) {
        return 1;
    }
    return 0;
}

void DrawGame(Makanan *makanan, Rintangan *rintangan, Snake *snake, int score, int lives, int level, Texture2D background) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    
    DrawRectangle(makanan->position.x * CELL_SIZE, makanan->position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    for (int i = 0; i < rintangan->count; i++) {
        DrawRectangle(rintangan->rintangan[i].x * CELL_SIZE, rintangan->rintangan[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
    }

    for (int i = 0; i < snake->length; i++) {
        DrawRectangle(snake->body[i].x * CELL_SIZE, snake->body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
    }

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
    DrawText(TextFormat("Lives: %d", lives), 10, 30, 20, BLACK);
    DrawText(TextFormat("Level: %d", level), 10, 50, 20, BLACK);
}
