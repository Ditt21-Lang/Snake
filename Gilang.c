#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

void InitSnake(Snake *Snake){
    Snake->position = (Vector2){LEBAR_LAYAR/2, TINGGI_LAYAR/2};
    Snake->speed= (Vector2){UKURAN_BLOCK, 0};
    Snake->panjang = 5;


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

bool cekTabrakan(Snake *Snake){
    for (int i = 1; i < Snake->panjang; i++){
        if(Snake->badan[0].x == Snake->badan[i].x && Snake->badan[0].y == Snake->badan[i].y){
            return true;
        }
    }
    return false;
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

    cekTabrakan(Snake);
} 

bool CheckMakanan(Snake *snake, Makanan *food) {
    return (snake->badan[0].x == food->position.x && snake->badan[0].y == food->position.y);
}

bool CheckObstacle(Snake *snake, Rintangan *Obstacle){
    for (int i = 0; i < Obstacle->count; i++){
        if (snake->badan[0].x == Obstacle->rintangan[i].x && snake->badan[0].y == Obstacle->rintangan[i].y){
            return true;
        }
    }
    return false;
}