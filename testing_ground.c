#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include "emir.h"  
    

float x;
float y;
float speed;
int main(){

    x=970;
    y=820;
    speed=5;
// Inisialisasi window
InitWindow(1000,850, "Gerakkan Lingkaran");
SetTargetFPS(60);

//texture
Image kayu=LoadImage("resources/queen.png");
Texture2D textuar=menggambar(&kayu,970,850);
Image port=LoadImage("resources/howto2.png");
Texture2D port_text=menggambar(&port,30,30);

while(!WindowShouldClose()){

    if(IsKeyDown(KEY_DOWN))y += 5;
    if(IsKeyDown(KEY_UP))y -= 5;
    if(IsKeyDown(KEY_LEFT))x -= 5;
    if(IsKeyDown(KEY_RIGHT))x += 5;


BeginDrawing();
ClearBackground(RAYWHITE);

DrawTexture(textuar,0,0,BLUE);//queen

DrawTexture(port_text,x,y,WHITE);
// DrawCircle(x,y,15,BLUE);
EndDrawing();      
}
CloseWindow();
return 0;
}
