#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20



void InitSnake(Snake *Snake){
    Snake->position = (Vector2){LEBAR_LAYAR/2, TINGGI_LAYAR/2};
    Snake->speed = (Vector2){UKURAN_BLOCK, 0};
    Snake->panjang = 8;


    for (int i = 0; i < Snake->panjang; i++) {
        Snake->badan[i] = (Vector2){ Snake->position.x - i * UKURAN_BLOCK, Snake->position.y };
        Snake->snakeSprites[i] = (Rectangle){i * 20, 0, 20, 20};
    }
}

void DrawSnake(Snake *Snake) {
    int i = 0;
    while (i < Snake->panjang) {
        int spriteIndex = 1;
        float rotation = 0;
        if (i == 0) { // kepala
            spriteIndex = 0;
            if (Snake->speed.x > 0) rotation = 90;
            if (Snake->speed.x < 0) rotation = 270;
            if (Snake->speed.y > 0) rotation = 180;
        }else if (i == Snake->panjang - 1) { // ekor
            spriteIndex = 2;
            Position tailDirection = {Snake->badan[i - 1].x - Snake->badan[i].x, Snake->badan[i - 1].y - Snake->badan[i].y};
            if (tailDirection.x > 0) rotation = 90;
            if (tailDirection.x < 0) rotation = 270;
            if (tailDirection.y > 0) rotation = 180;
        }else{
            Position prevDirection = {Snake->badan[i - 1].x - Snake->badan[i].x, Snake->badan[i - 1].y - Snake->badan[i].y};
            Position nextDirection = {Snake->badan[i + 1].x - Snake->badan[i].x, Snake->badan[i + 1].y - Snake->badan[i].y};

            spriteIndex = snakeSpritesheet(prevDirection, nextDirection);
            if (spriteIndex == -1) {
                if (prevDirection.x != 0 && nextDirection.x != 0) {  // ke kanan/kiri
                    spriteIndex = 7; // sprite untuk badan lurus ke kiri/kanan
                } else if (prevDirection.y != 0 && nextDirection.y != 0) {  // ke atas/bawah
                    spriteIndex = 1; // sprite untuk badan lurus ke atas/bawah
                }
            }
        }
                
        Vector2 position = { Snake->badan[i].x, Snake->badan[i].y };
        Rectangle destRect = { position.x + UKURAN_BLOCK / 2, position.y + UKURAN_BLOCK / 2, UKURAN_BLOCK, UKURAN_BLOCK };
        Vector2 origin = { UKURAN_BLOCK / 2, UKURAN_BLOCK / 2 };

        DrawTexturePro(Snake->tekstur, Snake->snakeSprites[spriteIndex], destRect, origin, rotation, WHITE);
        
        i = i + 1;
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

bool CheckMakanan(Snake *snake, Food *food) {
    return (snake->badan[0].x == food->position.x && snake->badan[0].y == food->position.y);
}