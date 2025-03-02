#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#define LEBAR_LAYAR 800
#define TINGGI_LAYAR 650



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
          while(coorY<TINGGI_LAYAR){
        coorY +=20;
    
        BeginDrawing();
        DrawCircle(coorX,coorY,radius,GOLD);
        ClearBackground(WHITE);
        EndDrawing();
        }
        ClearBackground(WHITE);
        break;
        
        case 265: //up
          while(coorY>TINGGI_LAYAR-650){
        coorY -=20;
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
   



int main(){
     const int screenWidth = 800;
    const int screenHeight = 600;
   

    // Variabel lingkaran
    float circleX = screenWidth / 2.0f;
    float circleY = screenHeight / 2.0f;
    float radius = 30.0f;
    float speed = 5.0f;

    int buffer;
    // Inisialisasi window
    InitWindow(LEBAR_LAYAR,TINGGI_LAYAR, "Gerakkan Lingkaran");
    SetTargetFPS(60);
     while(!WindowShouldClose()){
         buffer=lastbutton();
         printf("pppp%d\n",buffer);
           if(IsKeyDown(KEY_P)){
            portal_blast(circleX,circleY,&buffer);
        }
        if (IsKeyDown(KEY_RIGHT)) circleX += speed;
        if (IsKeyDown(KEY_LEFT)) circleX -= speed;
        if (IsKeyDown(KEY_DOWN)) circleY += speed;
        if (IsKeyDown(KEY_UP)) circleY -= speed;
        
        // Gambar
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle((int)circleX, (int)circleY, radius, BLUE);
        DrawText("BUG cuy", 10, 10, 20, DARKGRAY);
        EndDrawing();      
     }
         CloseWindow();
    return 0;
}
