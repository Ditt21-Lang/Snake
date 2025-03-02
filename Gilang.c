#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define CELL_SIZE 20
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)

typedef struct Snake {
    Vector2 position;
    Vector2 speed;
    int length;
    Vector2 body[100];
} Snake;

typedef struct Food {
    Vector2 position;
} Food;

typedef enum GameState { 
    MAIN_MENU, 
    PLAYING, 
    GAME_OVER 
} GameState;

void DrawWalls() {
    for (int x = 0; x < SCREEN_WIDTH; x += CELL_SIZE) {
        DrawRectangle(x, 0, CELL_SIZE, CELL_SIZE, BLACK);
        DrawRectangle(x, SCREEN_HEIGHT - CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
    }
    for (int y = 0; y < SCREEN_HEIGHT; y += CELL_SIZE) {
        DrawRectangle(0, y, CELL_SIZE, CELL_SIZE, BLACK);
        DrawRectangle(SCREEN_WIDTH - CELL_SIZE, y, CELL_SIZE, CELL_SIZE, BLACK);
    }
}

void InitSnake(Snake *snake) {
    snake->position = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    snake->speed = (Vector2){ CELL_SIZE, 0 };
    snake->length = 3; // Mulai dengan panjang 3
    snake->body[0] = snake->position;
    // Set posisi tubuh ular lainnya
    for (int i = 1; i < snake->length; i++) {
        snake->body[i] = (Vector2){ snake->position.x - i * CELL_SIZE, snake->position.y };
    }
}

void UpdateSnake(Snake *snake) {
    // Pindahkan tubuh ular
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    // Perbarui posisi kepala ular
    snake->position.x += snake->speed.x;
    snake->position.y += snake->speed.y;
    // Set posisi kepala ular sebagai bagian pertama tubuh
    snake->body[0] = snake->position;
}

void DrawSnake(Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        DrawRectangle(snake->body[i].x, snake->body[i].y, CELL_SIZE, CELL_SIZE, BLACK);
    }
}

void InitFood(Food *food) {
    food->position = (Vector2){ (rand() % (GRID_WIDTH - 2) + 1) * CELL_SIZE, (rand() % (GRID_HEIGHT - 2) + 1) * CELL_SIZE };
}

void DrawFood(Food *food) {
    DrawRectangle(food->position.x, food->position.y, CELL_SIZE, CELL_SIZE, RED);
}

bool CheckCollision(Snake *snake, Food *food) {
    return (snake->position.x == food->position.x && snake->position.y == food->position.y);
}

bool CheckWallCollision(Snake *snake) {
    return (snake->position.x <= 0 || snake->position.x >= SCREEN_WIDTH - CELL_SIZE ||
            snake->position.y <= 0 || snake->position.y >= SCREEN_HEIGHT - CELL_SIZE);
}

bool CheckSelfCollision(Snake *snake) {
    for (int i = 1; i < snake->length; i++) {
        if (snake->position.x == snake->body[i].x && snake->position.y == snake->body[i].y) {
            return true; // Snake head collides with its body
        }
    }
    return false;
}

void DrawMainMenu() {
    DrawText("Snake Game", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 30, BLACK);
    DrawText("Press ENTER to Play", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 20, BLACK);
}

void DrawGameOver() {
    DrawText("Game Over", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 30, BLACK);
    DrawText("Press ENTER to Restart", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 20, BLACK);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    SetTargetFPS(10);
    
    Snake snake;
    Food food;
    GameState gameState = MAIN_MENU;
    
    while (!WindowShouldClose()) {
        switch (gameState) {
            case MAIN_MENU:
                if (IsKeyPressed(KEY_ENTER)) {
                    InitSnake(&snake);
                    InitFood(&food);
                    gameState = PLAYING;
                }
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawMainMenu();
                EndDrawing();
                break;
            
            case PLAYING:
                if (IsKeyPressed(KEY_UP) && snake.speed.y == 0) {
                    snake.speed = (Vector2){ 0, -CELL_SIZE };
                } else if (IsKeyPressed(KEY_DOWN) && snake.speed.y == 0) {
                    snake.speed = (Vector2){ 0, CELL_SIZE };
                } else if (IsKeyPressed(KEY_LEFT) && snake.speed.x == 0) {
                    snake.speed = (Vector2){ -CELL_SIZE, 0 };
                } else if (IsKeyPressed(KEY_RIGHT) && snake.speed.x == 0) {
                    snake.speed = (Vector2){ CELL_SIZE, 0 };
                }
                
                UpdateSnake(&snake);
                
                if (CheckCollision(&snake, &food)) {
                    snake.length++;
                    InitFood(&food);
                }
                
                if (CheckWallCollision(&snake) || CheckSelfCollision(&snake)) {
                    gameState = GAME_OVER;
                }
                
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawWalls();
                DrawSnake(&snake);
                DrawFood(&food);
                EndDrawing();
                break;
            
            case GAME_OVER:
                if (IsKeyPressed(KEY_ENTER)) {
                    gameState = MAIN_MENU;
                }
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawGameOver();
                EndDrawing();
                break;
        }
    }
    
    CloseWindow();
return 0;
}