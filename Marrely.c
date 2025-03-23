#include "Marrely.h"
#include <stdlib.h>
#include <time.h>

void GenerateMakanan(Makanan *makanan, Rintangan *rintangan) {
    int validPosition = 0;

    while (!validPosition) {
        makanan->position.x = (rand() % GRID_WIDTH - 4) + 2;
        makanan->position.y = (rand() % GRID_HEIGHT - 4) + 2;
        validPosition = 1;

      
        for (int i = 0; i < rintangan->count; i++) {
            if (rintangan->rintangan[i].x * CELL_SIZE == makanan->position.x &&
                rintangan->rintangan[i].y * CELL_SIZE == makanan->position.y) {
                validPosition = 0; 
                break;
            }
        }

        if (makanan->position.x < 0 || makanan->position.x >= 400 || 
            makanan->position.y < 0 || makanan->position.y >= 400) {
            validPosition = 0;
        }
    }
}


void GenerateRintangan(Rintangan *rintangan, int level) {
    if (level < 1 || level > 5) return;  
    rintangan->count = level;

    Position levelRintangan[5][10] = {
        { {10, 12}, {14, 14}, {12, 8} },
        { {9, 11}, {15, 13}, {11, 9}, {13, 15} },
        { {8, 10}, {16, 12}, {12, 14}, {14, 8}, {10, 16} },
        { {9, 13}, {11, 15}, {13, 9}, {15, 11}, {12, 12}, {14, 14} },
        { {10, 14}, {14, 10}, {12, 16}, {16, 12}, {8, 12}, {12, 8}, {12, 12} }
    };

    for (int i = 0; i < rintangan->count; i++) {
        rintangan->rintangan[i] = levelRintangan[level - 1][i];
    }
}

void GenerateEnemy(Enemy *enemy, int count, int level) {
    if (level < 2) return;  
    Position enemyPositions[3][3] = {
        { {12, 12} },                   
        { {10, 14}, {14, 10} },          
        { {9, 9}, {13, 13}, {15, 11} }
    };

    for (int i = 0; i < count; i++) {
        enemy[i].position = enemyPositions[level - 2][i];  
        enemy[i].direction = 1;
        enemy[i].isVertical = i % 2;
    }
}

void DrawGame(Makanan *makanan, Rintangan *rintangan, Enemy *enemies, int enemyCount, int score, int level, 
              Texture2D background, Texture2D borderTexture, Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture) {

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

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
    DrawText(TextFormat("Level: %d", level), 10, 30, 20, BLACK);
}

void MoveEnemy(Enemy *enemy) {
    int batasKiri = 1;
    int batasAtas = 1;
    int batasKanan =  (600 / CELL_SIZE) - 1;  
    int batasBawah =  (600 / CELL_SIZE) - 1;  

    if (enemy->isVertical) {
        enemy->position.y += enemy->direction;
        if (enemy->position.y <= batasAtas || enemy->position.y >= batasBawah) {
            enemy->direction *= -1;
            enemy->position.y += enemy->direction;
        }
    } else {
        enemy->position.x += enemy->direction;
        if (enemy->position.x <= batasKiri || enemy->position.x >= batasKanan) {
            enemy->direction *= -1;
            enemy->position.x += enemy->direction;
        }
    }
}
