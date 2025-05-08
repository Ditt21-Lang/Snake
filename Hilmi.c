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

bool CekTabrakDinding(Snake *snake) {
    float headX = snake->badan[0].x;
    float headY = snake->badan[0].y;

    if (headX >= 540 || headY >= 540){
        return true;
    } else if (headX <= 20 || headY <= 20){
        return true;
    } else {
        return false;
    }
}


bool CekTabrakRintangan(Snake snake, Vector2 head, Rintangan *rintangan){
    int KepalaX = (int)(head.x / CELL_SIZE);
    int KepalaY = (int)(head.y/CELL_SIZE);

    for (int i = 0; i < snake.panjang; i ++){
        if (KepalaX == rintangan->rintangan[i].x &&
            KepalaY == rintangan->rintangan[i].y) {
            return true;
        }
        else {
            return false;
        }
    }
}


// void CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives, bool *alive){
//     int i = 0;
//     while (i < enemy->count){
//             if (head.x == enemy[i].position.x 
//                 && head.y == enemy[i].position.y){
//                 (*lives)--;
//                 if (*lives <=0){
//                     *alive = false;
//                   } else {
//                     *alive = true;
//                   }
//                 }
//                 printf("Lives : %d\n", *lives);
//             }
//             i++;
// }      kode lama yang error

bool CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives, bool *alive){
    int i = 0;
    bool collision = false;  
    while (i < *count) {
        if (head.x == enemy[i].position.x && head.y == enemy[i].position.y) {
            (*lives)--;  
            collision = true;
            if (*lives <= 0) {
                *alive = false;  
            } else {
                *alive = true;
            }
        }
        i++;
    }
    
    if (collision) {
        printf("Lives: %d\n", *lives); 
    }
}   //kode baru 
