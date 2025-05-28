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

void DrawGame(Makanan *makanan, RintanganNode *rintangan, EnemyList *enemies, int enemyCount, int score, int level, 
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
    
    Enemy *Ecurr = enemies->head;
    while (Ecurr != NULL) {
        DrawTexturePro(enemyTexture, (Rectangle){0, 0, enemyTexture.width, enemyTexture.height}, 
                       (Rectangle){Ecurr->position.x * CELL_SIZE, Ecurr->position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
        Ecurr = Ecurr->next;
    }
    DrawRectangle(0, 700, GetScreenWidth(), 200,  LIGHTGRAY);
    DrawRectangle(0, 600, GetScreenWidth(), 100, (Color){0, 0, 0, 200}); 

}