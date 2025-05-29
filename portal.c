#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
#define KANAN 262
#define KIRI 263
#define BAWAH 264
#define ATAS 265
#include "portal.h"


/*buat endless tapi belum jadi:
void teleport_snake(portal *p,int layar,float object){
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
*/



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
