#include "raylib.h"

int main()
{
    InitWindow(600, 800, "Endless Mode Map");

    Texture2D background = LoadTexture("tanah.png"); // pastiin si tanah.png nya ada di folder yg sama

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();

    return 0;
}
