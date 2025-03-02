#include <stdio.h>
#include "raylib.h"

typedef struct{
    Vector2 position; //Menyimpan dua nilai, menentukan nilai koordinat x dan y. 
    Vector2 speed;
    int panjang;
    Vector2 badan[100];
} Snake;

void InitSnake(Snake *Snake);
void DrawSnake(Snake *Snake);
void UpdateSnake(Snake *Snake);
bool cekTabrakan(Snake *Snake);