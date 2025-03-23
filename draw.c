#include "draw.h"

    Texture2D menggambar(Image *edit,int width,int height){
     ImageResize(edit,width,height);
     Texture2D textuar=LoadTextureFromImage(*edit);
     UnloadImage(*edit);
     return textuar;
    }
