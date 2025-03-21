
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

//LoadImage("portual.png") langsung masukin ke fungsi
Texture2D imgTOtexture(Image img,Texture2D texture){
    texture=LoadTextureFromImage(img);
    return texture;
}


//apabila p ditekan dijadikan fungsi "mainobjX","mainobjY"
if(IsKeyPressed //p true)
void p_pressed(peluru *mpeluru,int buffer_mengisi,Vector2 target_obj){
    (*mpeluru).status=true;
    (*mpeluru).coor.x=target_obj.x;
    (*mpeluru).coor.y=target_obj.y;
    (*mpeluru).buffer=buffer_mengisi;
    }


    //jadi fungsikah dan ada buffer dan ditambahkan speed:
if(mpeluru.status){
    void move_peluru(peluru *mpeluru,float speed){
        switch(mpeluru->buffer){
        case 262//KANAN:
        mpeluru->coor.x +=speed;
        break;
        case 263//KIRI:
        mpeluru->coor.x -=speed;
        break;
        case 264//BAWAH:
        mpeluru->coor.y -=speed;
        break;
        case 265//ATAS:
        mpeluru->coor.y +=speed;
        break;
        }
        }
    }

    bool check_peluru(coor x/y,max and min){
        if(coor>max || coor<min){
            true;
        }
    }    