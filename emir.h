#ifndef EMIR_H
#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define KANAN 262
#define KIRI 263
#define BAWAH 264
#define ATAS 265
#define BATAS_PORTAL_V 650
#define BATAS_PORTAL_H 750
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650
#define EMIR_H

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

typedef struct{
    Vector2 coor;
    bool status;
    Image gambar_portal;
    int arah;
    float cooldown;
    float activation;
}portal;



//utilitas
int lastbutton();
    bool yes();
    
//peluru
void p_pressed(peluru *mpeluru,int buffer_mengisi,Vector2 target_obj);
void move_peluru(peluru *mpeluru,float speed);
    bool check_peluru(float coor,int lebar_tinggi,int min);
    
    
    
//bagian portal\\

Vector2 convert_coor_portal(Vector2 coor,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah);
    void place_portal(Vector2 obj,portal *p1,int kotak,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah,float cooldown,float activation);
bool cooldown(float *target);
    Texture2D menggambar(Image *edit,int width,int height);
    void draw_portal(Texture2D purtal,int kotak,portal *mportal,int lgambar,int tgambar);
void teleport_portal(float *targetx,float *targety,portal mportal[],int lgambar,int tgambar,int kotak);

#endif