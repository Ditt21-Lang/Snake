#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "Marrely.h"
#include "Gilang.h"
#include "Bayu.h"
#include "emir.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

int main(){
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snave");
    InitAudioDevice();
    SetTargetFPS(60);
    ClearBackground(RAYWHITE);
    
    GameScreen currentScreen = MENU;
    int howToPlayPage = 0;
    int fps = 60;


    Snake snake;
    Makanan makanan;
    Rintangan rintangan;
    Enemy enemy;

    //peluru
    peluru mpeluru={0};
    mpeluru.speed=50;
    mpeluru.status=false;

    //portal
    portal mportal[2];
    mportal[0].status=false;
    mportal[1].status=false;

    int score = 0;
    int level = 0;
    int lives = 0;
    int enemyCount = 0;
    int buffer;

    bool isMusicPlaying = false;
    bool isStartPlaying = false;
    bool isGameOver = false;
    bool isSoundOver = false;
    
    const char *menuTexts[] = {"Play", "How to Play", "Quit"};
    Button menuButtons[3];
    InitButtons(menuButtons, menuTexts, 3, 300);
    
    const char *modeTexts[] = {"Endless Mode", "Stage Mode", "Back"};
    Button modeButtons[3];
    InitButtons(modeButtons, modeTexts, 3, 300);
    
    Button prevButton = {{SCREEN_WIDTH / 2 - 150, 680, 100, 40}, "Prev", false};
    Button nextButton = {{SCREEN_WIDTH / 2 + 50, 680, 100, 40}, "Next", false};
    Button backButton = {{SCREEN_WIDTH / 2 - 100, 730, 200, 50}, "Back", false};
    
    Texture2D latar = LoadTexture("resources/latar.png");
    Texture2D howToPlayImages[4] = {
        LoadTexture("resources/howto1.png"),
        LoadTexture("resources/howto2.png"),
        LoadTexture("resources/howto3.png"),
        LoadTexture("resources/howto4.png"),
    };

    Texture2D ssGameplay = LoadTexture("resources/ssGameplay.png");
    Texture2D ssGameplay2 = LoadTexture("resources/ssGameplay2.png");
    Texture2D ssGameplay3 = LoadTexture("resources/ssGameplay3.png");
    Texture2D tanah = LoadTexture("resources/tanah.png");
    Texture2D musuh = LoadTexture("resources/krtTambang.png");
    Texture2D obstacle = LoadTexture ("resources/obstacle.png");
    Texture2D food = LoadTexture ("resources/tikus.png");
    Texture2D dinding = LoadTexture ("resources/dinding.png");
    snake.tekstur = LoadTexture ("resources/teksturUlar.png");
    Image kayu=LoadImage("resources/portal2.png");
    Texture2D textuar=menggambar(&kayu,50,50);

    Music menu = LoadMusicStream("resources/Menu.wav");
    Sound start = LoadSound("resources/StartGame.wav");
    Sound eat = LoadSound("resources/Makanan.wav");
    Music game = LoadMusicStream("resources/GamePlay.wav");
    Sound over = LoadSound("resources/GameOver.wav");

    SetSoundVolume(start ,1.5f);
    SetSoundVolume(eat ,1.5f);
    
    float tuaim=0;
    mportal[0].cooldown=10;
    float bgX = 0;
    float scrollSpeed = 75;
    float scale = 1.2;
    float radius = 10.0f;

    GenerateRintangan(&rintangan, level);
    GenerateMakanan(&makanan, &rintangan);

    InitSnake(&snake);

    while(!WindowShouldClose()){
        if(yes()){
            buffer=lastbutton();
        }   
        
        tuaim+=GetFrameTime(); 

        if(tuaim >=10){
            tuaim=0;
        }

        cooldown(&mportal[0].cooldown);
        if(IsKeyPressed(KEY_P) && mportal[0].cooldown == 0){
            p_pressed(&mpeluru,buffer,(Vector2){snake.badan[0].x, snake.badan[0].y});
            mportal[0].cooldown=10;
        }

        if(mpeluru.status == true){
            move_peluru(&mpeluru,mpeluru.speed);
        }

        if(check_peluru(mpeluru.coor.x,BATAS_PORTAL_H-100,0+30) || check_peluru(mpeluru.coor.y,BATAS_PORTAL_V-100,0+30) ){
            place_portal(mpeluru.coor,mportal,2,BATAS_PORTAL_H,0,BATAS_PORTAL_V,0,mpeluru.buffer,10,5);
            mpeluru.status=false;
            mpeluru.coor.x=400;
            mpeluru.coor.y=400;
        }
        teleport_portal(&snake.badan[0].x,&snake.badan[0].y,mportal,100,100,2);

        UpdateMusicStream(menu);
        UpdateMusicStream(game);

        bgX -= scrollSpeed * GetFrameTime();
        if (bgX <= -latar.width * scale) bgX += latar.width * scale;

        BeginDrawing();

        DrawTextureEx(latar, (Vector2){bgX, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(latar, (Vector2){bgX + latar.width * scale, 0}, 0.0f, scale, WHITE);

        if ((currentScreen == ENDLESS || currentScreen == STAGE) && fps != 10) {
            fps = 10;
            SetTargetFPS(fps);
        }
        
        if (currentScreen == MENU || currentScreen == MODE_SELECTION) {
            if (!isMusicPlaying ) {
                PlayMusicStream(menu);
                SetMusicVolume(menu, 2.0f);
                isMusicPlaying = true;
            }
        }

        if(currentScreen == ENDLESS || currentScreen == STAGE){
            if (!isStartPlaying) {
                PlaySound(start);
                PlayMusicStream(game);
                SetMusicVolume(game, 1.5f);
                isStartPlaying = true;
            }
        }

        if ((currentScreen == ENDLESS || currentScreen == STAGE )&& isGameOver) {   
            StopMusicStream(game);  
            if (!isSoundOver) {  
                PlaySound(over);  
                isSoundOver = true; 
            }  
        }
        

        if (currentScreen == MENU) {
            DrawText("Snave", SCREEN_WIDTH / 2 - MeasureText("Snave", 50) / 2, 200, 50, WHITE);
            UpdateButtons(menuButtons, 3, &currentScreen);
            DrawButtons(menuButtons, 3);
            isGameOver = false;
            isSoundOver = false; 
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
                DrawScaledTexture(howToPlayImages[0], SCREEN_WIDTH / 2, 150, BOX_WIDTH);
                DrawScaledTexture(ssGameplay, SCREEN_WIDTH / 2, 250, BOX_WIDTH);
                DrawScaledTexture(howToPlayImages[1], SCREEN_WIDTH / 2, 430, BOX_WIDTH);
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

        else if (currentScreen == ENDLESS){
            ClearBackground(RAYWHITE);
            StopMusicStream(menu);
            DrawGame(&makanan, &rintangan, &enemy, enemyCount, score, level, dinding, tanah, food, musuh, obstacle );

            DrawText(TextFormat("Score: %d", score), 165, 625, 50, GOLD);
            DrawText("ENDLESS MODE", SCREEN_WIDTH / 2 - MeasureText("ENDLESS MODE", 70) / 2, SCREEN_HEIGHT - 90, 70, BROWN);

            if(!cekTabrakan(&snake)){
                UpdateSnake(&snake);
                DrawSnake(&snake);
            }
            else{
                isGameOver = true;
                DrawText("GAME OVER", 150, 250, 50, RED);
                DrawText(TextFormat("Score: %i", score), 230, 300, 30, RED);  
            }
    
            if(CheckMakanan(&snake, &makanan)){
                score += 100;
                snake.panjang++;
                GenerateMakanan(&makanan, &rintangan);
                PlaySound(eat);
            }
        }

        else if (currentScreen == STAGE){
            level = 1;
            ClearBackground(RAYWHITE);
            StopMusicStream(menu);
            DrawGame(&makanan, &rintangan, &enemy, enemyCount, score,level, dinding, tanah, food, musuh, obstacle );
            
            DrawText(TextFormat("Score: %d", score), 10, 630, 30, GOLD);
            DrawText(TextFormat("Lives: %d", lives), 250, 630, 30, GOLD);
            DrawText(TextFormat("Level: %d", level), 450, 630, 30, GOLD);
            DrawText(TextFormat("time: %f tuaim: %f", GetTime(),tuaim), 50, 330, 30, RED);
            DrawText("STAGE MODE", SCREEN_WIDTH / 2 - MeasureText("STAGE MODE", 70) / 2, SCREEN_HEIGHT - 90, 70, BROWN);
            if(!cekTabrakan(&snake)){
                UpdateSnake(&snake);
                DrawSnake(&snake);
            }
            else{
                isGameOver = true;
                DrawText("GAME OVER", 150, 250, 50, RED);
                DrawText(TextFormat("Score: %i", score), 230, 300, 30, RED);  
            }
    
            if(CheckMakanan(&snake, &makanan)){
                score += 100;
                snake.panjang++;
                GenerateMakanan(&makanan, &rintangan);
                PlaySound(eat);
            }

            if(score >= 1000){
                score = 0;
                InitSnake(&snake);
                DrawSnake(&snake);
                level = level + 1;
                enemyCount = enemyCount + 1;
                GenerateEnemy(&enemy, enemyCount, level);
            }
            if(mpeluru.status){
                DrawCircle((int)mpeluru.coor.x, (int)mpeluru.coor.y, radius, GOLD);
            }
            if(cooldown(&mportal[0].activation) == false){
                draw_portal(textuar,2,mportal,20,20);
                }else{
                    mportal[0].status=false;
                    mportal[1].status=false;
                }
            MoveEnemy(&enemy);
        }
        EndDrawing();
    }

    UnloadTexture(latar); 
    UnloadTexture(food);
    UnloadTexture(musuh);
    UnloadTexture(obstacle);
    UnloadTexture(snake.tekstur);
    UnloadMusicStream(menu);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}