#ifndef Hilmi_H
#define Hilmi_H
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "Gilang.h"
#include "Marrely.h"
#include <stdbool.h>
#define GRID_WIDTH 30
#define GRID_HEIGHT 30
#define REVERSE_COOLDOWN 20.0f

typedef struct{
    Position rintangan[10];
    int count;
} Rintangan;

typedef struct{
    Position position;
    int direction;
    int isVertical;
    int count;
} Enemy;

extern float reverseTimer;

void ReverseSnake(Snake *Snake);
void HandleReverseInput(Snake *Snake);
void UpdateCooldown();
void CekTabrakDinding(Vector2 head, int *lives, bool *alive);
void CekTabrakRintangan(Vector2 head, Rintangan *rintangan, int *lives);
void CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives);

#endif
