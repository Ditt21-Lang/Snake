#include <raylib.h>

#define MAX_LENGTH 100  // Panjang maksimal ular
#define CELL_SIZE 20

typedef struct {
    int x, y;
} Segment;

int i =0;
 Segment snake[MAX_LENGTH];  // Array untuk tubuh ular
    int length = 3;  // Panjang awal ular
    int direction = 0;  // 0 = kanan, 1 = kiri, 2 = atas, 3 = bawah
    
       void drawpp(int i,int length){
             while(i < length){
             DrawRectangle(snake[i].x * CELL_SIZE, snake[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
            i++;
        }
            
            
        }
int main() {
    const int screenWidth = 400, screenHeight = 400;
    InitWindow(screenWidth, screenHeight, "Snake Game");

   
    
    // Inisialisasi posisi awal ular
    for (int i = 0; i < length; i++) {
        snake[i].x = 5 - i;  // Ular mulai dari kiri ke kanan
        snake[i].y = 5;
    }

    SetTargetFPS(10);  // Kecepatan permainan

    while (!WindowShouldClose()) {
        // Kontrol gerakan
        if (IsKeyPressed(KEY_RIGHT) && direction != 1) direction = 0;
        if (IsKeyPressed(KEY_LEFT)  && direction != 0) direction = 1;
        if (IsKeyPressed(KEY_UP)    && direction != 3) direction = 2;
        if (IsKeyPressed(KEY_DOWN)  && direction != 2) direction = 3;

        // Geser tubuh ular dari belakang ke depan
        for (int i = length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        // Update posisi kepala
        if (direction == 0) snake[0].x += 1;
        if (direction == 1) snake[0].x -= 1;
        if (direction == 2) snake[0].y -= 1;
        if (direction == 3) snake[0].y += 1;

        // Gambar ulang
        BeginDrawing();
        ClearBackground(BLACK);

        // Gambar ular
        i=0;
        drawpp(i,length);
        
        
        
        DrawCircle(100, 30, 100, BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
