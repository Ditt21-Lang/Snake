#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "emir.h"


// void init_peluru(Vector2 *coor,float *speed,bool *status,int *buffer){

// }



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
    return false;
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
bool check_peluru(float coor,int max,int min){
    if(coor > max || coor < min){
        return true;
    }
    else {
        return false;
    }   
}    

//fungsi ini tuh membalikan apabila kanan maka koor paling kirin up maka bawah
//fungsi ini tuh membalikan apabila kanan maka koor paling kirin up maka bawah
Vector2 convert_coor_portal(Vector2 portal_coordinat,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah){
//fungsi ini tuh membalikan apabila kanan maka koor paling kirin up maka bawah
    switch(arah){
        case KANAN:
        portal_coordinat.x = min_lebar; //x
        return portal_coordinat;
        break;
        case KIRI:
        portal_coordinat.x = max_lebar; //x
        return portal_coordinat;
        break;
        case BAWAH:
        portal_coordinat.y =min_tinggi; 
        return portal_coordinat;
        break;
        case ATAS:
        portal_coordinat.y=max_tinggi;
        return portal_coordinat;
        break;
        default:
        break;
}
}

//mengset coor portal
//if(check_peluru==true) kalo si peluru kena tembok
//     void place_portal(Vector2 coor_peluru,portal *p1,int kotak,int max_lebar/*- lebar image - lebar object */,int min_lebar,int max_tinggi,int min_tinggi,int arah,float cooldown,float activation){
//     for(int i=0;i<kotak;i++){
//         if(i%2 == 0){
//         (*(p1+i)).coor=convert_coor_portal(coor_peluru,min_lebar,max_lebar,min_tinggi,max_tinggi,arah);
//         (*(p1+i)).status=true;
//         (*(p1+i)).cooldown=cooldown;
//         (*(p1+i)).activation=activation;
//         }
//         else{
//         (*(p1+i)).coor=convert_coor_portal((*(p1+i-1)).coor,max_lebar,min_lebar,max_tinggi,min_tinggi,arah);
//         (*(p1+i)).status=true;
//         }
//     }
// } 

    pll Alokasi_portal( Vector2 coor,bool status,int arah,float activation)
{
	 pll P;
	 P = (pll) malloc (sizeof (portal));
	 if (P != NULL)
	{
    P->status=status;
    P->coor=coor;
    P->arah=arah;
    P->activation=activation;
	P->next = NULL;
    P->prev=NULL;
	 }
	 return (P);
}


//dia akan traversal ke seluruh node dan memproses (disini saya mendeletenya)dari yang paling akhir
void dellall_portal(pll *target){
    if (*target == NULL)return;

    dellall_portal(&((*target)->next));

    //prosessing nya disini 
        
        free(*target);
        *target=NULL;
}

//dia akan true ketika portal nya itu sudah tidak aktif tapi masih ada di node
bool check_portal_activation(pll p){
    if(p!= NULL){
        if(p->status = false) return true;
        return false;
    }
    return false;
}


void place_portal(Vector2 coor_peluru,pll *p1,int max_lebar/*- lebar image - lebar object */,int min_lebar,int max_tinggi,int min_tinggi,int arah,float activation){
    // if(p == NULL)
    for(int i=0;i<2;i++){
        if(i%2 == 0){
        insert_value_last(p1,convert_coor_portal(coor_peluru,min_lebar,max_lebar,min_tinggi,max_tinggi,arah),true,arah,activation);
    }
    else{
        insert_value_last(p1,convert_coor_portal(coor_peluru,max_lebar,min_lebar,max_tinggi,min_tinggi,arah),true,arah,activation); 
    }
    }
} 

void cooldown_portal_traversal(pll p){
    if(p == NULL)return;

    if(p->activation >0) p->activation -= GetFrameTime();
    if(p->activation <0 || p->activation == 0){
        p->activation=0;
        p->status=false;
    }
    cooldown_portal_traversal(p->next);
}



void insert_value_last(pll *p,Vector2 coor,bool status,int arah,float activation)
{
    pll temp=NULL;
    if(*p == NULL ) {*p=Alokasi_portal(coor,status,arah,activation); return;}
    temp=traversal(*p);
    temp->next=Alokasi_portal(coor,status,arah,activation);
    temp->next->prev=temp;
}


void insert_last(pll *p,pll inserted_node){
    pll temp=NULL;
    if(*p == NULL ) {*p=inserted_node; return;}
    temp=traversal(*p);
    temp->next=inserted_node;
    temp->next->prev=temp;
}


