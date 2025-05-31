#ifndef EMIR_H
#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define KANAN 262
#define KIRI 263
#define BAWAH 264
#define ATAS 265
#define EMIR_H

typedef struct main_portal *pll;

//variable peluru
typedef struct{
    Vector2 coor;
    float speed;
    bool status;
    int buffer;
    Image gambar_peluru;
    Texture2D texture;
}peluru;


typedef struct main_portal{
    Vector2 coor;
    bool status;
    Image gambar_portal;
    int arah;
    float activation;
    pll next;
    pll prev;
}portal;

//utilitas
int lastbutton();
bool yes();
    
//peluru
void p_pressed(peluru *mpeluru,int buffer_mengisi,Vector2 target_obj);
void move_peluru(peluru *mpeluru,float speed);
bool check_peluru(float coor,int lebar_tinggi,int min);
       
//bagian portal

Vector2 convert_coor_portal(Vector2 portal_coordinat,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah);
void place_portal(Vector2 coor_peluru,pll *p1,int max_lebar/*- lebar image - lebar object */,int min_lebar,int max_tinggi,int min_tinggi,int arah,float activation);
bool cooldown(float *target);
Texture2D menggambar(Image *edit,int width,int height);
void draw_portal(Texture2D purtal,pll mportal,int lgambar,int tgambar,Color portal_color);
void teleport_portal(float *targetx,float *targety,pll mportal,int lgambar,int tgambar);
    pll Alokasi_portal( Vector2 coor,bool status,int arah,float activation);
    void dellall_portal(pll *target);
void insert_last(pll *p,pll inserted_node);
void insert_value_last(pll *p,Vector2 coor,bool status,int arah,float activation);
pll traversal(pll p);
void cooldown_portal_traversal(pll p);

bool check_portal_activation(pll p);
#endif