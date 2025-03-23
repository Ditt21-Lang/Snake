#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
#define KANAN 262
#define KIRI 263
#define BAWAH 264
#define ATAS 265

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