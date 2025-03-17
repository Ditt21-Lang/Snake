#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650

int lastbutton(){
if(IsKeyPressed(KEY_RIGHT)){

return 262;
}
else if(IsKeyPressed(KEY_LEFT)){

return 263;
}
else if(IsKeyPressed(KEY_DOWN)){

return 264;
}
else if(IsKeyPressed(KEY_UP)){

return 265;
}

}

bool yes(){

if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT) ||IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)){
return true;
}

}


//variable peluru
typedef struct{
    Vector2 koordinat_peluru;
    float speed;
    bool status;
    int buffer;
    Image gambar_peluru;
    Texture2D texture;
}peluru;

typedef struct{
    Vector2 koordinat_portal;
    bool status;
    Image gambar_portal;
}portal;

//initpeluru
peluru mpeluru={0};
peluru init_peluru(peluru mpeluru){
return mpeluru;
}

//LoadImage("portual.png") langsung masukin ke fungsi
Texture2D imgTOtexture(Image img,Texture2D texture){
    texture=LoadTextureFromImage(img);
    return texture;
}

//apabila p ditekan dijadikan fungsi "mainobjX","mainobjY"

void p_pressed(peluru *mpeluru,int *buffer_tujuan,int buffer_mengisi,Vector2 target_obj){
    (*mpeluru).status=true;
    (*mpeluru).koordinat_peluru.x=target_obj.x;
    (*mpeluru).koordinat_peluru.y=target_obj.y;
    *buffer_tujuan=buffer_mengisi;
    }

    
//jadi fungsikah dan ada buffer dan ditambahkan speed:
void move_peluru(peluru *mpeluru,float speed){
if(mpeluru->status){
    switch(mpeluru->buffer){
    case 262:
    mpeluru->koordinat_peluru.x +=speed;
    break;
    }
    }
}


//cek tembok
bool cek_tembok(int max_layar,int x){
if(x>max_layar){
    return true;
}
}
//init portal
portal mportal={0};

// set koordinat portal
void activeportal(Vector2 *posisi_portal,Vector2 posisi_bullet){
    posisi_portal->x=posisi_bullet.x;
    posisi_portal->y=posisi_bullet.y;
}

//kalo main_obj kena portal maka dia akan teleport
//tahap pengembangan 
/*
void check_portal(Vector2 posisi_portal,Vector2 main_obj){
    if(posisiportal.x>main_obj.x && posisiportal.y < main_obj.y ){
    
    
    }
    
}
*/

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
