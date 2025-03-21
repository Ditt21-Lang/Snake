#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
#define ATAS 0
#define BAWAH 1
#define KANAN 2
#define KIRI 3

typedef struct{
    Vector2 coor;
    bool status;
    Image gambar_portal;
    int arah;
}portal;


void teleport_snake(portal p[],int layar,float object){
     static int trigger=0;
     static float circlex_modul;
     static float circley_modul;
     const float speed=5;
    if(*x>=layar-object){
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
//mengset coor portal
if(check_peluru=true){
    void place_portal(objx,objy,portal *p1){
    for(int i=0;i<KOTAK;i++){
        if(i%2 == 0){
        *(p1+i).coor.x=objx;
        *(p1+i).coor.y=objy;
        }
        else{
        *(p1+i).coor.x=(p1+i-1).coor.x;
        *(p1+i).coor.y=(p1+i-1).coor.y;

        }
    }

}

int convert_coor_portal(int coor,max_lebar,int arah){
    switch(arah){
        case KANAN:
        coor -= coor; //x
        return coor;
        break;
        case KIRI:
        coor = max_lebar; //x
        return coor;
        break;
        case BAWAH:
        coor = max_tinggi; 
        break;
        case ATAS:
        coor -=coor;
        break;
}