#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650

   struct portal{
   int activation_time;
};

struct peluru{
int cooldown;
int coorX;
int coorY;
};



void draw_portal(){
   
    
}

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


   void portal_blast(int coorX,int coorY,int *buffer){
       float radius=30;
    switch(*buffer){
        case 262: //right
        while(coorX < LEBAR_LAYAR){
        coorX +=20;
        BeginDrawing();
        DrawCircle(coorX,coorY,radius,GOLD);
        ClearBackground(WHITE);
        EndDrawing();
        }
        ClearBackground(WHITE);
        break;
        
        case 263: //left
        while(coorX>LEBAR_LAYAR-800){
        coorX -=20;
        BeginDrawing();
        DrawCircle(coorX,coorY,radius,GOLD);
        ClearBackground(WHITE);
        EndDrawing();
            printf("huaaa%d\n",lastbutton());
        }
        ClearBackground(WHITE);
        break;
        
        case 264: //down
        while(coorY>TINGGI_LAYAR-650){
        coorY -=20;
        BeginDrawing();
        DrawCircle(coorX,coorY,radius,GOLD);
        ClearBackground(WHITE);
        EndDrawing();
        }
        ClearBackground(WHITE);
        break;
        
        case 265: //up
        while(coorY<TINGGI_LAYAR){
        coorY +=20;
        BeginDrawing();
        DrawCircle(coorX,coorY,radius,GOLD);
        ClearBackground(WHITE);
        EndDrawing();
        }
        ClearBackground(WHITE);
        break;
        }
        ClearBackground(WHITE);
        printf("a%d\n",lastbutton());
    }
   

int init_cooldown(int cooldown){
    
}


bool cooldown_timer(int timer){
    while(timer>0){
        sleep(1);
        --timer;
        return true;
    }
}


int main(){
    struct peluru P1;
    int buffer;
    // Inisialisasi window
    InitWindow(LEBAR_LAYAR,TINGGI_LAYAR, "Gerakkan Lingkaran");
    SetTargetFPS(60);
     while(!WindowShouldClose()){
         buffer=lastbutton();
         printf("pppp%d\n",buffer);
           if(IsKeyPressed(KEY_P)){
            portal_blast(200,300,&buffer);
        }

         BeginDrawing();
    ClearBackground(GOLD);
    DrawCircle(400,400,90,BLUE);
    EndDrawing();
      
      
     }
         CloseWindow();
    return 0;
}

   struct portal{
   int activation_time;
};

struct peluru{
int cooldown;
int coorX;
int coorY;
};



void draw_portal(){
   
    
}




int init_cooldown(int cooldown){
    
}


bool cooldown_timer(int timer){
    while(timer>0){
        sleep(1);
        --timer;
        return true;
    }
}
