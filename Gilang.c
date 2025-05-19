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
        } else{
            newNode->sprite = (Rectangle){140, 0 ,20, 20};
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

Vector2 getDir(Vector2 A, Vector2 B){
    return (Vector2){A.x - B.x, A.y - B.y};
}

void DrawSnake(Snake *snake, Texture2D texture) {
    SnakeNode* current = snake->head;
    while (current != NULL) {
        Vector2 tikpus = (Vector2){UKURAN_BLOCK / 2.0f, UKURAN_BLOCK / 2.0f};
        Rectangle ukuran = {current->position.x + UKURAN_BLOCK / 2.0f, 
                            current->position.y + UKURAN_BLOCK / 2.0f, 
                            UKURAN_BLOCK, 
                            UKURAN_BLOCK};

        float rotation = 0;
        if(current == snake->head){
            current->sprite = (Rectangle){0, 0, 20, 20};
            if (snake->speed.x > 0){
                rotation = 90;
            } else if (snake->speed.x < 0){
                rotation = 270;
            } else if (snake->speed.y > 0){
                rotation = 180;
            } else if (snake->speed.y < 0){
                rotation = 0;
            }

        } else if (current->next == NULL){
            current->sprite = (Rectangle){40, 0, 20, 20};
            Vector2 direction = getDir(current->prev->position, current->position);
            if (direction.x > 0){
                rotation = 90;
            } else if (direction.x < 0){
                rotation = 270;
            } else if (direction.y > 0){
                rotation = 180;
            } else if (direction.y < 0){
                rotation = 0;
            }
        } else {
            Vector2 prevDir = getDir(current->prev->position, current->position);
            Vector2 nextDir = getDir(current->position, current->next->position);

            if ((prevDir.x > 0 && nextDir.y > 0) || (prevDir.y < 0 && nextDir.x < 0)) {
                current->sprite = (Rectangle){60, 0, 20, 20};
            } else if ((prevDir.x < 0 && nextDir.y > 0) || (prevDir.y < 0 && nextDir.x > 0)){
                current->sprite = (Rectangle){80, 0, 20, 20};
            } else if ((prevDir.x > 0 && nextDir.y < 0) || (prevDir.y > 0 && nextDir.x < 0)){
                current->sprite = (Rectangle){100, 0, 20, 20};
            } else if ((prevDir.x < 0 && nextDir.y < 0) || (prevDir.y > 0 && nextDir.x > 0)){
                current->sprite = (Rectangle){120, 0, 20, 20};
            }

            // Badan lurus horizontal
            else if (prevDir.x != 0 && nextDir.x != 0) {
                current->sprite = (Rectangle){140, 0, 20, 20};
            }
            // Badan lurus vertikal
            else if (prevDir.y != 0 && nextDir.y != 0) {
                current->sprite = (Rectangle){20, 0, 20, 20};
            }
        }
        DrawTexturePro(texture, current->sprite, ukuran, tikpus, rotation, WHITE);

        current = current->next;
    }
}



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

void tambahNode(Snake *snake){
    SnakeNode* newbody = (SnakeNode*)malloc(sizeof(SnakeNode));
    newbody->prev = snake->tail;
    snake->tail->next = newbody;
    snake->tail = newbody;
}

bool CheckMakanan(Snake *snake, Makanan *food) {
    return (snake->head->position.x == food->position.x && snake->head->position.y == food->position.y);
}