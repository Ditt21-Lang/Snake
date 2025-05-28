#include "Marrely.h"
#include "Hilmi.h"
#include <stdlib.h>
#include <time.h>


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

LevelNode *levelList = NULL;

void FreeRintangan(RintanganNode **head) {
    RintanganNode *curr = *head;
    while (curr != NULL) {
        RintanganNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

void FreeLevel(LevelNode **head){
    LevelNode *curr = *head;
    while (curr != NULL) {
        LevelNode *temp = curr;
        curr = curr->next;
        FreeRintangan(&temp->rintanganHead); 
        free(temp); 
    }
    *head = NULL;
}
void GenerateRintangan(RintanganNode **head, int jumlahRintangan) {
    FreeRintangan(head);

    int batasKiri = 2;
    int batasKanan = GRID_WIDTH - 3;
    int batasAtas = 2;
    int batasBawah = GRID_HEIGHT - 3;

    RintanganNode *prev = NULL;

    for (int i = 0; i < jumlahRintangan * 3; i++) {
        RintanganNode *node = malloc(sizeof(RintanganNode));
        int validPosition = 0;

        
        
        while (!validPosition) {
            int x = (rand() % (batasKanan - batasKiri + 1)) + batasKiri;
            int y = (rand() % (batasBawah - batasAtas + 1)) + batasAtas;

            validPosition = 1;
            RintanganNode *curr = *head;
            while (curr != NULL) {
                if (curr->posisi.x == x && curr->posisi.y == y) {
                    validPosition = 0;
                    break;
                }
                curr = curr->next;
            }

            if (validPosition) {
                node->posisi.x = x;
                node->posisi.y = y;
            }
        }

        node->next = NULL;

       
        if (*head == NULL) {
            *head = node;
        } else {
            prev->next = node;
        }
        prev = node;
    }
}

void GenerateLevel(LevelNode **head, int jumlahLevel){
    LevelNode *prev = NULL;

    for (int i = 0; i < jumlahLevel; i++) {
        LevelNode *node = malloc(sizeof(LevelNode));
        node->next = NULL;
        node->rintanganHead = NULL;

        int jumlahRintangan = 3 + i;  

        
        GenerateRintangan(&node->rintanganHead, jumlahRintangan);

        if (prev == NULL) {
            *head = node;
        } else {
            prev->next = node;
        }
        prev = node;
    }
}






void GenerateEnemy(Enemy *enemy, int count, int level) {
    if (level < 2) return; 
    Position enemyPositions[3][3] = {
        { {12, 12} },                   
        { {10, 14}, {14, 10} },          
        { {9, 9}, {13, 13}, {15, 11} }
    };

    for (int i = 0; i < count; i++) {
        enemy[i].position = enemyPositions[level - 2][i];  
        enemy[i].direction = 1;
        enemy[i].isVertical = i % 2;
    }
}

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