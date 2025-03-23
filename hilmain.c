#include <stdio.h>
#include "Marrely.h"
#include "Hilmi.h"

int main() {
    Rintangan rintangan;
    Enemy enemy[3];
    Vector2 snakeHead = {12, 12}; // Kepala ular
    int level = 2;
    int lives = 3;

    
    GenerateRintangan(&rintangan, level);
    GenerateEnemy(enemy, level, level);

    CekTabrakRintangan(snakeHead, &rintangan, NULL, &lives);
    CekTabrakEnemy(snakeHead, enemy, level, &lives);

    return 0;
}
