#include "cooldown.h"

bool cooldown(float *target){
    if(*target > 0){
        *target-=GetFrameTime();
        return false;
    }else
        *target=0;
        return true;
}