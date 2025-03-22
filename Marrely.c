#include "Marrely.h"
#include <stdlib.h>
#include <time.h>

void GenerateMakanan(Makanan *makanan, Rintangan *rintangan) {
    int validPosition = 0;

    while (!validPosition) {
        makanan->position.x = rand() % GRID_WIDTH;  
        makanan->position.y = rand() % GRID_HEIGHT;
        validPosition = 1;

        for (int i = 0; i < rintangan->count; i++) {
            if (rintangan->rintangan[i].x == makanan->position.x &&
                rintangan->rintangan[i].y == makanan->position.y) {
                validPosition = 0;
                break;
            }
        }
    }
}

void GenerateRintangan(Rintangan *rintangan, int level) {
    rintangan->count = level;
    
    Position levelRintangan[5][10] = {
        { {3, 7}, {12, 5}, {8, 14} },
        { {2, 10}, {7, 3}, {14, 8}, {11, 12} },
        { {5, 2}, {9, 6}, {3, 13}, {16, 10}, {12, 17} },
        { {1, 9}, {8, 4}, {13, 11}, {6, 15}, {17, 7}, {20, 14} },
        { {0, 5}, {11, 3}, {4, 12}, {15, 6}, {9, 18}, {19, 8}, {23, 20} }
    };

    for (int i = 0; i < rintangan->count; i++) {
        rintangan->rintangan[i] = levelRintangan[level - 1][i];
    }
}

void MoveEnemy(Enemy *enemy) {
    if (enemy->isVertical) {
        enemy->position.y += enemy->direction;
        if (enemy->position.y < 0 || enemy->position.y >= GRID_HEIGHT) {
            enemy->direction *= -1;
        }
    } else {
        enemy->position.x += enemy->direction;
        if (enemy->position.x < 0 || enemy->position.x >= GRID_WIDTH) {
            enemy->direction *= -1;
        }
    }
}
