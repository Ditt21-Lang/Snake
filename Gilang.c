#include <raylib.h>

int main(){

    const int lebar = 800;
    const int tinggi = 600;
    InitWindow(lebar, tinggi, "Test");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(400, 500, 50, MAROON);
        
        DrawText("Contoh", 280, 500, 20, BLACK);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}