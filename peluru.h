//variable peluru


typedef struct{
    Vector2 coor;
    float speed;
    bool status;
    int buffer;
    Image gambar_peluru;
    Texture2D texture;
}peluru;

//LoadImage("portual.png") langsung masukin ke fungsi
Texture2D imgTOtexture(Image img,Texture2D texture){
    texture=LoadTextureFromImage(img);
    return texture;
}


//apabila p ditekan dijadikan fungsi "mainobjX","mainobjY"
if(IsKeyPressed //p true)
void p_pressed(peluru *mpeluru,int *buffer_tujuan,int buffer_mengisi,Vector2 target_obj){
    (*mpeluru).status=true;
    (*mpeluru).coor.x=target_obj.x;
    (*mpeluru).coor.y=target_obj.y;
    *buffer_tujuan=buffer_mengisi;
    }


    //jadi fungsikah dan ada buffer dan ditambahkan speed:
if(mpeluru.status){
    void move_peluru(peluru *mpeluru,float speed){
        switch(mpeluru->buffer){
        case KANAN:
        mpeluru->koordinat_peluru.x +=speed;
        break;
        case KIRI:
        mpeluru->koordinat_peluru.x -=speed;
        break;
        case BAWAH:
        mpeluru->koordinat_peluru.x -=speed;
        break;
        case ATAS:
        mpeluru->koordinat_peluru.x +=speed;
        break;
        }
        }
    }

    void check_peluru(){

    }