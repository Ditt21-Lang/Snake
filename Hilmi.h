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

// membutuhkan header Gilang.h untuk tipe data SnakeNode dan Snake
// membutuhkan header Marrely.h untuk tipe data RintanganNode, EnemyList dan Enemy

void ReverseSnake(Snake *snake); //membalikkan arah ular
void UpdateCooldown(); //memperbarui cooldown
bool CekTabrakDinding(Snake *snake); //mengecek jika kepala ular menabrak dinding
bool CekTabrakRintangan(Vector2 head, RintanganNode *rintanganHead); //mengecek jika kepala ular menabrak rintangan
bool CekTabrakEnemy(Snake ular, EnemyList list); //mengecek jika ular menabrak enemy

EnemyList GenerateEnemy(int level); //membuat list enemy berdasarkan level
void FreeEnemyList(EnemyList *list); //membebaskan memori list enemy
void MoveEnemy(EnemyList *list); //menggerakkan enemy sesuai arah dan batas

#endif
