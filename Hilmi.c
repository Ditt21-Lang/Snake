#include "raylib.h"
#include "stdlib.h"
#include "Hilmi.h"
#include "Gilang.h"
#define GRID_WIDTH 30
#define GRID_HEIGHT 30

void ReverseSnake(Snake *snake) {
    for (int i = 0; i < snake->panjang / 2; i++) {
        Vector2 temp = snake->badan[i];                                 /* simpan sementara bagian badan diposisi i*/
        snake->badan[i] = snake->badan[snake->panjang - 1 - i];
        snake->badan[snake->panjang - 1 - i] = temp;
     }

    snake->position = snake->badan[0];                                  /* pastiin kepala di posisi yang benar*/
    /*menentukan arah gerak baru*/
    Vector2 diff = (Vector2){ 
        snake->badan[0].x - snake->badan[1].x, 
        snake->badan[0].y - snake->badan[1].y 
    };

    snake->speed = diff;                                        /* perbarui kecepatan*/

}

/* if (IsKeyPressed(KEY_SPACE)) {
    ReverseSnake(&snake);
} */

void CekTabrakBorder(Vector2 head, Snake *snake, int *lives){
    if (head.x < 2 || head.x >=GRID_WIDTH -2 ||
        head.y < 2 || head.y >=GRID_HEIGHT -2){
            (*lives)--;
            printf("Lives : "%d\n", *lives);
        }
}

void CekTabrakRintangan(Vector2 head, Snake *snake, Rintangan *rintangan, int *count, int *lives){
        for (int i = 0; i < rintangan->count; i++){
            if (head.x == rintangan->rintangan[i].x
                && head.y == rintangan->rintangan[i].y){
                    (*lives)--;
                    printf("Lives : %d\n", *lives);
                }
        }
}

void CekTabrakEnemy(Vector2 head, Snake *snake, Enemy *enemy, int *count, int *lives){
        for (int i = 0; i < enemy->count; i++){
            if (head.x == enemy->enemy[i].x 
                && head.y == enemy->enemy[i].y){
                (*lives)--;
                printf("Lives : %d\n", *lives);
                }
        }
}