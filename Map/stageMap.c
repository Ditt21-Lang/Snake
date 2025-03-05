#include "raylib.h"

int main()
{
    InitWindow(600, 800, "Stage Mode Map");

    Texture2D background = LoadTexture("tanah.png");  
    Texture2D wall = LoadTexture("dinding.png");      // pastiin file2 nya ada di folder yang sama

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        DrawTexture(wall, 0, 0, WHITE);

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(wall);
    CloseWindow();

    return 0;
}
