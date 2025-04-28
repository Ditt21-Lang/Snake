#ifndef Hilmi_H
#define Hilmi_H
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "Gilang.h"
#include "Marrely.h"
#include <stdbool.h>
#define REVERSE_COOLDOWN 20.0f

extern float reverseTimer;

void ReverseSnake(Snake *Snake);
void HandleReverseInput(Snake *Snake);
void UpdateCooldown();
bool CekTabrakDinding(Snake *snake, int *lives, bool *alive);
bool CekTabrakRintangan(Vector2 head, Rintangan *rintangan, int *lives, bool *alive);
bool CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives, bool *alive);

#endif
