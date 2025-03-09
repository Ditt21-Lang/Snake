#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#define CELL_SIZE 20
#define GRID_WIDTH  (500 / CELL_SIZE)  
#define GRID_HEIGHT (400 / CELL_SIZE)  
#define SCREEN_WIDTH  500
#define SCREEN_HEIGHT 400
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

typedef struct {
    Position body[MAX_LENGTH];
    int length;
    int dx, dy;
} Snake;

void GenerateMakanan(Makanan *makanan, Rintangan *rintangan, Snake *snake);
void GenerateRintangan(Rintangan *rintangan, int level);
void InitSnake(Snake *snake);
void UpdateSnake(Snake *snake);
int CheckCollision(Snake *snake, Rintangan *rintangan);
void DrawGame(Makanan *makanan, Rintangan *rintangan, Snake *snake, int score, int lives, int level, Texture2D background);

#endif
