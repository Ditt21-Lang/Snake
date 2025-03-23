#include <stdlib.h>
#include "raylib.h"
#include "Gilang.h"
#ifndef Hilmi_H
#define Hilmi_H
#define GRID_WIDTH 30
#define GRID_HEIGHT 30
#define REVERSE_COOLDOWN 20.0f

typedef struct{
    Vector2 rintangan[10];
    int count;
} Rintangan;

typedef struct{
    Vector2 enemy[3];
    int count;
} Enemy;

extern float reverseTimer;

void ReverseSnake(Snake *Snake);
void HandleReverseInput(Snake *Snake);
void UpdateCooldown();
void CekTabrakBorder(Vector2 head, int *lives);
void CekTabrakRintangan(Vector2 head, Rintangan *rintangan, int *count, int *lives);
void CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives);

#endif
