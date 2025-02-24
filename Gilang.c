#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
#define UKURAN_BLOCK 20

int main(){

    
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Test");
    Snake Snake;
    SetTargetFPS(10);
    InitSnake(&Snake);

    while(!WindowShouldClose()){
        BeginDrawing();
        UpdateSnake(&Snake);
        ClearBackground(RAYWHITE);

        DrawSnake(&Snake);
        

        
        DrawText("Contoh", 280, 500, 20, BLACK);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}

void InitSnake(Snake *Snake){
    Snake->position = (Vector2){LEBAR_LAYAR/2, TINGGI_LAYAR/2};
    Snake->speed = (Vector2){3,0};
    Snake->panjang = 10;


    for (int i = 0; i < Snake->panjang; i++) {
        Snake->badan[i] = (Vector2){ Snake->position.x - i * UKURAN_BLOCK, Snake->position.y };
        // Snake->position.x akan membuat badan lainnya ke sebelah kiri dengan mengurangi posisi sebesar 20.
    }
}

void DrawSnake(Snake *Snake) {
    for (int i = 0; i < Snake->panjang; i++) {
        DrawRectangleV(Snake->badan[i], (Vector2){UKURAN_BLOCK, UKURAN_BLOCK}, BLUE);
    }
}

void UpdateSnake(Snake *Snake) {
    if(Snake->speed.x !=0){
        if(IsKeyPressed(KEY_UP)){
            Snake->speed = (Vector2){0, -UKURAN_BLOCK};
        }
        else if(IsKeyPressed(KEY_DOWN)){
            Snake->speed = (Vector2){0, UKURAN_BLOCK};
        }
    }
    else if(Snake->speed.y != 0){
        if(IsKeyPressed(KEY_RIGHT)){
            Snake->speed = (Vector2){UKURAN_BLOCK, 0};
        }
        else if(IsKeyPressed(KEY_LEFT)){
            Snake->speed = (Vector2){-UKURAN_BLOCK, 0};
        }
    }

    // Geser posisi tiap segmen ke posisi segmen sebelumnya, dari ekor ke kepala
    for (int i = Snake->panjang - 1; i > 0; i--) {
    Snake->badan[i] = Snake->badan[i - 1];
    }
   // Perbarui posisi kepala dengan menambahkan kecepatan
    Snake->badan[0].x += Snake->speed.x;
    Snake->badan[0].y += Snake->speed.y;
} 