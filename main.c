#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#include "Marrely.h"
#include <time.h>

#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

int main() {
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Snake Game");
    
    Snake Snake;
    Rintangan obstacle;
    Makanan food;
    Enemy musuh;

    SetTargetFPS(10);
    InitSnake(&Snake);


    Texture2D background = LoadTexture("tanah.png");  
    Texture2D makananTexture = LoadTexture("tikus.png");  
    Texture2D rintanganTexture = LoadTexture("obstacle.png");  
    Texture2D enemyTexture = LoadTexture("krtTambang.png");

    srand(time(NULL));
    
    int score = 0, lives = 3, level = 4;
    
    GenerateRintangan(&obstacle, level);
    GenerateMakanan(&food, &obstacle);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        
       DrawGame(&food, &obstacle, &musuh, 0, score, level, background, makananTexture, enemyTexture, rintanganTexture);

        if (!cekTabrakan(&Snake)) {
            UpdateSnake(&Snake);
            DrawSnake(&Snake);
        } else {
            DrawText("Game Over", LEBAR_LAYAR / 2, TINGGI_LAYAR / 2, 25, RED);
        }

        if (CheckMakanan(&Snake, &food)) {
            score += 100;
            Snake.panjang++;
            GenerateMakanan(&food, &obstacle);
        }

        if (CheckObstacle(&Snake, &obstacle)) {
            score -= 50;
            Snake.panjang--;
        }
        
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(makananTexture);
    UnloadTexture(rintanganTexture);
    UnloadTexture(enemyTexture);

    CloseWindow();
    return 0;
}
