#include <stdio.h>
#include "raylib.h"
#include "Marrely.h"
#ifndef GILANG_H
#define GILANG_H

typedef struct{
    Vector2 position; //Menyimpan dua nilai, menentukan nilai koordinat x dan y. 
    Vector2 speed;
    int panjang;
    Vector2 badan[100];
    Rectangle snakeSprites[100];
    Texture2D tekstur;
} Snake;

void InitSnake(Snake *Snake);
void DrawSnake(Snake *Snake);
void UpdateSnake(Snake *Snake);
bool cekTabrakan(Snake *Snake);

//Dibutuhkan header Marrely
bool CheckMakanan(Snake *snake, Makanan *Makanan);

#endif