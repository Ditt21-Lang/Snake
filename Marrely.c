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
            if (rintangan->rintangan[i].x == makanan->position.x &&
                rintangan->rintangan[i].y == makanan->position.y) {
                validPosition = 0;
                break;
            }
        }
    }
}

void GenerateRintangan(Rintangan *rintangan, int level) {
    rintangan->count = level;
    
    Position levelRintangan[5][10] = {
        { {3, 7}, {12, 5}, {8, 14} },
        { {2, 10}, {7, 3}, {14, 8}, {11, 12} },
        { {5, 2}, {9, 6}, {3, 13}, {16, 10}, {12, 17} },
        { {1, 9}, {8, 4}, {13, 11}, {6, 15}, {17, 7}, {20, 14} },
        { {0, 5}, {11, 3}, {4, 12}, {15, 6}, {9, 18}, {19, 8}, {23, 20} }
    };

    for (int i = 0; i < rintangan->count; i++) {
        rintangan->rintangan[i] = levelRintangan[level - 1][i];
    }
}

void GenerateEnemy(Enemy *enemy, int count, int level) {
    Position enemyPositions[3][3] = {
        { {5, 5} },                 
        { {3, 4}, {7, 8} },         
        { {2, 2}, {6, 6}, {10, 10} } 
    };

    for (int i = 0; i < count; i++) {
        enemy[i].position = enemyPositions[level - 2][i];  
        enemy[i].direction = 1;
        enemy[i].isVertical = i % 2;
    }
}

void DrawGame(Makanan *makanan, Rintangan *rintangan, Enemy enemies[], int enemyCount, int score, int lives, int level, Texture2D borderTexture, 
              Texture2D background, Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(borderTexture, 0, 0, WHITE);

    for (int i = 0; i < rintangan->count; i++) {
        DrawTexturePro(rintanganTexture, (Rectangle){0, 0, rintanganTexture.width, rintanganTexture.height}, 
                       (Rectangle){rintangan->rintangan[i].x * CELL_SIZE, rintangan->rintangan[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
    }

    DrawTexturePro(makananTexture, (Rectangle){0, 0, makananTexture.width, makananTexture.height}, 
                   (Rectangle){makanan->position.x, makanan->position.y, CELL_SIZE, CELL_SIZE}, 
                   (Vector2){0, 0}, 0, WHITE);
    
    for (int i = 0; i < enemyCount; i++) {
        DrawTexturePro(enemyTexture, (Rectangle){0, 0, enemyTexture.width, enemyTexture.height}, 
                       (Rectangle){enemies[i].position.x * CELL_SIZE, enemies[i].position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
    }
}

void MoveEnemy(Enemy *enemy) {
    if (enemy->isVertical) {
        enemy->position.y += enemy->direction;
        if (enemy->position.y < 0 || enemy->position.y >= GRID_HEIGHT) {
            enemy->direction *= -1;
        }
    } else {
        enemy->position.x += enemy->direction;
        if (enemy->position.x < 0 || enemy->position.x >= GRID_WIDTH) {
            enemy->direction *= -1;
        }
    }
}
