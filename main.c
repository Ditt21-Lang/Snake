#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "Gilang.h"
#include "Marrely.h"

#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

int main() {
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Snake Game");
    
    Snake snake;
    Rintangan obstacle;
    Makanan food;
    Enemy enemies[4];
    int enemyCount = 3;

    SetTargetFPS(10);
    InitSnake(&snake);

    Texture2D background = LoadTexture("tanah.png");  
    Texture2D makananTexture = LoadTexture("tikus.png");  
    Texture2D rintanganTexture = LoadTexture("obstacle.png");  
    Texture2D enemyTexture = LoadTexture("krtTambang.png");
    Texture2D borderTexture = LoadTexture ("dinding.png");

    srand(time(NULL));
    
    int score = 0, level = 1;
    
    GenerateRintangan(&obstacle, level);
    GenerateMakanan(&food, &obstacle);
    GenerateEnemy(enemies, enemyCount, level);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawGame(&food, &obstacle, enemies, enemyCount, score, level, background, borderTexture, makananTexture, enemyTexture, rintanganTexture);

        if (!cekTabrakan(&snake)) {
            UpdateSnake(&snake);
            DrawSnake(&snake);
        } else {
            DrawText("Game Over", LEBAR_LAYAR / 2 - 50, TINGGI_LAYAR / 2, 25, RED);
        }

        if (CheckMakanan(&snake, &food)) {
            score += 100;
            snake.panjang++;
            GenerateMakanan(&food, &obstacle);
        }

        if (CheckObstacle(&snake, &obstacle)) {
            score -= 50;
            if (snake.panjang > 1) snake.panjang--;
        }

        if (score >= 1000) {
            level++;
            GenerateRintangan(&obstacle, level);
            score = 0;
            if (level >= 2) enemyCount = level - 1;  

            GenerateEnemy(enemies, enemyCount, level);
        }

    UnloadTexture(background);
    UnloadTexture(makananTexture);
    UnloadTexture(rintanganTexture);
    UnloadTexture(enemyTexture);
    UnloadTexture(borderTexture);
    CloseWindow();
    return 0;
}
}