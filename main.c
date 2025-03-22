#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#include "Hilmi.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

int main(){
    
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Snake Game");
    Snake Snake;
    SetTargetFPS(10);
    InitSnake(&Snake);

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

        if(IsKeyPressed(KEY_SPACE)){
           ReverseSnake(&Snake); 
        }

    }

    CloseWindow();
    return 0;
}