#ifndef MARRELY_H
#define MARRELY_H

#include "raylib.h"

#define CELL_SIZE 20
#define GRID_WIDTH  (520 / CELL_SIZE)  
#define GRID_HEIGHT (520 / CELL_SIZE)  
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 800

typedef struct {
    int x, y;
} Position;


typedef struct {
    Position position;
} Makanan;

typedef struct {
    Position position;
    int direction;
    int isVertical;
} Enemy;

typedef struct EnemyNode {
    Enemy enemy;
    struct EnemyNode *next;
} EnemyNode;

typedef struct LevelEnemyData {
    int Level;
    EnemyNode *enemyList;
    struct LevelEnemyData *next;
} LevelEnemyData;

typedef struct RintanganNode {
    Position posisi;
    struct RintanganNode *next;
} RintanganNode;

void GenerateMakanan(Makanan *makanan, RintanganNode *rintanganHead);
void GenerateRintangan(RintanganNode **head, int level);
void GenerateEnemy(EnemyNode **head, int count, int level);
void DrawGame(Makanan *makanan, RintanganNode *rintanganHead, EnemyNode *enemyHead, 
              int score, int level, 
              Texture2D background, Texture2D borderTexture, 
              Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture)
void MoveEnemy(EnemyNode *head);
void FreeRintangan(RintanganNode *head);
void FreeEnemy(EnemyNode *head);

#endif



