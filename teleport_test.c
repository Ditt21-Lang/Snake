#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650


void teleport_snake(float *x,float *y,int layar,float object){
     static int trigger=0;
     static float circlex_modul;
     static float circley_modul;
     const float speed=5;
    if(*x>layar-object){
        circlex_modul=*x;
        circley_modul=*y;
        *x=0-object;
        trigger=1;
    }
        if(trigger == 1){
        if (IsKeyDown(KEY_RIGHT)) circlex_modul += speed;
        if (IsKeyDown(KEY_LEFT)) circlex_modul -= speed;
        if (IsKeyDown(KEY_DOWN)) circley_modul += speed;
        if (IsKeyDown(KEY_UP)) circley_modul -= speed;
        
        DrawCircle(circlex_modul,circley_modul,object,BLUE);
        if(circlex_modul > layar+object){
        trigger=0;
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

 teleport_snake(&circleX, &circleY,LEBAR_LAYAR,radius);
 
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
