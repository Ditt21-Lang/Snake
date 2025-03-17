#ifndef BAYU_H
#define BAYU_H

#include "raylib.h"
#include <stdbool.h>

#define CELL_SIZE 20
#define GRID_WIDTH 30
#define GRID_HEIGHT 30
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

typedef struct {
    int x, y;
} Vector;

typedef struct {
    Vector body[GRID_WIDTH * GRID_HEIGHT];
    int length;
    Vector direction;
} Snake;

void InitSnake(Snake *snake);
void MoveSnake(Snake *snake, bool *alive);
void SpawnFood(Vector *food, Snake *snake);
int snakeSpritesheet(Vector prevDirection, Vector nextDirection);

#endif