#include "marrely.h"
#include <stdlib.h>
#include <time.h>


void GenerateMakanan(Makanan *makanan, Rintangan *rintangan) {
    int validPosition = 0;
    
    while (!validPosition) {
        makanan->position.x = rand() % (500 / CELL_SIZE); // X antara 0 - 24
        makanan->position.y = rand() % (500 / CELL_SIZE); // Y antara 0 - 24
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

void DrawGame(Makanan *makanan, Rintangan *rintangan, Enemy *enemies, int enemyCount, int score, int level, 
              Texture2D background, Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);

    for (int i = 0; i < rintangan->count; i++) {
        DrawTexturePro(rintanganTexture, (Rectangle){0, 0, rintanganTexture.width, rintanganTexture.height}, 
                       (Rectangle){rintangan->rintangan[i].x * CELL_SIZE, rintangan->rintangan[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
    }

    DrawTexturePro(makananTexture, (Rectangle){0, 0, makananTexture.width, makananTexture.height}, 
                   (Rectangle){makanan->position.x * CELL_SIZE, makanan->position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                   (Vector2){0, 0}, 0, WHITE);
    
    for (int i = 0; i < enemyCount; i++) {
        DrawTexturePro(enemyTexture, (Rectangle){0, 0, enemyTexture.width, enemyTexture.height}, 
                       (Rectangle){enemies[i].position.x * CELL_SIZE, enemies[i].position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
    }

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
    DrawText(TextFormat("Level: %d", level), 10, 30, 20, BLACK);
}

void MoveEnemy(Enemy *enemy) {
    if (enemy->isVertical) {
        enemy->position.y += enemy->direction;
        if (enemy->position.y <= 0 || enemy->position.y >= GRID_HEIGHT - 1) {
            enemy->direction *= -1;
        }
    } else {
        enemy->position.x += enemy->direction;
        if (enemy->position.x <= 0 || enemy->position.x >= GRID_WIDTH - 1) {
            enemy->direction *= -1;
        }
    }
}
