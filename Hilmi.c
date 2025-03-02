#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"

void ReverseSnake(Snake *snake){
    Vector2 tempBody[100];

    for (int i = 0; i < snake->panjang; i++){
        tempBody[i] = snake->badan[snake->panjang - 1 - i];
    }

    for (int i = 0; i < snake->panjang; i++){
        snake->badan[i] = tempBody[i];
    }

    snake->position = snake->body[0];

    if(snake->speed.x !=0) {
    snake->speed.x = -snake->speed.x; }
    if(snake->speed.y !=0) {
    snake->speed.y = -snake->speed.y; }

    if (IsKeyPressed(KEY_SPACE)) {
        ReverseSnake(snake);
    }
}
