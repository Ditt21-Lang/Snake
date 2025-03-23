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
    { {12, 12}, {0, 6}, {24, 18} },
    { {13, 10}, {5, 24}, {24, 4}, {0, 16} },
    { {6, 0}, {18, 24}, {12, 12}, {24, 7}, {0, 18} },
    { {0, 0}, {24, 24}, {12, 12}, {6, 6}, {18, 18}, {12, 0} },
    { {0, 12}, {24, 12}, {12, 0}, {12, 24}, {6, 6}, {18, 18}, {24, 24} }
}; 
    

    for (int i = 0; i < rintangan->count; i++) {
        rintangan->rintangan[i] = levelRintangan[level - 1][i];
    }
}

void GenerateEnemy(Enemy *enemy, int count, int level) {
    Position enemyPositions[3][3] = {
        { {8, 8} },                   
        { {3, 4}, {18, 6} },          
        { {2, 2}, {12, 12}, {22, 22} } 
    };

    for (int i = 0; i < count; i++) {
        enemy[i].position = enemyPositions[level - 2][i];  
        enemy[i].direction = 1;
        enemy[i].isVertical = i % 2;
    }
}

void DrawGame(Makanan *makanan, Rintangan *rintangan, Enemy *enemies, int enemyCount, int score, int level, Texture2D background, Texture2D borderTexture, Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture){


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
    int batasKanan = (500 / CELL_SIZE) - 1; 
    int batasBawah = (500 / CELL_SIZE) - 1; 

    if (enemy->isVertical) {
        enemy->position.y += enemy->direction;
        if (enemy->position.y < 0 || enemy->position.y >= GRID_HEIGHT) {
            enemy->direction *= -1;
            enemy->position.y += enemy->direction;
        }
    } else {
        enemy->position.x += enemy->direction;
        if (enemy->position.x < 0 || enemy->position.x >= GRID_WIDTH) {
          enemy->direction *= -1;
          enemy->position.x += enemy->direction; 
        }
    }
}
