#include "Marrely.h"
#include <stdlib.h>
#include <time.h>

void GenerateMakanan(Makanan *makanan, Rintangan *rintangan) {
    int validPosition = 0;
    while (!validPosition) {
        makanan->position.x = (rand() % GRID_WIDTH) * CELL_SIZE;
        makanan->position.y = (rand() % GRID_HEIGHT) * CELL_SIZE;
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



void DrawGame(Makanan *makanan, Rintangan *rintangan, int score, int lives, int level, Texture2D background) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    
    DrawRectangle(makanan->position.x, makanan->position.y , CELL_SIZE, CELL_SIZE, RED);

    for (int i = 0; i < rintangan->count; i++) {
        DrawRectangle(rintangan->rintangan[i].x * CELL_SIZE, rintangan->rintangan[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
    }

    DrawText(TextFormat("Score: %d", score), 10, 600, 30, WHITE);
    DrawText(TextFormat("Lives: %d", lives), 10, 630, 30, RED);
    DrawText(TextFormat("Level: %d", level), 10, 660, 30, YELLOW);
}
