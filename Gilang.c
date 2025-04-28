#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#include "Bayu.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20



void InitSnake(Snake *snake){
    float startX = LEBAR_LAYAR/2;
    float startY = TINGGI_LAYAR/2;
    snake->speed= (Vector2){UKURAN_BLOCK, 0};
    snake->panjang = 8;
    snake->head = NULL;
    snake->tail = NULL;


    for (int i = 0; i < snake->panjang; i++) {
        SnakeNode* newNode = (SnakeNode*)malloc(sizeof(SnakeNode));
        newNode->position = (Vector2){startX - i * UKURAN_BLOCK, startY};
        newNode->prev = NULL;
        newNode->next = NULL;

        if(i == 0){
            newNode->sprite = (Rectangle){0, 0, 20, 20};
        } else if (i == 7){
            newNode->sprite = (Rectangle){40, 0, 20, 20};
        } else {
            newNode->sprite = (Rectangle){140, 0, 20, 20};
        }

        if(snake->head == NULL && snake->tail == NULL){
            snake->head = newNode;
            snake->tail = newNode;
        } else {
            newNode->next = NULL;
            snake->tail->next = newNode;
            newNode->prev = snake->tail;
            snake->tail =newNode; 
        }
    }
}

void DrawSnake(Snake *snake, Texture2D texture) {
    SnakeNode* current = snake->head;
    while (current != NULL) {
        DrawTextureRec(
            texture,                  // texture spritesheet
            current->sprite,           // potongan sprite node ini
            current->position,         // posisi di layar
            WHITE                      // warna (putih supaya tidak berubah warna)
        );
        current = current->next;
    }
}
    // int i = 0;
    // while (i < Snake->panjang) {
    //     int spriteIndex = 1;
    //     float rotation = 0;
    //     if (i == 0) { // kepala
    //         spriteIndex = 0;
    //         if (Snake->speed.x > 0) rotation = 90;
    //         if (Snake->speed.x < 0) rotation = 270;
    //         if (Snake->speed.y > 0) rotation = 180;
    //     }else if (i == Snake->panjang - 1) { // ekor
    //         spriteIndex = 2;
    //         Position tailDirection = {Snake->badan[i - 1].x - Snake->badan[i].x, Snake->badan[i - 1].y - Snake->badan[i].y};
    //         if (tailDirection.x > 0) rotation = 90;
    //         if (tailDirection.x < 0) rotation = 270;
    //         if (tailDirection.y > 0) rotation = 180;
    //     }else{
    //         Position prevDirection = {Snake->badan[i - 1].x - Snake->badan[i].x, Snake->badan[i - 1].y - Snake->badan[i].y};
    //         Position nextDirection = {Snake->badan[i + 1].x - Snake->badan[i].x, Snake->badan[i + 1].y - Snake->badan[i].y};

    //         spriteIndex = snakeSpritesheet(prevDirection, nextDirection);
    //         if (spriteIndex == -1) {
    //             if (prevDirection.x != 0 && nextDirection.x != 0) {  // ke kanan/kiri
    //                 spriteIndex = 7; // sprite untuk badan lurus ke kiri/kanan
    //             } else if (prevDirection.y != 0 && nextDirection.y != 0) {  // ke atas/bawah
    //                 spriteIndex = 1; // sprite untuk badan lurus ke atas/bawah
    //             }
    //         }
    //     }
                
    //     Vector2 position = { Snake->badan[i].x, Snake->badan[i].y };
    //     Rectangle destRect = { position.x + UKURAN_BLOCK / 2, position.y + UKURAN_BLOCK / 2, UKURAN_BLOCK, UKURAN_BLOCK };
    //     Vector2 origin = { UKURAN_BLOCK / 2, UKURAN_BLOCK / 2 };

    //     DrawTexturePro(Snake->tekstur, Snake->snakeSprites[spriteIndex], destRect, origin, rotation, WHITE);
        
    //     i = i + 1;
    // }


bool cekTabrakan(Snake *snake){
    SnakeNode* current;
    current = snake->head->next;
    for (int i = 1; i < snake->panjang; i++){
        if(snake->head->position.x == current->position.x && snake->head->position.y == current->position.y){
            return true;
        }
        current = current->next;
    }
    return false;
}

void UpdateSnake(Snake *snake) {
    if(snake->speed.x !=0){
        if(IsKeyPressed(KEY_UP)){
            snake->speed = (Vector2){0, -UKURAN_BLOCK};
        }
        else if(IsKeyPressed(KEY_DOWN)){
            snake->speed = (Vector2){0, UKURAN_BLOCK};
        }
    }
    else if(snake->speed.y != 0){
        if(IsKeyPressed(KEY_RIGHT)){
            snake->speed = (Vector2){UKURAN_BLOCK, 0};
        }
        else if(IsKeyPressed(KEY_LEFT)){
            snake->speed = (Vector2){-UKURAN_BLOCK, 0};
        }
    }

    // Geser posisi tiap segmen ke posisi segmen sebelumnya, dari ekor ke kepala
    SnakeNode* current = snake->tail;
    while (current != snake->head){
        current->position = current->prev->position;
        current = current->prev;
    } 

    // Perbarui posisi kepala dengan menambahkan kecepatan
    snake->head->position.x += snake->speed.x;
    snake->head->position.y += snake->speed.y;

    cekTabrakan(snake);
} 

bool CheckMakanan(Snake *snake, Makanan *food) {
    if (snake->head->position.x == food->position.x && snake->head->position.y == food->position.y){
        return true;
    }
    return false;
}

void tambahEkor(Snake *snake){
    SnakeNode* newNode = (SnakeNode*)malloc(sizeof(SnakeNode));
    if (newNode == NULL){
        printf("Ekor gagal ditambahkan");
    }

    newNode->position = snake->tail->position;
    newNode->sprite = (Rectangle){40, 0, 20, 20};
    newNode->prev = snake->tail;
    newNode->next = NULL;

    snake->tail->next = newNode;
    snake->tail = newNode;
    snake->panjang = snake->panjang + 1;
}

void freeSnake(Snake *snake){
    SnakeNode* current;
    current = snake->head;
    while (current != NULL){
        SnakeNode* next = current->next;
        free(current);
        current = next;
    }

    snake->head = NULL;
    snake->tail = NULL;
    snake->panjang = 0;
}