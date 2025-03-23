#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
#define KANAN 262
#define KIRI 263
#define BAWAH 264
#define ATAS 265

//variable peluru
typedef struct{
    Vector2 coor;
    float speed;
    bool status;
    int buffer;
    Image gambar_peluru;
    Texture2D texture;
    float cooldown;
}peluru;

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
    
//if P press | peluru koor koornya ada di head of ular
void p_pressed(peluru *mpeluru,int buffer_mengisi,Vector2 target_obj){
    (*mpeluru).status=true;
    (*mpeluru).coor.x=target_obj.x;
    (*mpeluru).coor.y=target_obj.y;
    (*mpeluru).buffer=buffer_mengisi;
    }


//peluru bergerak and arah nya
    void move_peluru(peluru *mpeluru,float speed){
        switch(mpeluru->buffer){
        case 262://KANAN:
        (*mpeluru).coor.x +=speed;
        break;
        case 263://KIRI:
        mpeluru->coor.x -=speed;
        break;
        case 264://BAWAH:
        mpeluru->coor.y +=speed;
        break;
        case 265://ATAS:
        mpeluru->coor.y -=speed;
        break;
        }
        }
    
   // check if peluru kena tembok return true
    bool check_peluru(float coor,int lebar_tinggi,int min){
        if(coor>lebar_tinggi || coor<min){
           return true;
        }else {
        return false;
        }
            
    }    
    
    
    
//bagian portal\\



typedef struct{
    Vector2 coor;
    bool status;
    Image gambar_portal;
    int arah;
    float cooldown;
    float activation;
}portal;

//koordinat portal ke 2
Vector2 convert_coor_portal(Vector2 coor,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah){
    switch(arah){
        case KANAN:
        coor.x -= coor.x; //x
        return coor;
        break;
        case KIRI:
        coor.x = max_lebar-100; //x
        return coor;
        break;
        case BAWAH:
        coor.y -=coor.y; 
        return coor;
        break;
        case ATAS:
        coor.y=max_tinggi-100;
        return coor;
        break;
        default:
        break;
}
}

//mengset coor portal
//if(check_peluru==true) kalo si peluru kena tembok
    void place_portal(Vector2 obj,portal *p1,int kotak,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah,float cooldown,float activation){
    for(int i=0;i<kotak;i++){
        if(i%2 == 0){
        (*(p1+i)).coor.x=obj.x;
        (*(p1+i)).coor.y=obj.y;
        (*(p1+i)).status=true;
        (*(p1+i)).cooldown=cooldown;
        (*(p1+i)).activation=activation;
        }
        else{
        (*(p1+i)).coor=convert_coor_portal((*(p1+i-1)).coor,max_lebar,min_lebar,max_tinggi,min_tinggi,arah);
        (*(p1+i)).status=true;
        }
    }

} 

bool cooldown(float *target){
    if(*target > 0){
        *target-=GetFrameTime();
        return false;
    }else
        *target=0;
        return true;
}

    Texture2D menggambar(Image *edit,int width,int height){
     ImageResize(edit,width,height);
     Texture2D textuar=LoadTextureFromImage(*edit);
     UnloadImage(*edit);
     return textuar;
    }


    void draw_portal(Texture2D purtal,int kotak,portal *mportal,int lgambar,int tgambar){
        for(int i=0;i<kotak;i++){
            if((mportal+i)->status == true){
        DrawTexture(purtal,mportal[i].coor.x-(lgambar/2),mportal[i].coor.y-(tgambar/2),BLUE);
        }else{
            printf("portal tidak ada");
        }
    }
    }


void teleport_portal(float *targetx,float *targety,portal mportal[],int lgambar,int tgambar,int kotak){
    for(int i=0;i<kotak;i++){
        if((mportal+i)->status == true){
            if(i%2 == 0){
                if( (*targetx >= mportal[i].coor.x-(lgambar/2) && *targetx <= mportal[i].coor.x+(lgambar/2)) &&(*targety >= mportal[i].coor.y-(tgambar/2) && *targety <= mportal[i].coor.y+(tgambar/2)) ){
                *targetx=mportal[i+1].coor.x;
                *targety=mportal[i+1].coor.y;
                (mportal+i)->status = false;
                (mportal+i+1)->status = false;
                
                }    
            
            }else{
               if( (*targetx >= mportal[i].coor.x-(lgambar/2) && *targetx <= mportal[i].coor.x+(lgambar/2)) &&(*targety >= mportal[i].coor.y-(tgambar/2) && *targety <= mportal[i].coor.y+(tgambar/2)) ){
                *targetx=mportal[i-1].coor.x;  
                *targety=mportal[i-1].coor.y;
                (mportal+i-1)->status = false;
                (mportal+i)->status = false;
            }
        }
    }
    else{
    return;
        }   
    }
}

                

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

teleport_portal(&circleX,&circleY,mportal,100,100,2);
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
