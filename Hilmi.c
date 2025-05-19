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


bool CekTabrakRintangan(Snake snake, Vector2 head, RintanganNode *rintanganHead) {
    int KepalaX = (int)(head.x / CELL_SIZE);
    int KepalaY = (int)(head.y / CELL_SIZE);

    RintanganNode *current = rintanganHead;

    while (current != NULL) {
        if (KepalaX == current->posisi.x && KepalaY == current->posisi.y) {
            return true;  
        }
        current = current->next;
    }
    return false; 
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

// bool CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives, bool *alive){
//     int i = 0;
//     bool collision = false;  
//     while (i < *count) {
//         if (head.x == enemy[i].position.x && head.y == enemy[i].position.y) {
//             (*lives); //--;  
//             collision = true;
//             if (*lives <= 0) {
//                 *alive = false;  
//             } else {
//                 *alive = true;
//             }
//         }
//         i++;
//     }
    
//     if (collision) {
//         printf("Lives: %d\n", *lives); 
//     }
// }   //kode baru 

EnemyList GenerateEnemy(int level) {
    EnemyList list = {NULL, 0};

    Position enemyPositions[3][3] = {
        { {12, 12} },
        { {10, 14}, {14, 10} },
        { {9, 9}, {13, 13}, {15, 11} }
    };

    int jumlah = 0;
    if (level == 2) {
        jumlah = 1;
    } else if (level == 3) {
        jumlah = 2;
    } else if (level == 4) {
        jumlah = 3;
    } else if (level == 5) {
        jumlah = 3;
    }

    Enemy *tail = NULL;
    int i;
    for (i = 0; i < jumlah; i++){
        Enemy *newEnemy = malloc(sizeof(Enemy));
        if (!newEnemy) break; //cek alokasi memori

        newEnemy->position = enemyPositions[level - 2 ][i];
        newEnemy->direction = 1;
        newEnemy->isVertical = 1 % 2;
        newEnemy->next = NULL;

        if (list.head == NULL) {
            list.head = newEnemy;
            tail = newEnemy;
        } else {
            tail->next = newEnemy;
            tail = newEnemy;
        }
        list.count++;
    }

    return list;
}