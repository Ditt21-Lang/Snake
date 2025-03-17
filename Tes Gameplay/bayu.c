#include "bayu.h"
#include <stdlib.h>

void InitSnake(Snake *snake) {
    snake->length = 3;
    snake->body[0] = (Vector){GRID_WIDTH / 2, GRID_HEIGHT / 2}; // kepala
    snake->body[1] = (Vector){GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2}; // badan
    snake->body[2] = (Vector){GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2}; // ekor
    snake->direction = (Vector){1, 0};
}

void MoveSnake(Snake *snake, bool *alive) {
    Vector newHead = {snake->body[0].x + snake->direction.x, snake->body[0].y + snake->direction.y};
    
    // cek nabrak dinding
    if (newHead.x < 2 || newHead.x >= GRID_WIDTH - 2 || newHead.y < 2 || newHead.y >= GRID_HEIGHT - 2) {
        *alive = false;
        return;
    }
    
    // cek nabrak diri sendiri
    for (int i = 0; i < snake->length; i++) {
        if (newHead.x == snake->body[i].x && newHead.y == snake->body[i].y) {
            *alive = false;
            return;
        }
    }
    
    // geser semua bagian tubuh ular ke posisi sebelumnya
    for (int i = snake->length; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[0] = newHead;
}

void SpawnFood(Vector *food, Snake *snake) {
    bool valid;
    do {
        valid = true;
        food->x = (rand() % (GRID_WIDTH - 4)) + 2;
        food->y = (rand() % (GRID_HEIGHT - 4)) + 2;
        
        // supaya makanan tidak muncul di tubuh ular
        for (int i = 0; i < snake->length; i++) {
            if (food->x == snake->body[i].x && food->y == snake->body[i].y) {
                valid = false;
                break;
            }
        }
    } while (!valid);
}

int snakeSpritesheet(Vector prevDirection, Vector nextDirection) {
    if (prevDirection.x == -1 && nextDirection.y == -1) return 4; // kiri ke Atas
    if (prevDirection.x == 1 && nextDirection.y == -1) return 3;  // kanan ke Atas
    if (prevDirection.x == -1 && nextDirection.y == 1) return 6;  // kiri ke Bawah
    if (prevDirection.x == 1 && nextDirection.y == 1) return 5;   // kanan ke Bawah
    if (prevDirection.y == -1 && nextDirection.x == -1) return 4; // atas ke Kiri
    if (prevDirection.y == -1 && nextDirection.x == 1) return 3;  // atas ke Kanan
    if (prevDirection.y == 1 && nextDirection.x == -1) return 6;  // bawah ke Kiri
    if (prevDirection.y == 1 && nextDirection.x == 1) return 5;   // bawah ke Kanan
    return -1; 
}