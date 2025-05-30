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


void ReverseSnake(Snake *snake);
void HandleReverseInput(Snake *Snake);
void UpdateCooldown();
bool CekTabrakDinding(Snake *snake);
bool CekTabrakRintangan(Vector2 head, RintanganNode *rintanganHead);
bool CekTabrakEnemy(Vector2 head, Enemy *enemyHead);

EnemyList GenerateEnemy(int level);
void FreeEnemyList(EnemyList *list);
void MoveEnemy(EnemyList *list);
#endif