//bertujuan untuk mengambil node akhir
pll traversal(pll p){
    if(p == NULL)return p;
    if(p->next == NULL)return p;
    p=traversal(p->next);

    return p;
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


void draw_portal(Texture2D purtal,pll mportal,int lgambar,int tgambar,Color portal_color){
    if(mportal == NULL)return;
    if((mportal)->status == true)DrawTexture(purtal,mportal->coor.x-(lgambar/2),mportal->coor.y-(tgambar/2),portal_color);

    draw_portal(purtal,mportal->next,lgambar,tgambar,portal_color);
}

// void teleport_portal(float *targetx,float *targety,portal mportal[],int lgambar,int tgambar,int kotak){
//     for(int i=0;i<kotak;i++){
//         if((mportal+i)->status == true){
//             if(i%2 == 0){
//                 if( (*targetx >= mportal[i].coor.x-(lgambar/2) && *targetx <= mportal[i].coor.x+(lgambar/2)) &&(*targety >= mportal[i].coor.y-(tgambar/2) && *targety <= mportal[i].coor.y+(tgambar/2)) ){
//                 *targetx=mportal[i+1].coor.x;
//                 *targety=mportal[i+1].coor.y;
//                 (mportal+i)->status = false;
//                 (mportal+i+1)->status = false;
                
//                 }    
            
//             }else{
//                if( (*targetx >= mportal[i].coor.x-(lgambar/2) && *targetx <= mportal[i].coor.x+(lgambar/2)) &&(*targety >= mportal[i].coor.y-(tgambar/2) && *targety <= mportal[i].coor.y+(tgambar/2)) ){
//                 *targetx=mportal[i-1].coor.x;  
//                 *targety=mportal[i-1].coor.y;
//                 (mportal+i-1)->status = false;
//                 (mportal+i)->status = false;
//             }
//         }
//     }
//     else{
//     return;
//         }   
//     }
// }



void teleport_portal(float *targetx,float *targety,pll mportal,int lgambar,int tgambar){
    
    if(mportal == NULL)return;
    if(mportal->status != true) return;

    if( (*targetx >= mportal->coor.x-(lgambar/2) && *targetx <= mportal->coor.x+(lgambar/2)) && (*targety >= mportal->coor.y-(tgambar/2) && *targety <= mportal->coor.y+(tgambar/2)) )
    {
        *targetx=mportal->next->coor.x;
        *targety=mportal->next->coor.y;
        (mportal)->status = false;
        (mportal)->next->status = false;
    }

    
    if(mportal->status != true) return;
    mportal=mportal->next;
    if( (*targetx >= mportal->coor.x-(lgambar/2) && *targetx <= mportal->coor.x+(lgambar/2)) && (*targety >= mportal->coor.y-(tgambar/2) && *targety <= mportal->coor.y+(tgambar/2)) )
    {

        *targetx=mportal->prev->coor.x;
        *targety=mportal->prev->coor.y;
        (mportal)->status = false;   
        (mportal)->prev->status = false;
    }
}


// void teleport_portal(float *targetx,float *targety,pll mportal,int lgambar,int tgambar){
    
//     if(mportal == NULL)return;
//     if(mportal->status != true) return;

//     if( (*targetx >= mportal->coor.x-(lgambar/2) && *targetx <= mportal->coor.x+(lgambar/2)) && (*targety >= mportal->coor.y-(tgambar/2) && *targety <= mportal->coor.y+(tgambar/2)) )
//     {
//         *targetx=mportal->next->coor.x;
//         *targety=mportal->next->coor.y;
//         (mportal)->status = false;
//         (mportal)->next->status = false;
//     }
//     // if( (*targetx >= mportal->next->coor.x-(lgambar/2) && *targetx <= mportal->next->coor.x+(lgambar/2)) && (*targety >= mportal->next->coor.y-(tgambar/2) && *targety <= mportal->next->coor.y+(tgambar/2)) )
//     if(mportal->status != true) return;
//     mportal=mportal->next;
//     if( (*targetx >= mportal->coor.x-(lgambar/2) && *targetx <= mportal->coor.x+(lgambar/2)) && (*targety >= mportal->coor.y-(tgambar/2) && *targety <= mportal->coor.y+(tgambar/2)) )
//     {
//         *targetx=mportal->prev->coor.x;
//         *targety=mportal->prev->coor.y;
//         (mportal)->status = false;   
//     }
// }


        