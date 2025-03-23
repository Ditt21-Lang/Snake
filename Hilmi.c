#include <stdio.h>
#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"
#include "Gilang.h"
#include "Marrely.h"

float reverseCooldown = 20.0f;                                      /*cooldown dalam detik*/
float reverseTimer = 0.0f;

void ReverseSnake(Snake *snake) {
    if (reverseTimer > 0) return;                                 /*kalau masih cooldown, jangan reverse*/  

    for (int i = 0; i < snake->panjang / 2; i++) {
        Vector2 temp = snake->badan[i];                                 
        snake->badan[i] = snake->badan[snake->panjang - 1 - i];
        snake->badan[snake->panjang - 1 - i] = temp;
     }

    snake->position = snake->badan[0];                                  /* pastikan kepala ada di posisi yang benar*/
    /*tentukan arah gerak baru setelah direverse*/
    Vector2 diff = (Vector2){ 
        snake->badan[0].x - snake->badan[1].x, 
        snake->badan[0].y - snake->badan[1].y 
    };

    snake->speed = diff;                                        /* perbarui kecepatan*/

    reverseTimer = reverseCooldown;                             /*reset cooldown*/
}

void HandleReverseInput(Snake *snake) {
    if (IsKeyPressed(KEY_SPACE) && reverseTimer <=0) {
        ReverseSnake(snake);
    } 
}

void UpdateCooldown(){
    if (reverseTimer > 0){
        reverseTimer -= GetFrameTime();                 /* kurangi cooldown berdasarkan deltaTime*/    
        if (reverseTimer < 0) reverseTimer = 0;
    }
}

void CekTabrakDinding(Snake *snake, int *lives, bool *alive){
    Position newHead = {snake->badan[0].x + snake->position.x,
                      snake->badan[0].y + snake->position.y};

    if (newHead.x < 2 || newHead.x >= GRID_WIDTH - 2 ||
        newHead.y < 2 || newHead.y >= GRID_HEIGHT -2) {
            (*lives)--;
            *alive = false;
            return;
        }
}

void CekTabrakRintangan(Vector2 head, Rintangan *rintangan, int *lives){
        for (int i = 0; i < rintangan->count; i++){
            if (head.x == rintangan->rintangan[i].x
                && head.y == rintangan->rintangan[i].y){
                    (*lives)--;
                    printf("Lives : %d\n", *lives);
                }
        }
}

void CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives){
    int i = 0;
    while (i < enemy->count){
            if (head.x == enemy[i].position.x 
                && head.y == enemy[i].position.y){
                (*lives)--;
                printf("Lives : %d\n", *lives);
                }
                i++;
        }
}