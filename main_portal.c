#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650

int main(){
const int screenWidth = 800;
const int screenHeight = 600;
int buffer;


// Variabel lingkaran
float circleX = screenWidth / 2.0f;
float circleY = screenHeight / 2.0f;
float radius = 30.0f;
float speed = 5.0f;


// Inisialisasi window
InitWindow(LEBAR_LAYAR,TINGGI_LAYAR, "Gerakkan Lingkaran");
SetTargetFPS(60);


while(!WindowShouldClose()){
    
if(yes()){
buffer=lastbutton();
    }
DrawText(TextFormat("Buffer: %d", buffer), 50, 50, 30, RED);

if(IsKeyPressed(KEY_P)){
p_pressed(&mpeluru,&mpeluru.buffer,buffer,(Vector2){circleX,circleY});
}

move_peluru(&mpeluru,5);

if(cek_tembok(LEBAR_LAYAR,mpeluru.koordinat_peluru.x)){
     (mpeluru).status=false;
    activeportal(&(mportal.koordinat_portal),mpeluru.koordinat_peluru);
    DrawCircle(mportal.koordinat_portal.x,mportal.koordinat_portal.y,30,GOLD);
}



if (IsKeyDown(KEY_RIGHT)) circleX += speed;
if (IsKeyDown(KEY_LEFT)) circleX -= speed;
if (IsKeyDown(KEY_DOWN)) circleY += speed;
if (IsKeyDown(KEY_UP)) circleY -= speed;

// Gambar
BeginDrawing();
ClearBackground(RAYWHITE);
if(mpeluru.status){
DrawCircle(mpeluru.koordinat_peluru.x,mpeluru.koordinat_peluru.y,30,BLUE);
}

DrawCircle((int)circleX, (int)circleY, radius, BLUE);
DrawText("BUG cuy", 10, 10, 20, DARKGRAY);
EndDrawing();      
}
CloseWindow();
return 0;
}
