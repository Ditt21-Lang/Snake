#include <stdlib.h>
#include "raylib.h"
#ifndef HILMI_H
#define HILMI_H

typedef struct{
  Vector2 tempBody [100];
  Vector2 position;
  Vector2 speed;
  int panjang;
  } Snake;

void ReverseSnake(Snake *snake);

#endif
