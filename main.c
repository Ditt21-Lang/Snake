#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "Marrely.h"
#include "Gilang.h"
#include "Bayu.h"
#include "emir.h"
#include "Hilmi.h"
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
    RintanganNode *rintangan = NULL;
    Enemy enemy;
    EnemyList enemyList;


    //peluru
    peluru mpeluru={0};
    mpeluru.speed=50;
    mpeluru.status=false;

    //portal
    pll mportal=NULL;

    int score = 0;
    int total_score = 0;
    int level = 1;
    int lives = 15;
    int enemyCount = 0;
    int buffer;

    bool isMusicPlaying = false;
    bool isStartPlaying = false;
    bool isGameOver = false;
    bool isSoundOver = false;
    bool isSoundWinning = false;
    bool isWin = false;
    bool showHit = false;
    bool hasWinTimeStarted = false;
    float hitStartTime = 0;
    float winStartTime = 0.0f;
    


    ButtonNode* menuButtons = InitButtons(300);
    AppendButton(&menuButtons, "Play", 300);
    AppendButton(&menuButtons, "How to Play", 400);
    AppendButton(&menuButtons, "Quit", 500);

    ButtonNode* modeButtons = InitButtons(300);
    AppendButton(&modeButtons, "Endless Mode", 300);
    AppendButton(&modeButtons, "Stage Mode", 400);
    AppendButton(&modeButtons, "Back", 500);

    ButtonNode* gameOverButtons = InitButtons(350);
    AppendButton(&gameOverButtons, "Restart", 350);
    AppendButton(&gameOverButtons, "Main Menu", 450);

    ButtonNode *howToButtons = NULL;

    ButtonNode *newNode = (ButtonNode *)malloc(sizeof(ButtonNode));
    newNode->border = (Rectangle){SCREEN_WIDTH / 2 - 100, 730, 200, 50};
    newNode->text = strdup("Back"); 
    newNode->hover = false;
    newNode->next = howToButtons;
    howToButtons = newNode;

    newNode = (ButtonNode *)malloc(sizeof(ButtonNode));
    newNode->border = (Rectangle){SCREEN_WIDTH / 2 + 50, 680, 100, 40};
    newNode->text = strdup("Next");
    newNode->hover = false;
    newNode->next = howToButtons;
    howToButtons = newNode;

    newNode = (ButtonNode *)malloc(sizeof(ButtonNode));
    newNode->border = (Rectangle){SCREEN_WIDTH / 2 - 150, 680, 100, 40};
    newNode->text = strdup("Prev");
    newNode->hover = false;
    newNode->next = howToButtons;
    howToButtons = newNode;

    TextureNode *howToPlayTextures = NULL;
    TextureNode *ssGameplayTextures = NULL;

    Texture2D latar = LoadTexture("resources/latar.png");

    AddTexture(&howToPlayTextures, "resources/howto1.png", 0, (Vector2){SCREEN_WIDTH / 2, 150});
    AddTexture(&howToPlayTextures, "resources/howto2.png", 0, (Vector2){SCREEN_WIDTH / 2, 430});
    AddTexture(&howToPlayTextures, "resources/howto3.png", 1, (Vector2){SCREEN_WIDTH / 2, 150});
    AddTexture(&howToPlayTextures, "resources/howto4.png", 2, (Vector2){SCREEN_WIDTH / 2, 150});
    
    AddTexture(&ssGameplayTextures, "resources/ssGameplay.png", 0, (Vector2){SCREEN_WIDTH / 2, 250});
    AddTexture(&ssGameplayTextures, "resources/ssGameplay2.png", 1, (Vector2){SCREEN_WIDTH / 2, 350});
    AddTexture(&ssGameplayTextures, "resources/ssGameplay3.png", 2, (Vector2){SCREEN_WIDTH / 2, 400});
    
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
    Sound hit = LoadSound("resources/hitObs.wav");
    Sound level_up = LoadSound("resources/LevelUp.wav");
    Sound Reverse = LoadSound("resources/Reverse.wav");
    Sound winning = LoadSound("resources/winStage.wav");

    SetSoundVolume(start ,1.5f);
    SetSoundVolume(eat ,1.5f);
    SetSoundVolume(hit, 1.5f);
    SetSoundVolume(level_up, 1.5f);
    SetSoundVolume(Reverse, 5.0f);
    SetSoundVolume(winning, 1.0f);
    
    float cooldown_bullet=10;//em
    float bgX = 0;
    float scrollSpeed = 75;
    float scale = 1.2;
    float radius = 10.0f;

    InitSnake(&snake);
    GenerateMakanan(&makanan, rintangan);
    
    while(!WindowShouldClose()){
        if(yes()){
            buffer=lastbutton();
        }   

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

        if (currentScreen == MENU) {
            DrawText("Snave", SCREEN_WIDTH / 2 - MeasureText("Snave", 50) / 2, 200, 50, WHITE);
            UpdateButtons(menuButtons, &currentScreen);
            DrawButtons(menuButtons);
            isGameOver = false;
            isSoundOver = false; 
        } else if (currentScreen == MODE_SELECTION) {
            DrawText("Mode Selection", SCREEN_WIDTH / 2 - MeasureText("Mode Selection", 50) / 2, 200, 50, WHITE);
            UpdateButtons(modeButtons, &currentScreen);
            DrawButtons(modeButtons);
        } else if (currentScreen == HOW_TO_PLAY) {
            DrawRectangle(SCREEN_WIDTH / 2 - 200, 100, BOX_WIDTH, BOX_HEIGHT, DARKGRAY);
            
            DrawText("How to Play", SCREEN_WIDTH / 2 - MeasureText("How to Play", 30) / 2, 110, 30, WHITE);
            DrawButtons(howToButtons);

            Vector2 mousePoint = GetMousePosition();
            ButtonNode *current = howToButtons;

            while (current != NULL) {
                current->hover = CheckCollisionPointRec(mousePoint, current->border);
                
                if (current->hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (strcmp(current->text, "Prev") == 0 && howToPlayPage > 0) {
                        howToPlayPage--;
                    }
                    else if (strcmp(current->text, "Next") == 0 && howToPlayPage < 2) {
                        howToPlayPage++;
                    }
                    else if (strcmp(current->text, "Back") == 0) {
                        currentScreen = MENU;
                    }
                }
                
                current = current->next;
            }
            
            TextureNode *textureCurrent = howToPlayTextures;
            while (textureCurrent != NULL) {
                if (textureCurrent->page == howToPlayPage) {
                    DrawScaledTexture(textureCurrent->texture, textureCurrent->position.x, textureCurrent->position.y, BOX_WIDTH);
                }
                textureCurrent = textureCurrent->next;
            }

            textureCurrent = ssGameplayTextures;
            while (textureCurrent != NULL) {
                if (textureCurrent->page == howToPlayPage) {
                    DrawScaledTexture(textureCurrent->texture, textureCurrent->position.x, textureCurrent->position.y, BOX_WIDTH);
                }
                textureCurrent = textureCurrent->next;
            }
            
            while (current != NULL) {
                DrawRectangleRec(current->border, current->hover ? LIGHTGRAY : GRAY);
                
                float textX, textY;
                int fontSize = 20;
                
                if (strcmp(current->text, "Back") == 0) {
                    textX = current->border.x + 60;
                    textY = current->border.y + 15;
                } else {
                    textX = current->border.x + 20;
                    textY = current->border.y + 10;
                }
                
                DrawText(current->text, textX, textY, fontSize, WHITE);
                
                current = current->next;
            }
        }

        else if (currentScreen == ENDLESS) {
            ClearBackground(RAYWHITE);
            StopMusicStream(menu);
            DrawGame(&makanan, rintangan, &enemyList, enemyCount, score, level, dinding, tanah, food, musuh, obstacle);

            DrawText(TextFormat("Score: %d", score), 165, 625, 50, GOLD);
            DrawText("ENDLESS MODE", SCREEN_WIDTH/2 - MeasureText("ENDLESS MODE",70)/2, SCREEN_HEIGHT-90, 70, BROWN);

            if(!cekTabrakan(&snake) && !CekTabrakDinding(&snake)) {
                UpdateSnake(&snake);
                DrawSnake(&snake, snake.tekstur);
                
                if(CheckMakanan(&snake, &makanan)) {
                    score += 100;
                    tambahNode(&snake);
                    GenerateMakanan(&makanan, rintangan);
                    PlaySound(eat);
                }
            }
            else {
                isGameOver = true;
            }
        }

        else if (currentScreen == STAGE ){
            ClearBackground(RAYWHITE);
            StopMusicStream(menu);
            DrawGame(&makanan, rintangan, &enemyList, enemyCount, score,level, dinding, tanah, food, musuh, obstacle );
            GenerateRintangan(&rintangan, level);
            
            DrawText(TextFormat("Score: %d", score), 10, 630, 30, GOLD);
            DrawText(TextFormat("Lives: %d", lives), 10, 660, 30, RED);
            DrawText(TextFormat("Level: %d", level), 395, 630, 30, WHITE);
            DrawText(TextFormat("Reverse: %f", reverseTimer), 395, 660, 30, GREEN);
            DrawText("STAGE MODE", SCREEN_WIDTH / 2 - MeasureText("STAGE MODE", 70) / 2, SCREEN_HEIGHT - 90, 70, BROWN);
            if(!isGameOver){
                if(!cekTabrakan(&snake) && !CekTabrakDinding(&snake)){
                    UpdateSnake(&snake);
                    DrawSnake(&snake, snake.tekstur);
                    MoveEnemy(&enemyList);
                }
                else{
                    level = 0;
                    isGameOver = true;
                }
            }
    
            if(CheckMakanan(&snake, &makanan)){
                score += 100;
                total_score = total_score + 100;
                tambahNode(&snake);
                GenerateMakanan(&makanan, rintangan);
                PlaySound(eat);
            }

            if(score >= 1000){
                score = 0;
                PlaySound(level_up);
                InitSnake(&snake);
                DrawSnake(&snake, snake.tekstur);
                level = level + 1;
                lives = lives + 1;
                GenerateRintangan(&rintangan, level);
                enemyCount = enemyCount + 1;            
                enemyList = GenerateEnemy(level); 
            }

            if(CekTabrakRintangan((Vector2){snake.head->position.x, snake.head->position.y}, rintangan) ||
                CekTabrakEnemy(snake, enemyList)) {
                if (!isGameOver){
                    lives = lives - 1;
                    PlaySound(hit);
                    showHit = true;
                    hitStartTime = GetTime();
                    if (lives == 0){
                        isGameOver = true;
                    }
                }
            }

            if (showHit && (GetTime() - hitStartTime >= 2.0f)) {
                showHit = false;
            }

            if (showHit){
                DrawText(TextFormat("HIT!"), 245, 650, 30, RED);
            }

            if (IsKeyPressed(KEY_SPACE)){
                PlaySound(Reverse);
                ReverseSnake(&snake);
            }

            if(level > 5){
                isWin = true;
            }

            UpdateCooldown();


            // //________________________
            // if( IsKeyPressed(KEY_P) ) p_pressed(&mpeluru,buffer,snake.head->position);

            // if(mpeluru.status){
            //     move_peluru(&mpeluru,mpeluru.speed);
            //     DrawCircle((int)mpeluru.coor.x, (int)mpeluru.coor.y, radius, GOLD);
            // }

        // if(check_peluru(mpeluru.coor.x,LEBAR_LAYAR,0) || check_peluru(mpeluru.coor.y,TINGGI_LAYAR,0) ){
        //     place_portal(mpeluru.coor,&mportal,LEBAR_LAYAR-50,50,TINGGI_LAYAR-50,50,mpeluru.buffer,2);
        //     mpeluru.status=false;
        //     mpeluru.coor.x=400;
        //     mpeluru.coor.y=400;
        // }

    //     if(mportal != NULL){
    //     if(mportal->status == false) dellall_portal(&mportal);
    // }
    // teleport_portal(&(snake.head->position.x),&(snake.head->position.y),mportal,80,80);
    // cooldown_portal_traversal(mportal);
    
    // draw_portal(textuar,mportal,50,50,BLUE);
    // //________________________    

}
        
        if (currentScreen == STAGE && isWin) {
            // Catat waktu saat menang pertama kali
            if (!hasWinTimeStarted) {
                winStartTime = GetTime();
                hasWinTimeStarted = true;
                StopMusicStream(game); 

                if (!isSoundWinning){
                    PlaySound(winning);
                    isSoundWinning = true;
                }

            }

            // Cek apakah 3 detik sudah berlalu
            if (GetTime() - winStartTime <= 3.0f) {
                DrawText("YOU WIN!", 180, 250, 50, GREEN);
                DrawText(TextFormat("Total Score: %i", total_score), 160, 300, 30, GREEN); 
                InitSnake(&snake);
            } else {
                // Reset status kemenangan agar bisa lanjut ke layar lain atau ulang game
                isWin = false;
                hasWinTimeStarted = false;
                isSoundWinning = false;
                isMusicPlaying = false;
                isSoundOver = false;
                isGameOver = false;
                isStartPlaying = false;
                fps = 60;
                score = 0;
                total_score = 0;
                lives = 15;
                level = 1;
                enemyCount = 0;
                reverseTimer = 0;
                SetTargetFPS(fps);
                FreeRintangan(&rintangan);
                FreeEnemyList(&enemyList);
                currentScreen = MENU;

            }
        }

        
        if ((currentScreen == ENDLESS || currentScreen == STAGE) && isGameOver) {   
            StopMusicStream(game);  
            if (!isSoundOver) {  
                PlaySound(over);  
                isSoundOver = true;
            }

            DrawText("GAME OVER", 150, 250, 50, RED);
            DrawText(TextFormat("Total Score: %i", total_score), 160, 300, 30, RED);  
            
            ButtonNode* current = gameOverButtons;
            while (current != NULL) {
                current->hover = CheckCollisionPointRec(GetMousePosition(), current->border);
                
                if (strcmp(current->text, "Restart") == 0 && current->hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    InitSnake(&snake);
                    score = 0;
                    total_score = 0;
                    lives = 15;
                    enemyCount = 0;
                    level = 1;
                    reverseTimer = 0;
                    FreeEnemyList(&enemyList); 
                    GenerateMakanan(&makanan, rintangan);
                    isGameOver = false;
                    isStartPlaying = false;
                    isSoundOver = false;
                }
                
                if (strcmp(current->text, "Main Menu") == 0 && current->hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    InitSnake(&snake);
                    currentScreen = MENU;
                    score = 0;
                    total_score = 0;
                    lives = 15;
                    level = 1;
                    enemyCount = 0;
                    reverseTimer = 0;
                    isGameOver = false;
                    isStartPlaying = false;
                    isSoundOver = false;
                    isMusicPlaying = false;
                    fps = 60;
                    SetTargetFPS(fps);
                    FreeRintangan(&rintangan);
                    FreeEnemyList(&enemyList);
                }
                
                current = current->next;
            }

            current = gameOverButtons;
            while (current != NULL) {
                DrawRectangleRec(current->border, current->hover ? LIGHTGRAY : GRAY);
                DrawText(current->text, 
                        current->border.x + current->border.width/2 - MeasureText(current->text, 20)/2,
                        current->border.y + current->border.height/2 - 10,
                        20, WHITE);
                current = current->next;
            }
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
    FreeButtons(menuButtons);
    FreeButtons(modeButtons);
    FreeButtons(gameOverButtons);
    FreeButtons(howToButtons);
    FreeTextures(howToPlayTextures);
    FreeTextures(ssGameplayTextures);
    freeSnake(&snake);
    FreeEnemyList(&enemyList);
    FreeRintangan(&rintangan);
    printf("Return Succesfully");
    return 0;      
}
