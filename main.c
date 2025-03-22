#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "marrely.h"

#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800

int main() {
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Snake Game");
    
    Snake snake;
    Rintangan obstacle;
    Makanan food;
    int score = 0, level = 1; 

    InitSnake(&snake);
    SetTargetFPS(10);
    srand(time(NULL));

    Texture2D background = LoadTexture("tanah.png");  
    Texture2D makananTexture = LoadTexture("tikus.png");  
    Texture2D rintanganTexture = LoadTexture("obstacle.png");  
    Texture2D enemyTexture = LoadTexture("krtTambang.png");

    GenerateRintangan(&obstacle, level);
    GenerateMakanan(&food, &obstacle);

    int enemyCount = (level == 2) ? 1 : (level == 3) ? 2 : (level == 5) ? 3 : 0;
    Enemy enemies[3];

    if (enemyCount > 0) {
        GenerateEnemy(enemies, enemyCount, level);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawGame(&food, &obstacle, enemies, enemyCount, score, level, background, makananTexture, enemyTexture, rintanganTexture);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
