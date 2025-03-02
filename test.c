#include "raylib.h"
#include <stdio.h>

int main() {
    InitWindow(800, 600, "Cek Tombol Pertama yang Ditekan");

    while (!WindowShouldClose()) {
        int key = GetKeyPressed(); // Mendapatkan tombol yang ditekan

        if (key != 0) { // Jika ada tombol yang ditekan
            printf("Tombol pertama yang ditekan: %d (%c)\n", key, (char)key);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tekan tombol apa saja...", 200, 250, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
