#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"
#include "Gilang.h"

void ReverseSnake(Snake *Snake){
    Vector2 tempBody[100];

    for (int i = 0; i < Snake->Panjang; i++){
        tempBody[i] = Snake->Body[Snake->Panjang - 1 - i];
        }    /* menyimpan tubuh ular dalam urutan terbalik */

    for (int i = 0; i < Snake->Panjang; i++){
        Snake->Body[i] = tempBody[i];
        }    /* mengganti posisi tubuh ular dengan tubuh yang sudah dibalik */

    Snake->Position = Snake->Body[0]; /* mengatur posisi kepala sesuai dengan tubuh yang baru dibalik */

    if(Snake->Speed.X !=0) {
        Snake->Speed.X = -Snake->Speed.X; }
    if(Snake->Speed.Y !=0) {
        Snake->Speed.Y = -Snake->Speed.Y; }

    if (IsKeyPressed(KEY_SPACE)) {
        ReverseSnake(Snake);
        }
}
