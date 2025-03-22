#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "Marrely.h"
#include "Gilang.h"
#include "Bayu.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

int main(){
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snave");
    SetTargetFPS(60);
    ClearBackground(RAYWHITE);
    
    GameScreen currentScreen = MENU;
    int howToPlayPage = 0;
    int fps = 60;


    Snake snake;
    Makanan makanan;
    Rintangan rintangan;
    Enemy enemy;

    int score = 0;
    int level = 0;
    int enemyCount = 0;
    
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
    Texture2D tanah = LoadTexture("tanah.png");
    Texture2D musuh = LoadTexture("krtTambang.png");
    Texture2D obstacle = LoadTexture ("obstacle.png");
    Texture2D food = LoadTexture ("tikus.png");
    
    float bgX = 0;
    float scrollSpeed = 75;
    float scale = 1.2;

    GenerateRintangan(&rintangan, level);
    GenerateMakanan(&makanan, &rintangan);

    InitSnake(&snake);

    while(!WindowShouldClose()){

        bgX -= scrollSpeed * GetFrameTime();
        if (bgX <= -latar.width * scale) bgX += latar.width * scale;

        BeginDrawing();

        DrawTextureEx(latar, (Vector2){bgX, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(latar, (Vector2){bgX + latar.width * scale, 0}, 0.0f, scale, WHITE);

        if (currentScreen == GAMEPLAY && fps != 10) {
            fps = 10;
            SetTargetFPS(fps);
            UnloadTexture(latar);
        }
        
        if (currentScreen != GAMEPLAY && fps != 60) {
            fps = 60;
            SetTargetFPS(fps);
        }

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

        else if (currentScreen == GAMEPLAY){
            ClearBackground(RAYWHITE);
            
            DrawGame(&makanan, &rintangan, &enemy, enemyCount, score, 0, tanah, food, musuh, obstacle );
            if(!cekTabrakan(&snake)){
                UpdateSnake(&snake);
                DrawSnake(&snake);
            }
            else{
                DrawText("Game Over", LEBAR_LAYAR/2, TINGGI_LAYAR/2, 25, RED);
            }
    
            if(CheckMakanan(&snake, &makanan)){
                score += 100;
                snake.panjang++;
                GenerateMakanan(&makanan, &rintangan);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
