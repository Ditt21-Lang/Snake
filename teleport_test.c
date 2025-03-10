#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650




void teleport(float *coordinate,float max,float object){
    if(*coordinate>max-object){
    *coordinate = *coordinate-(max+object);
    }
    else{
    if(*coordinate<max-max){
    *coordinate = max;
    }
}
}


int main(){



// Variabel lingkaran
float circleX = LEBAR_LAYAR / 2.0f;
float circleY = TINGGI_LAYAR/ 2.0f;
float radius = 30.0f;
float speed = 5.0f;

int buffer;
// Inisialisasi window
InitWindow(LEBAR_LAYAR,TINGGI_LAYAR, "Gerakkan Lingkaran");
SetTargetFPS(60);
while(!WindowShouldClose()){
if (IsKeyDown(KEY_RIGHT)) circleX += speed;
if (IsKeyDown(KEY_LEFT)) circleX -= speed;
if (IsKeyDown(KEY_DOWN)) circleY += speed;
if (IsKeyDown(KEY_UP)) circleY -= speed;

 teleport(&circleX,LEBAR_LAYAR,radius);

 
 
// Gambar
BeginDrawing();
ClearBackground(RAYWHITE);
DrawCircle((int)circleX, (int)circleY, radius, BLUE);
DrawText("BUG cuy", 10, 10, 20, DARKGRAY);
EndDrawing();      
}
CloseWindow();
return 0;
}
