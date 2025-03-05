#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

typedef enum {
    MENU,
    MODE_SELECTION
} GameScreen;

typedef struct {
    Rectangle border;
    const char *text;
    bool hover;
} Button;

void InitButtons(Button buttons[], const char *texts[], int count, int startY);
void UpdateButtons(Button buttons[], int count, GameScreen *screen);
void DrawButtons(Button buttons[], int count);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
    SetTargetFPS(60);
    
    GameScreen currentScreen = MENU;
    
    // Tombol main menu
    const char *menuTexts[] = {"Play", "Option", "Quit"};
    Button menuButtons[3];
    InitButtons(menuButtons, menuTexts, 3, 300);
    
    // Tombol pilihan mode
    const char *modeTexts[] = {"Endless Mode", "Stage Mode", "Back"};
    Button modeButtons[3];
    InitButtons(modeButtons, modeTexts, 3, 300);
    
    Texture2D latar = LoadTexture("latar.png");
    
    float bgX = 0;          
    float scrollSpeed = 75; 
    float scale = 1.2;      

    while (!WindowShouldClose()) {
       
        bgX -= scrollSpeed * GetFrameTime();

        if (bgX <= -latar.width * scale) {
            bgX += latar.width * scale;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // pake 2 latar yang sama, biar transisinya halus
        DrawTextureEx(latar, (Vector2){bgX, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(latar, (Vector2){bgX + latar.width * scale, 0}, 0.0f, scale, WHITE);

        if (currentScreen == MENU) {
            DrawText("Snake Game", SCREEN_WIDTH / 2 - MeasureText("Snake Game", 50) / 2, 200, 50, WHITE);
            
            UpdateButtons(menuButtons, 3, &currentScreen);
            DrawButtons(menuButtons, 3);
        } else if (currentScreen == MODE_SELECTION) {
            UpdateButtons(modeButtons, 3, &currentScreen);
            DrawButtons(modeButtons, 3);
        }

        EndDrawing();
    }

    UnloadTexture(latar);
    CloseWindow();
    return 0;
}

void InitButtons(Button buttons[], const char *texts[], int count, int startY) {
    for (int i = 0; i < count; i++) {
        buttons[i].border = (Rectangle){200, startY + i * 100, 200, 50};
        buttons[i].text = texts[i];
        buttons[i].hover = false;
    }
}

void UpdateButtons(Button buttons[], int count, GameScreen *screen) {
    Vector2 mousePoint = GetMousePosition();
    for (int i = 0; i < count; i++) {
        buttons[i].hover = CheckCollisionPointRec(mousePoint, buttons[i].border);
        if (buttons[i].hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (*screen == MENU) {
                if (i == 0) *screen = MODE_SELECTION;
                else if (i == 2) {
                    CloseWindow();
                    exit(0);
                }
            } else if (*screen == MODE_SELECTION) {
                if (i == 2) *screen = MENU;
            }
        }
    }
}

void DrawButtons(Button buttons[], int count) {
    for (int i = 0; i < count; i++) {
        Color btnColor = buttons[i].hover ? LIGHTGRAY : GRAY;
        DrawRectangleRec(buttons[i].border, btnColor);
        DrawText(buttons[i].text, buttons[i].border.x + 35, buttons[i].border.y + 15, 20, WHITE);
    }
}
