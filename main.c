#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#include "Marrely.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

int main(){
    
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Snake Game");
    Snake Snake;
    SetTargetFPS(10);
    InitSnake(&Snake);
    Texture2D background = LoadTexture("tanah.jpeg");  
    Texture2D makananTexture = LoadTexture("makanan.png");  
    Texture2D rintanganTexture = LoadTexture("rintangan.png");  
    
    srand(time(NULL));
    
    Makanan makanan;
    Rintangan rintangan;
    
    int score = 0, lives = 3, level = 1;
    
    GenerateRintangan(&rintangan, level);
    GenerateMakanan(&makanan, &rintangan);
    
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        if(!cekTabrakan(&Snake)){
            UpdateSnake(&Snake);
            DrawSnake(&Snake);
        }
        else{
            DrawText("Game Over", LEBAR_LAYAR/2, TINGGI_LAYAR/2, 25, RED);
        }
        EndDrawing();

    }

    CloseWindow();
    return 0;
}