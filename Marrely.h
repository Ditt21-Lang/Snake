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

typedef struct RintanganNode {
    Position posisi;
    struct RintanganNode *next;
} RintanganNode;

// Fungsi utama
void GenerateMakanan(Makanan *makanan, RintanganNode *rintanganHead);
void GenerateRintangan(RintanganNode **, int level);
void GenerateEnemy(Enemy *enemy, int count, int level);
void DrawGame(Makanan *makanan, RintanganNode *rintanganHead, Enemy *enemy, int enemyCount,
              int score, int level,
              Texture2D background, Texture2D borderTexture,
              Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture);
void MoveEnemy(Enemy *enemy, int enemyCount);
void FreeRintangan(RintanganNode **head);

#endif
