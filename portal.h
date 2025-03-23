#ifndef PORTAL_H
#define PORTAL_H
#include "raylib.h"


typedef struct{
    Vector2 coor;
    bool status;
    Image gambar_portal;
    int arah;
    float cooldown;
    float activation;
}portal;

Vector2 convert_coor_portal(Vector2 coor,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah){
void place_portal(Vector2 obj,portal *p1,int kotak,int max_lebar,int min_lebar,int max_tinggi,int min_tinggi,int arah,float cooldown,float activation){
void draw_portal(Texture2D purtal,int kotak,portal *mportal,int lgambar,int tgambar){

void teleport_portal(float *targetx,float *targety,portal mportal[],int lgambar,int tgambar,int kotak){



#endif