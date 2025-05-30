#include <stdio.h>
#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"
#include "Gilang.h"
#include "Marrely.h"

float reverseCooldown = 20.0f;                                      /*cooldown dalam detik*/
float reverseTimer = 0.0f;

//untuk membalikkan arah ular 
void ReverseSnake(Snake *snake){
    if (reverseTimer > 0) return;  /* jangan direverse kalo masih cooldown */
    if (snake->head == NULL || snake->tail == NULL) return;                 

    SnakeNode *current = snake->head;   
    SnakeNode *prev = NULL; 

    //balik arah ular dengan next jadi prev dan sebaliknya
    while (current != NULL) {
        SnakeNode *next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }

    snake->tail = snake->head;                                      /* update pointer tail */
    snake->head = prev;                                             /* update pointer head */
    
    //update arah ular dari dua node pertama
    if (snake->head->next != NULL){  
        Vector2 newHead = snake->head->position;     
        Vector2 secondNode = snake->head->next->position;

        snake->direction.x = newHead.x - secondNode.x;
        snake->direction.y = newHead.y - secondNode.y;
    }

    reverseTimer = reverseCooldown;                                 /*reset cooldown*/
}

//untuk memperbarui cooldown
void UpdateCooldown(){
    if (reverseTimer > 0){
        reverseTimer -= GetFrameTime();                 /*kurangi cooldown dengan waktu frame*/
        if (reverseTimer < 0) reverseTimer = 0;
    }
}

//untuk mengecek jika kepala ular menabrak dinding
bool CekTabrakDinding(Snake *snake) {
    float headX = snake->head->position.x;
    float headY = snake->head->position.y;

    if (headX >= 540 || headY >= 540){
        return true;
    } else if (headX <= 20 || headY <= 20){
        return true;
    } else {
        return false;
    }
}

//untuk mengecek jika kepala ular menabrak rintangan
bool CekTabrakRintangan(Vector2 head, RintanganNode *rintanganHead) {
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

//untuk mengecek jika ular menabrak enemy
bool CekTabrakEnemy(Snake ular, EnemyList list){

    Enemy *enemy = list.head;
    while (enemy != NULL) {

        SnakeNode *current = ular.head;
        while (current != NULL){
            int snakeX = (int)(current->position.x / CELL_SIZE);
            int snakeY = (int)(current->position.y / CELL_SIZE);

            if (enemy->position.x == snakeX && enemy->position.y == snakeY) {
                return true;  
            }
            current = current->next;
        }
        enemy = enemy->next;
    }
    return false;
}

//membuat list enemy berdasarkan level
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
        if (!newEnemy) break;       /* cek alokasi memori */

        newEnemy->position = enemyPositions[level - 2 ][i];
        newEnemy->direction = 1;
        newEnemy->isVertical = i % 2;
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

//untuk membebaskan memori list enemy
void FreeEnemyList(EnemyList *list) {
    Enemy *current = list->head;
    while (current != NULL) { 
        Enemy *hapus = current;
        current = current->next;
        free(hapus);
    }
    list->head = NULL;
    list->count = 0;
}

//untuk menggerakkan enemy sesuai arah dan batas
void MoveEnemy(EnemyList *list) {
    int batasKiri = 1;
    int batasAtas = 1;
    int batasKanan = GRID_WIDTH - 2;
    int batasBawah = GRID_HEIGHT - 2;

    Enemy *current = list->head;
    while (current != NULL) {
        if (current->isVertical) {
            current->position.y += current->direction;
            if (current->position.y <= batasAtas || current->position.y >= batasBawah) {
                current->direction *= -1;
                current->position.y += current->direction;
            }
        } else {
            current->position.x += current->direction;
            if (current->position.x <= batasKiri || current->position.x >= batasKanan) {
                current->direction *= -1;
                current->position.x += current->direction;
            }
        }
        current = current->next;
    }
}
