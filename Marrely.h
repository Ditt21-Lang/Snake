#ifndef MARRELY_H
#define MARRELY_H

#include "raylib.h"

#define CELL_SIZE 20
#define GRID_WIDTH  (500 / CELL_SIZE)  
#define GRID_HEIGHT (400 / CELL_SIZE)  
#define MAX_LENGTH 100

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


void GenerateMakanan(Makanan *makanan, Rintangan *rintangan);
void GenerateRintangan(Rintangan *rintangan, int level);
void DrawGame(Makanan *makanan, Rintangan *rintangan, int score, int lives, int level, Texture2D background);

#endif
