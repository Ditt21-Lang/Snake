#ifndef MARRELY_H
#define MARRELY_H

#include "raylib.h"

#define CELL_SIZE 20
#define GRID_WIDTH  (600 / CELL_SIZE)  
#define GRID_HEIGHT (800 / CELL_SIZE)  
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 800

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position position;
} Makanan;

typedef struct {
    Position rintangan[10];
    int count;
} Rintangan;

typedef struct {
    Position position;
    int direction;
    int isVertical;
} Enemy;

void GenerateMakanan(Makanan *makanan, Rintangan *rintangan);
void GenerateRintangan(Rintangan *obstacle, int level);
void GenerateEnemy(Enemy *enemy, int count, int level);
void DrawGame(Makanan *makanan, Rintangan *rintangan, Enemy *enemies, int enemyCount, int score, int lives, int level, Texture2D borderTexture, Texture2D background, Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture);
void MoveEnemy(Enemy *enemy);

#endif



