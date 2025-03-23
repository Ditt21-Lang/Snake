#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
 #include "peluru.h"
 
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
    
