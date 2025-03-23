#include <stdio.h>
#include "buffer.h"


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