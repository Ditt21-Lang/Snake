#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"
#include "Gilang.h"

void ReverseSnake(Snake *snake) {
    for (int i = 0; i < snake->length / 2; i++) {
        Vector2 temp = snake->body[i];
        snake->body[i] = snake->body[snake->length - 1 - i];
        snake->body[snake->length - 1 - i] = temp;
     }
    snake->position = snake->body[0];
    Vector2 diff = (Vector2){ snake->body[0].x - snake->body[1].x, 
                              snake->body[0].y - snake->body[1].y };
    snake->speed = diff;
}

    if (IsKeyPressed(KEY_SPACE)) {
        ReverseSnake(&snake);
    }
