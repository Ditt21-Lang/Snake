#include <stdio.h>
#include "raylib.h"
#include "Marrely.h"
#include "Hilmi.h"
#ifndef GILANG_H
#define GILANG_H

typedef struct SnakeNode{
    Vector2 position;
    Rectangle sprite;
    struct SnakeNode* next;
    struct SnakeNode* prev;
}SnakeNode;

typedef struct{
    SnakeNode* head;
    SnakeNode* tail;
    Vector2 speed;
    int panjang;
    Texture2D tekstur;
} Snake;

void InitSnake(Snake *snake);
void DrawSnake(Snake *snake, Texture2D texture);
void UpdateSnake(Snake *snake);
bool cekTabrakan(Snake *snake);
void tambahEkor(Snake *snake);
void freeSnake(Snake *snake);


//Dibutuhkan header Marrely
bool CheckMakanan(Snake *snake, Makanan *Makanan);


#endif