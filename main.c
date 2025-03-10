#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

int main(){
    
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Snake Game");
    Snake Snake;
    Rintangan obstacle;
    Makanan food;
    SetTargetFPS(10);
    InitSnake(&Snake);
    int score = 0;
    GenerateMakanan(&food, &obstacle);
    Texture2D tanah = LoadTexture("tanah.png");


    while(!WindowShouldClose()){
        BeginDrawing();
        DrawGame(&food, &obstacle, score ,0 ,0 ,tanah);
        if(!cekTabrakan(&Snake)){
            UpdateSnake(&Snake);
            DrawSnake(&Snake);
        }
        else{
            DrawText("Game Over", LEBAR_LAYAR/2, TINGGI_LAYAR/2, 25, RED);
        }

        if(CheckMakanan(&Snake, &food)){
            score += 100;
            Snake.panjang++;
            GenerateMakanan(&food, &obstacle);
        }

        if(CheckObstacle(&Snake, &obstacle)){
            score -= 50;
            Snake.panjang--;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}