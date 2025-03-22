#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"
#include "Gilang.h"

void ReverseSnake(Snake *snake) {
    for (int i = 0; i < snake->panjang / 2; i++) {
        Vector2 temp = snake->badan[i];
        snake->badan[i] = snake->badan[snake->panjang - 1 - i];
        snake->badan[snake->panjang - 1 - i] = temp;
     }
    snake->position = snake->badan[0];
    Vector2 diff = (Vector2){ snake->badan[0].x - snake->badan[1].x, 
                              snake->badan[0].y - snake->badan[1].y };
    snake->speed = diff;

}
