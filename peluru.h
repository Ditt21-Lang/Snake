#ifndef gugugaga_h
#define gugugaga_h

//variable peluru
typedef struct{
    Vector2 coor;
    float speed;
    bool status;
    int buffer;
    Image gambar_peluru;
    Texture2D texture;
}peluru;

void p_pressed(peluru *mpeluru,int *buffer_tujuan,int buffer_mengisi,Vector2 target_obj);
void move_peluru(peluru *mpeluru,float speed);
bool check_peluru(coor x/y,max and min);
bool yes();
int lastbutton();
    #endif