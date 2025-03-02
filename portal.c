#include "raylib.h"

int main() {
    // Inisialisasi window
    InitWindow(800, 600, "Gerakkan Lingkaran");

    // Variabel lingkaran
    int circleX = 350;
    int circleY = 250;
    float radius = 14.0f;
    Color color = GOLD;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update posisi berdasarkan input
        if (IsKeyDown(KEY_RIGHT)) circleX += 5;
        if (IsKeyDown(KEY_LEFT))  circleX -= 5;
        if (IsKeyDown(KEY_DOWN))  circleY += 5;
        if (IsKeyDown(KEY_UP))    circleY -= 5;

        // Render
        BeginDrawing();
        ClearBackground(GREEN);
        DrawCircle(circleX, circleY, radius, color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
