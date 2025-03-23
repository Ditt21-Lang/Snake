#include <stdio.h>
#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"
#include "Gilang.h"
#include "Marrely.h"
#include "dinding.h"
#define GRID_WIDTH 30
#define GRID_HEIGHT 30

int main (){
    Vector2 snakeHead = {12, 12};
    int lives = 3;
    int count = 0;
    bool alive = true;
    int level = 1;

    Snake snake;
    Rintangan rintangan;
    Enemy enemy[3];

    GenerateRintangan(&rintangan, level);

    if (level >= 2){
    GenerateEnemy(enemy, 3, level);
    }

    while (!WindowShouldClose() && alive) {
        CekTabrakDinding(snakeHead, &lives, &alive);

        CekTabrakRintangan(snakeHead, &rintangan, lives);

        if (level >= 2){
            CekTabrakEnemy(snakeHead, enemy, count, lives);
        }
        UpdateCooldown();
        HandleReverseInput(&snake);
    }
}
