#include <stdlib.h>
#include "raylib.h"
#ifndef Hilmi_H
#define Hilmi_H

typedef struct{
  Vector2 tempBody [2000];
  Vector2 Position;
  Vector2 Speed;
  int Panjang;
  } SNAKE;

void ReverseSnake(SNAKE *SnakE);

#endif
