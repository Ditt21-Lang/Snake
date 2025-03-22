#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define BOX_WIDTH 400
#define BOX_HEIGHT 540

typedef enum {
    MENU,
    MODE_SELECTION,
    HOW_TO_PLAY
} GameScreen;

typedef struct {
    Rectangle border;
    const char *text;
    bool hover;
} Button;

void InitButtons(Button buttons[], const char *texts[], int count, int startY);
void UpdateButtons(Button buttons[], int count, GameScreen *screen);
void DrawButtons(Button buttons[], int count);
void DrawScaledTexture(Texture2D texture, int x, int y, int maxWidth);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snave");
    SetTargetFPS(60);
    
    GameScreen currentScreen = MENU;
    int howToPlayPage = 0;
    
    const char *menuTexts[] = {"Play", "How to Play", "Quit"};
    Button menuButtons[3];
    InitButtons(menuButtons, menuTexts, 3, 300);
    
    const char *modeTexts[] = {"Endless Mode", "Stage Mode", "Back"};
    Button modeButtons[3];
    InitButtons(modeButtons, modeTexts, 3, 300);
    
    Button prevButton = {{SCREEN_WIDTH / 2 - 150, 680, 100, 40}, "Prev", false};
    Button nextButton = {{SCREEN_WIDTH / 2 + 50, 680, 100, 40}, "Next", false};
    Button backButton = {{SCREEN_WIDTH / 2 - 100, 730, 200, 50}, "Back", false};
    
    Texture2D latar = LoadTexture("latar.png");
    Texture2D howToPlayImages[4] = {
        LoadTexture("howto1.png"),
        LoadTexture("howto2.png"),
        LoadTexture("howto3.png"),
        LoadTexture("howto4.png"),
    };
    Texture2D ssGameplay = LoadTexture("ssGameplay.png");
    Texture2D ssGameplay2 = LoadTexture("ssGameplay2.png");
    Texture2D ssGameplay3 = LoadTexture("ssGameplay3.png");
    
    float bgX = 0;
    float scrollSpeed = 75;
    float scale = 1.2;
    
    while (!WindowShouldClose()) {
        bgX -= scrollSpeed * GetFrameTime();
        if (bgX <= -latar.width * scale) bgX += latar.width * scale;
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawTextureEx(latar, (Vector2){bgX, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(latar, (Vector2){bgX + latar.width * scale, 0}, 0.0f, scale, WHITE);
        
        if (currentScreen == MENU) {
            DrawText("Snave", SCREEN_WIDTH / 2 - MeasureText("Snave", 50) / 2, 200, 50, WHITE);
            UpdateButtons(menuButtons, 3, &currentScreen);
            DrawButtons(menuButtons, 3);
        } else if (currentScreen == MODE_SELECTION) {
            UpdateButtons(modeButtons, 3, &currentScreen);
            DrawButtons(modeButtons, 3);
        } else if (currentScreen == HOW_TO_PLAY) {
            DrawRectangle(SCREEN_WIDTH / 2 - 200, 100, BOX_WIDTH, BOX_HEIGHT, DARKGRAY);
            
            DrawText("How to Play", SCREEN_WIDTH / 2 - MeasureText("How to Play", 30) / 2, 110, 30, WHITE);

            Vector2 mousePoint = GetMousePosition();
            
            prevButton.hover = CheckCollisionPointRec(mousePoint, prevButton.border);
            nextButton.hover = CheckCollisionPointRec(mousePoint, nextButton.border);
            backButton.hover = CheckCollisionPointRec(mousePoint, backButton.border);
            
            if (prevButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && howToPlayPage > 0) {
                howToPlayPage--;
            }
            if (nextButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && howToPlayPage < 2) {
                howToPlayPage++;
            }
            if (backButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                currentScreen = MENU;
            }
            
            if (howToPlayPage == 0) {
                int howto1Y = 150;
                int ssGameplayY = howto1Y + 100;
                int howto2Y = ssGameplayY + 180;
                DrawScaledTexture(howToPlayImages[0], SCREEN_WIDTH / 2, howto1Y, BOX_WIDTH);
                DrawScaledTexture(ssGameplay, SCREEN_WIDTH / 2, ssGameplayY, BOX_WIDTH);
                DrawScaledTexture(howToPlayImages[1], SCREEN_WIDTH / 2, howto2Y, BOX_WIDTH);
            } else if (howToPlayPage == 1) {
                DrawScaledTexture(howToPlayImages[2], SCREEN_WIDTH / 2, 150, BOX_WIDTH);
                DrawScaledTexture(ssGameplay2, SCREEN_WIDTH / 2, 350, BOX_WIDTH);
            } else if (howToPlayPage == 2) {
                DrawScaledTexture(howToPlayImages[3], SCREEN_WIDTH / 2, 150, BOX_WIDTH);
                DrawScaledTexture(ssGameplay3, SCREEN_WIDTH / 2, 400, BOX_WIDTH);
            }
            
            DrawRectangleRec(prevButton.border, prevButton.hover ? LIGHTGRAY : GRAY);
            DrawText(prevButton.text, prevButton.border.x + 20, prevButton.border.y + 10, 20, WHITE);
            
            DrawRectangleRec(nextButton.border, nextButton.hover ? LIGHTGRAY : GRAY);
            DrawText(nextButton.text, nextButton.border.x + 20, nextButton.border.y + 10, 20, WHITE);
            
            DrawRectangleRec(backButton.border, backButton.hover ? LIGHTGRAY : GRAY);
            DrawText(backButton.text, backButton.border.x + 60, backButton.border.y + 15, 20, WHITE);
        }
        
        EndDrawing();
    }
    
    UnloadTexture(latar);
    UnloadTexture(ssGameplay);
    UnloadTexture(ssGameplay2);
    UnloadTexture(ssGameplay3);
    for (int i = 0; i < 5; i++) UnloadTexture(howToPlayImages[i]);
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
                else if (i == 1) *screen = HOW_TO_PLAY;
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
        DrawRectangleRec(buttons[i].border, buttons[i].hover ? LIGHTGRAY : GRAY);
        DrawText(buttons[i].text, buttons[i].border.x + 35, buttons[i].border.y + 15, 20, WHITE);
    }
}

void DrawScaledTexture(Texture2D texture, int x, int y, int maxWidth) {
    float scale = (texture.width > maxWidth) ? (float)maxWidth / texture.width : 1.0f;
    int newWidth = texture.width * scale;
    int newHeight = texture.height * scale;
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, 
                   (Rectangle){x - newWidth / 2, y, newWidth, newHeight}, 
                   (Vector2){0, 0}, 0.0f, WHITE);
}
