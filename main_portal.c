#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
#define KANAN 262
#define KIRI 263
#define BAWAH 264
#define ATAS 265


   
    
    
//bagian portal\\

                

int main(){
const int screenWidth = 800;
const int screenHeight = 600;
int buffer;
//peluru
peluru mpeluru={0};
mpeluru.speed=50;
mpeluru.status=false;

//portal
portal mportal[2];
mportal[0].status=false;
mportal[1].status=false;

// Variabel lingkaran
float circleX = screenWidth / 2.0f;
float circleY = screenHeight / 2.0f;
float radius = 30.0f;
float speed = 5.0f;

// Inisialisasi window
InitWindow(LEBAR_LAYAR,TINGGI_LAYAR, "Gerakkan Lingkaran");
SetTargetFPS(60);

//texture
Image kayu=LoadImage("portal2.png");
Texture2D textuar=menggambar(&kayu,100,100);

float tuaim=0;
mportal[0].cooldown=10;


while(!WindowShouldClose()){
    
if(yes()){
buffer=lastbutton();
    }
    
   
DrawText(TextFormat("Buffer: %d", buffer), 50, 50, 30, RED);
DrawText(TextFormat("peluru: %f", mpeluru.coor.y), 100, 150, 30, RED);
DrawText(TextFormat("peluru: %f", mpeluru.coor.x), 100, 100, 30, RED);
DrawText(TextFormat("status: %d", mpeluru.status), 50, 200, 30, RED);
DrawText(TextFormat("portalx: %f portaly: %f", mportal[0].coor.x, mportal[0].coor.y), 50, 230, 30, RED);
DrawText(TextFormat("portalx: %f portaly: %f", mportal[1].coor.x, mportal[1].coor.y), 50, 280, 30, RED);
DrawText(TextFormat("time: %f tuaim: %f", GetTime(),tuaim), 50, 330, 30, RED);
DrawText(TextFormat("tur or fulse: %f ", mportal[0].activation), 50, 360, 30, RED);
DrawText(TextFormat("portul %f ", mportal[0].cooldown), 50, 380, 30, RED);

//mengambil waktu
tuaim+=GetFrameTime();    

if(tuaim >=10){
    tuaim=0;
}

if (IsKeyDown(KEY_RIGHT)) circleX += speed;
if (IsKeyDown(KEY_LEFT)) circleX -= speed;
if (IsKeyDown(KEY_DOWN)) circleY += speed;
if (IsKeyDown(KEY_UP)) circleY -= speed;


cooldown(&mportal[0].cooldown);
if(IsKeyPressed(KEY_P) && mportal[0].cooldown == 0){
    p_pressed(&mpeluru,buffer,(Vector2){circleX,circleY});
    mportal[0].cooldown=10;
}

if(mpeluru.status == true){
move_peluru(&mpeluru,mpeluru.speed);
}

if(check_peluru(mpeluru.coor.x,LEBAR_LAYAR-100,0+30) || check_peluru(mpeluru.coor.y,TINGGI_LAYAR-100,0+30) ){
    place_portal(mpeluru.coor,mportal,2,LEBAR_LAYAR,0,TINGGI_LAYAR,0,mpeluru.buffer,10,5);
    mpeluru.status=false;
    mpeluru.coor.x=400;
    mpeluru.coor.y=400;
}

teleport_portal(&circleX,&circleY,&mportal,100,100,2);
// Gambar
BeginDrawing();
ClearBackground(RAYWHITE);
DrawCircle((int)circleX, (int)circleY, radius, BLUE);
if(mpeluru.status){
DrawCircle((int)mpeluru.coor.x, (int)mpeluru.coor.y, radius, GOLD);
}
//mportal
    if(cooldown(&mportal[0].activation) == false){
    draw_portal(textuar,2,mportal,100,100);
    }else{
        mportal[0].status=false;
        mportal[1].status=false;
    }


DrawText("BUG cuy", 10, 10, 20, DARKGRAY);
EndDrawing();      
}
CloseWindow();
return 0;
}
