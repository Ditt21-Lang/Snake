#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"

void ReverseSnake(SNAKE *SnakE){
    Vector2 tempBody[100];

    for (int i = 0; i < SnakE->Panjang; i++){
        tempBody[i] = SnakE->Body[SnakE->Panjang - 1 - i];
        }    /* menyimpan tubuh ular dalam urutan terbalik */

    for (int i = 0; i < SnakE->Panjang; i++){
        SnakE->Body[i] = tempBody[i];
        }    /* mengganti posisi tubuh ular dengan tubuh yang sudah dibalik */

    SnakE->Position = SnakE->Body[0]; /* mengatur posisi kepala sesuai dengan tubuh yang baru dibalik */

    if(SnakE->Speed.X !=0) {
        SnakE->Speed.X = -SnakE->Speed.X; }
    if(SnakE->Speed.Y !=0) {
        SnakE->Speed.Y = -SnakE->Speed.Y; }

    if (IsKeyPressed(KEY_SPACE)) {
        ReverseSnake(SnakE);
        }
}
