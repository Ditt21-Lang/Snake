#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define CELL_SIZE 20
#define GRID_WIDTH 30
#define GRID_HEIGHT 30
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

typedef struct {
    int x, y;
} Vector;

typedef struct {
    Vector body[GRID_WIDTH * GRID_HEIGHT];
    int length;
    Vector direction;
} Snake;

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

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snave");
    SetTargetFPS(10);
    
    Texture2D tanah = LoadTexture("tanah.png");
    Texture2D dinding = LoadTexture("dinding.png");
    Texture2D teksturUlar = LoadTexture("teksturUlar.png");
    Texture2D tikus = LoadTexture("tikus.png");
    
    Rectangle snakeSprites[8];
    for (int i = 0; i < 8; i++) {
        snakeSprites[i] = (Rectangle){i * 20, 0, 20, 20};
    }
    
    Snake snake;
    InitSnake(&snake);
    
    Vector food;
    SpawnFood(&food, &snake);
    
    bool alive = true;
    
    while (!WindowShouldClose()) {
        if (alive) {
            // update arah pergerakan
            if (IsKeyPressed(KEY_RIGHT) && snake.direction.x == 0) snake.direction = (Vector){1, 0};
            if (IsKeyPressed(KEY_LEFT) && snake.direction.x == 0) snake.direction = (Vector){-1, 0};
            if (IsKeyPressed(KEY_UP) && snake.direction.y == 0) snake.direction = (Vector){0, -1};
            if (IsKeyPressed(KEY_DOWN) && snake.direction.y == 0) snake.direction = (Vector){0, 1};
            
            MoveSnake(&snake, &alive);
            
            // periksa apakah ular makan makanan
            if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
                snake.length++;
                SpawnFood(&food, &snake);
            }
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(tanah, 0, 0, WHITE);
        DrawTexture(dinding, 0, 0, WHITE);
    
        for (int i = 0; i < snake.length; i++) {
            int spriteIndex = 1; // default badan lurus (atas/bawah)
            float rotation = 0;

            if (i == 0) { // kepala
                spriteIndex = 0;
                if (snake.direction.x == 1) rotation = 90;
                if (snake.direction.x == -1) rotation = 270;
                if (snake.direction.y == 1) rotation = 180;
            } else if (i == snake.length - 1) { // ekor
                spriteIndex = 2;
                Vector tailDirection = {snake.body[i - 1].x - snake.body[i].x, snake.body[i - 1].y - snake.body[i].y};
                if (tailDirection.x == 1) rotation = 90;
                if (tailDirection.x == -1) rotation = 270;
                if (tailDirection.y == 1) rotation = 180;
            } else { // badan
                Vector prevDirection = {snake.body[i - 1].x - snake.body[i].x, snake.body[i - 1].y - snake.body[i].y};
                Vector nextDirection = {snake.body[i + 1].x - snake.body[i].x, snake.body[i + 1].y - snake.body[i].y};

                // cek apakah badan ular berbelok
                spriteIndex = snakeSpritesheet(prevDirection, nextDirection);
                if (spriteIndex == -1) {
                    if (prevDirection.x == 1 || prevDirection.x == -1) {  // ke kanan/kiri
                        spriteIndex = 7; // sprite untuk badan lurus ke kiri/kanan
                    } else if (prevDirection.y == 1 || prevDirection.y == -1) {  // ke atas/bawah
                        spriteIndex = 1; // sprite untuk badan lurus ke atas/bawah
                    }
                }
            }

            // posisi dan rotasi
            Vector2 position = {(float)snake.body[i].x * CELL_SIZE + CELL_SIZE / 2, (float)snake.body[i].y * CELL_SIZE + CELL_SIZE / 2};
            Rectangle destRect = {position.x, position.y, CELL_SIZE, CELL_SIZE};
            Vector2 origin = {CELL_SIZE / 2, CELL_SIZE / 2};

            // gambar sprite
            DrawTexturePro(teksturUlar, snakeSprites[spriteIndex], destRect, origin, rotation, WHITE);
        }
    
        // makanannya tikus
        DrawTexture(tikus, food.x * CELL_SIZE, food.y * CELL_SIZE, WHITE);

        if (!alive) {
            DrawText("Pencet R Bang", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, WHITE);
            if (IsKeyPressed(KEY_R)) {
                InitSnake(&snake);
                alive = true;
                SpawnFood(&food, &snake);
            }
        }

        EndDrawing();
    }
    
    UnloadTexture(tanah);
    UnloadTexture(dinding);
    UnloadTexture(teksturUlar);
    UnloadTexture(tikus);
    CloseWindow();
    
    return 0;
}