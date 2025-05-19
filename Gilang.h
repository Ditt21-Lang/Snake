#include <stdio.h>
#include "raylib.h"
#include "Marrely.h"
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
    Texture2D tekstur;
    int panjang;
} Snake;

void InitSnake(Snake *snake);
void DrawSnake(Snake *snake, Texture2D texture);
void UpdateSnake(Snake *snake);
bool cekTabrakan(Snake *snake);
void tambahNode(Snake *snake);
Vector2 getDir(Vector2 A, Vector2 B);

//Dibutuhkan header Marrely
bool CheckMakanan(Snake *snake, Makanan *food);

#endif