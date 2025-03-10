#include <stdlib.h>
#include "raylib.h"
#ifndef Hilmi_H
#define Hilmi_H

typedef struct{
  Vector2 tempBody [2000];
  Vector2 position;
  Vector2 speed;
  int panjang;
  } SNAKE;

void ReverseSnake(SNAKE *SnakE);

#endif
