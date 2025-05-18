#include "Marrely.h"
#include "Hilmi.h"
#include <stdlib.h>
#include <time.h>

void FreeRintangan(RintanganNode **head) {
    RintanganNode *curr = *head;
    while (curr != NULL) {
        RintanganNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

void FreeEnemy(EnemyNode **head) {
    EnemyNode *curr = *head;
    while (curr != NULL) {
        EnemyNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

void GenerateMakanan(Makanan *makanan, RintanganNode *rintanganHead) {
    int validPosition = 0;

    int batasKiri = 2;  
    int batasKanan = GRID_WIDTH - 3; 
    int batasAtas = 2;
    int batasBawah = GRID_HEIGHT - 3;  

    while (!validPosition) {
        makanan->position.x = (rand() % (batasKanan - batasKiri + 1) + batasKiri) * CELL_SIZE;
        makanan->position.y = (rand() % (batasBawah - batasAtas + 1) + batasAtas) * CELL_SIZE;
        validPosition = 1;

        RintanganNode *curr = rintanganHead;
        while (curr != NULL) {
            if(curr->posisi.x * CELL_SIZE == makanan->position.x && curr->posisi.y * CELL_SIZE == makanan->position.y){
                validPosition = 0;
                break;
            }
            curr = curr->next;
        }
        

        if (makanan->position.x < 0 || makanan->position.x >= 500 || 
            makanan->position.y < 0 || makanan->position.y >= 500) {
            validPosition = 0;
        }
    }
}


void GenerateRintangan(RintanganNode **head, int level) {
    if (level < 1 || level > 5) return;  
  
    
    Position levelRintangan[5][10] = {
    { {10, 12}, {14, 14}, {12, 8} },
    { {9, 11}, {15, 13}, {11, 9}, {13, 15} },
    { {8, 10}, {16, 12}, {12, 14}, {14, 8}, {10, 16} },
    { {9, 13}, {11, 15}, {13, 9}, {15, 11}, {12, 12}, {14, 14} },
    { {10, 14}, {14, 10}, {12, 16}, {16, 12}, {8, 12}, {12, 8}, {12, 12} }
}; 

*head = NULL;
    

    for (int i = 0; i < level; i++) {
       RintanganNode *newNode = (RintanganNode *)malloc(sizeof(RintanganNode));
       newNode->posisi = levelRintangan[level - 1][i];
       newNode->next = *head;
       *head = newNode;
    }
}
void GenerateEnemy(EnemyNode **head, int count, int level){
    if (level < 2) return; 

    Position enemyPositions[3][3] = {
        { {12, 12} },                   
        { {10, 14}, {14, 10} },          
        { {9, 9}, {13, 13}, {15, 11} }
    };

    for (int i = 0; i < count; i++) {
         EnemyNode *newNode = (EnemyNode *)malloc(sizeof(EnemyNode));
        newNode->enemy.position = enemyPositions[level - 2][i];
        newNode->enemy.direction = 1;
        newNode->enemy.isVertical = i % 2;
        newNode->next = *head;
        *head = newNode;
    }
}

void DrawGame(Makanan *makanan, RintanganNode *rintanganHead, EnemyNode *enemyHead, 
              int score, int level, 
              Texture2D background, Texture2D borderTexture, 
              Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture) {

    ClearBackground(RAYWHITE);
    DrawTexture(borderTexture, 0, 0, WHITE);
    DrawTexture(background, 0, 0, WHITE);

   
    RintanganNode *currR = rintanganHead;
    while (currR != NULL) {
        DrawTexturePro(rintanganTexture, 
                       (Rectangle){0, 0, rintanganTexture.width, rintanganTexture.height}, 
                       (Rectangle){currR->posisi.x * CELL_SIZE, currR->posisi.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
        currR = currR->next;
    }

    DrawTexturePro(makananTexture, 
                   (Rectangle){0, 0, makananTexture.width, makananTexture.height}, 
                   (Rectangle){makanan->position.x, makanan->position.y, CELL_SIZE, CELL_SIZE}, 
                   (Vector2){0, 0}, 0, WHITE);

    EnemyNode *currE = enemyHead;
    while (currE != NULL) {
        DrawTexturePro(enemyTexture, 
                       (Rectangle){0, 0, enemyTexture.width, enemyTexture.height}, 
                       (Rectangle){currE->enemy.position.x * CELL_SIZE, currE->enemy.position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
        currE = currE->next;
    }

    
    DrawRectangle(0, 700, GetScreenWidth(), 200, LIGHTGRAY);
    DrawRectangle(0, 600, GetScreenWidth(), 100, (Color){0, 0, 0, 200}); 
}

// void MoveEnemy(Enemy *enemy) {
//     int batasKiri = 1;
//     int batasAtas = 1;
//     int batasKanan =  (600 / CELL_SIZE) - 1;  
//     int batasBawah =  (600 / CELL_SIZE) - 1;  

//     if (enemy->isVertical) {
//         enemy->position.y += enemy->direction;
//         if (enemy->position.y <= batasAtas || enemy->position.y >= batasBawah) {
//             enemy->direction *= -1;
//             enemy->position.y += enemy->direction;
//         }
//     } else {
//         enemy->position.x += enemy->direction;
//         if (enemy->position.x <= batasKiri || enemy->position.x >= batasKanan) {
//             enemy->direction *= -1;
//             enemy->position.x += enemy->direction;
//         }
//     }
// }    kode lama ale


void MoveEnemy(EnemyNode *head) {
    int batasKiri = 1;
    int batasAtas = 1;
    int batasKanan = GRID_WIDTH - 1;
    int batasBawah = GRID_HEIGHT - 1;

    EnemyNode *curr = head;
    while (curr != NULL) {
        if (curr->enemy.isVertical) {
            curr->enemy.position.y += curr->enemy.direction;
            if (curr->enemy.position.y <= batasAtas || curr->enemy.position.y >= batasBawah) {
                curr->enemy.direction *= -1;
                curr->enemy.position.y += curr->enemy.direction;
            }
        } else {
            curr->enemy.position.x += curr->enemy.direction;
            if (curr->enemy.position.x <= batasKiri || curr->enemy.position.x >= batasKanan) {
                curr->enemy.direction *= -1;
                curr->enemy.position.x += curr->enemy.direction;
            }
        }
        curr = curr->next;
    }
}

 //kode baru ale yang aku benerin

