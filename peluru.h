#ifndef PELURU_H
#define PELURU_H
#include "raylib.h"
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

    
    void p_pressed(peluru *mpeluru,int buffer_mengisi,Vector2 target_obj);
    void move_peluru(peluru *mpeluru,float speed);
    bool check_peluru(float coor,int lebar_tinggi,int min);

#endif