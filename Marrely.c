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


void GenerateRintangan(RintanganNode **head, int *level) {
    if (*level < 1 || *level > 5) return;  
  
    
    Position levelRintangan[5][10] = {
    { {10, 12}, {14, 14}, {12, 8} },
    { {9, 11}, {15, 13}, {11, 9}, {13, 15} },
    { {8, 10}, {16, 12}, {12, 14}, {14, 8}, {10, 16} },
    { {9, 13}, {11, 15}, {13, 9}, {15, 11}, {12, 12}, {14, 14} },
    { {10, 14}, {14, 10}, {12, 16}, {16, 12}, {8, 12}, {12, 8}, {12, 12} }
}; 

*head = NULL;
    

    for (int i = 0; i < *level; i++) {
       RintanganNode *newNode = (RintanganNode *)malloc(sizeof(RintanganNode));
       newNode->posisi = levelRintangan[*level - 1][i];
       newNode->next = *head;
       *head = newNode;
    }
}
void DrawGame(Makanan *makanan, RintanganNode *rintanganHead, EnemyList *enemy, int enemyCount,
              int score, int level,
              Texture2D background, Texture2D borderTexture,
              Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture) {

    ClearBackground(RAYWHITE);
    DrawTexture(borderTexture, 0, 0, WHITE);
    DrawTexture(background, 0, 0, WHITE);

   RintanganNode *curr = rintanganHead;
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
    
    Enemy *Ecurr = enemy->head;
    while (Ecurr != NULL) {
        DrawTexturePro(enemyTexture, (Rectangle){0, 0, enemyTexture.width, enemyTexture.height}, 
                       (Rectangle){Ecurr->position.x * CELL_SIZE, Ecurr->position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                       (Vector2){0, 0}, 0, WHITE);
        Ecurr = Ecurr->next;
    }
    DrawRectangle(0, 700, GetScreenWidth(), 200,  LIGHTGRAY);
    DrawRectangle(0, 600, GetScreenWidth(), 100, (Color){0, 0, 0, 200}); 

}