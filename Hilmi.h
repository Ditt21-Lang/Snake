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


// void ReverseSnake(Snake *Snake);
void HandleReverseInput(Snake *Snake);
void UpdateCooldown();
bool CekTabrakDinding(Snake *snake);
bool CekTabrakRintangan(Vector2 head, RintanganNode *rintanganHead);
bool CekTabrakEnemy(Vector2 head, Enemy *enemy, int *count, int *lives, bool *alive);

void FreeRintangan(RintanganNode **head);
EnemyList GenerateEnemy(int level);
<<<<<<< HEAD
void FreeEnemyList(EnemyList *list)
=======
void FreeEnemyList(EnemyList *list);
void MoveEnemy(EnemyList *list);
// EnemyList GenerateEnemy(int level);
>>>>>>> a7ce359f2e42e4854833a14ae05308a936a5b001

#endif
