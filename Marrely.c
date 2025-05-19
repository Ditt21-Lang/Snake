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
// void GenerateEnemy(Enemy *enemy, int count, int level) {
//     if (level < 2) return; 
//     Position enemyPositions[3][3] = {
//         { {12, 12} },                   
//         { {10, 14}, {14, 10} },          
//         { {9, 9}, {13, 13}, {15, 11} }
//     };

//     for (int i = 0; i < count; i++) {
//         enemy[i].position = enemyPositions[level - 2][i];  
//         enemy[i].direction = 1;
//         enemy[i].isVertical = i % 2;
//     }
// }

void DrawGame(Makanan *makanan, RintanganNode *rintangan, Enemy *enemies, int enemyCount, int score, int level, 
              Texture2D background, Texture2D borderTexture, Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture) {

    ClearBackground(RAYWHITE);
    DrawTexture(borderTexture, 0, 0, WHITE);
    DrawTexture(background, 0, 0, WHITE);

   RintanganNode *curr = rintangan;
while (curr != NULL) {
    DrawTexturePro(rintanganTexture,
        (Rectangle){0, 0, rintanganTexture.width, rintanganTexture.height},
        (Rectangle){curr->posisi.x * CELL_SIZE, curr->posisi.y * CELL_SIZE, CELL_SIZE, CELL_SIZE},
        (Vector2){0, 0}, 0, WHITE);
    curr = curr->next;
}
    DrawTexturePro(makananTexture, (Rectangle){0, 0, makananTexture.width, makananTexture.height}, 
                   (Rectangle){makanan->position.x, makanan->position.y, CELL_SIZE, CELL_SIZE}, 
                   (Vector2){0, 0}, 0, WHITE);
    
    for (int i = 0; i < enemyCount; i++) {
        DrawTexturePro(enemyTexture, (Rectangle){0, 0, enemyTexture.width, enemyTexture.height}, 
                       (Rectangle){enemies[i].position.x * CELL_SIZE, enemies[i].position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
    
    }
    DrawRectangle(0, 700, GetScreenWidth(), 200,  LIGHTGRAY);
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


void MoveEnemy(Enemy *enemy, int enemyCount) {
    int batasKiri = 1;
    int batasAtas = 1;
    int batasKanan = GRID_WIDTH - 2;   // Lebih aman agar tidak ke luar batas
    int batasBawah = GRID_HEIGHT - 2;

    for (int i = 0; i < enemyCount; i++) {
        if (enemy[i].isVertical) {
            enemy[i].position.y += enemy[i].direction;
            if (enemy[i].position.y <= batasAtas || enemy[i].position.y >= batasBawah) {
                enemy[i].direction *= -1;
                enemy[i].position.y += enemy[i].direction;
            }
        } else {
            enemy[i].position.x += enemy[i].direction;
            if (enemy[i].position.x <= batasKiri || enemy[i].position.x >= batasKanan) {
                enemy[i].direction *= -1;
                enemy[i].position.x += enemy[i].direction;
            }
        }
    }
}//kode baru ale yang aku benerin