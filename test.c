#include "raylib.h"

int main(){
    InitWindow(900,650,"testo");
    while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(GOLD);
    DrawCircle(810,200,90,BLUE);
    EndDrawing();
    }
    
    
}
