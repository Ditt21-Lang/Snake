#include <stdio.h>
#include "emir.h"
#include <stdlib.h>


int main(){
const int screenWidth = 800;
const int screenHeight = 600;



// Variabel lingkaran
float circleX = screenWidth / 2.0f;
float circleY = screenHeight / 2.0f;
float radius = 30.0f;
float speed = 5.0f;

//buat arah peluru
int buffer=0;

//peluru
peluru mpeluru={0};
mpeluru.speed=50;
mpeluru.status=false;

//portal
pll mportal=NULL;


// Inisialisasi window
InitWindow(LEBAR_LAYAR,TINGGI_LAYAR, "Gerakkan Lingkaran");
SetTargetFPS(60);

//texture
Image kayu=LoadImage("resources/queen.png");
Texture2D textuar=menggambar(&kayu,100,100);

while(!WindowShouldClose()){
    
if(yes())buffer=lastbutton();

if (IsKeyDown(KEY_RIGHT)) circleX += speed;
if (IsKeyDown(KEY_LEFT)) circleX -= speed;
if (IsKeyDown(KEY_DOWN)) circleY += speed;
if (IsKeyDown(KEY_UP)) circleY -= speed;

//todo make cooldown not in portal
if(IsKeyPressed(KEY_P) ){
    p_pressed(&mpeluru,buffer,(Vector2){circleX,circleY});
}

if(mpeluru.status == true){
move_peluru(&mpeluru,mpeluru.speed);
}


//DISINI MULAI ERROR NYA ERRORRRRR
if(check_peluru(mpeluru.coor.x,LEBAR_LAYAR,0) || check_peluru(mpeluru.coor.y,TINGGI_LAYAR,0) ){
    place_portal(mpeluru.coor,&mportal,LEBAR_LAYAR-50,50,TINGGI_LAYAR-50,50,mpeluru.buffer,2);
    mpeluru.status=false;
    mpeluru.coor.x=400;
    mpeluru.coor.y=400;
}

if(mportal != NULL){
    if(mportal->status == false) dellall_portal(&mportal);
}

teleport_portal(&circleX,&circleY,mportal,130,130);
cooldown_portal_traversal(mportal);
    

// Gambar
BeginDrawing();
ClearBackground(RAYWHITE);
DrawCircle((int)circleX, (int)circleY, radius, BLUE);
if(mpeluru.status){
DrawCircle((int)mpeluru.coor.x,(int)mpeluru.coor.y, radius, GOLD);
}
//mportal

draw_portal(textuar,mportal,100,100,BLUE);
DrawText("BUG cuy", 10, 10, 20, DARKGRAY);
EndDrawing();      
}
CloseWindow();
return 0;
}
