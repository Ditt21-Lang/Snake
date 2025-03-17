#include "raylib.h"

#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 600

int main() {
    InitWindow(LEBAR_LAYAR, TINGGI_LAYAR, "Game Satu Peluru");
    SetTargetFPS(60);

    // Posisi objek utama (misalnya alien)
    float playerX = LEBAR_LAYAR / 2;
    float playerY = TINGGI_LAYAR - 50;

    // Variabel peluru
    float bulletX = 0;
    float bulletY = 0;
    bool bulletActive = false;  // Apakah peluru sedang ada di layar?
    float bulletSpeed = 5.0f;

    while (!WindowShouldClose()) {
        // Kontrol objek utama
        if (IsKeyDown(KEY_RIGHT)) playerX += 5;
        if (IsKeyDown(KEY_LEFT)) playerX -= 5;

        // Jika tombol P ditekan dan belum ada peluru, buat peluru baru
        if (IsKeyPressed(KEY_P) && !bulletActive) {
            bulletX = playerX;
            bulletY = playerY;
            bulletActive = true;
        }

        // Gerakkan peluru ke atas jika aktif
        if (bulletActive) {
            bulletY -= bulletSpeed;

            // Jika peluru keluar layar, reset agar bisa menembak lagi
            if (bulletY < 0) {
                bulletActive = false;
            }
        }

        // Gambar
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Gambar objek utama
        DrawCircle(playerX, playerY, 20, BLUE);

        // Gambar peluru hanya jika aktif
        if (bulletActive) {
            DrawCircle(bulletX, bulletY, 5, RED);
        }

        DrawText("Tekan P untuk menembak", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
