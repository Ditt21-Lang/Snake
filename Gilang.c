#include "raylib.h"
#include <stdlib.h>
#include "Gilang.h"
#include "Bayu.h"
#define LEBAR_LAYAR 600
#define TINGGI_LAYAR 800
#define UKURAN_BLOCK 20

// IS: Snake belum ada
// FS: Snake sudah ada dan dialokasikan memorinya
void InitSnake(Snake *snake){
    float startX = LEBAR_LAYAR/2;
    float startY = TINGGI_LAYAR/2;
    snake->direction= (Vector2){UKURAN_BLOCK, 0};
    snake->head = NULL;
    snake->tail = NULL;


    for (int i = 0; i < 8; i++) {
        SnakeNode* newNode = (SnakeNode*)malloc(sizeof(SnakeNode));
        newNode->position = (Vector2){startX - i * UKURAN_BLOCK, startY};
        newNode->prev = NULL;
        newNode->next = NULL;

        if(i == 0){
            newNode->sprite = (Rectangle){0, 0, 20, 20};
        } else if (i == 7){
            newNode->sprite = (Rectangle){40, 0, 20, 20};
        } else{
            newNode->sprite = (Rectangle){140, 0 ,20, 20};
        }

        if(snake->head == NULL && snake->tail == NULL){
            snake->head = newNode;
            snake->tail = newNode;
        } else {
            newNode->next = NULL;
            snake->tail->next = newNode;
            newNode->prev = snake->tail;
            snake->tail =newNode; 
        }
    }
}

//IS: Dua buah Node posinya diketahui
//FS: Mengembalikan Nilai selisih antara kedua node
Vector2 getDir(Vector2 A, Vector2 B){
    return (Vector2){A.x - B.x, A.y - B.y};
}

//IS : Snake sudah diinisialisasi (sudah ada)
//FS : Snake digambar di layar
void DrawSnake(Snake *snake, Texture2D texture) {
    SnakeNode* current = snake->head;
    while (current != NULL) {
        Vector2 tikpus = (Vector2){UKURAN_BLOCK / 2.0f, UKURAN_BLOCK / 2.0f};
        Rectangle ukuran = {current->position.x + UKURAN_BLOCK / 2.0f, 
                            current->position.y + UKURAN_BLOCK / 2.0f, 
                            UKURAN_BLOCK, 
                            UKURAN_BLOCK};

        float rotation = 0;
        if(current == snake->head){
            current->sprite = (Rectangle){0, 0, 20, 20};
            if (snake->direction.x > 0){
                rotation = 90;
            } else if (snake->direction.x < 0){
                rotation = 270;
            } else if (snake->direction.y > 0){
                rotation = 180;
            } else if (snake->direction.y < 0){
                rotation = 0;
            }

        } else if (current->next == NULL){
            current->sprite = (Rectangle){40, 0, 20, 20};
            Vector2 direction = getDir(current->prev->position, current->position);
            if (direction.x > 0){
                rotation = 90;
            } else if (direction.x < 0){
                rotation = 270;
            } else if (direction.y > 0){
                rotation = 180;
            } else if (direction.y < 0){
                rotation = 0;
            }
        } else {
            Vector2 prevDir = getDir(current->prev->position, current->position);
            Vector2 nextDir = getDir(current->position, current->next->position);

            if ((prevDir.x > 0 && nextDir.y > 0) || (prevDir.y < 0 && nextDir.x < 0)) {
                current->sprite = (Rectangle){60, 0, 20, 20};
            } else if ((prevDir.x < 0 && nextDir.y > 0) || (prevDir.y < 0 && nextDir.x > 0)){
                current->sprite = (Rectangle){80, 0, 20, 20};
            } else if ((prevDir.x > 0 && nextDir.y < 0) || (prevDir.y > 0 && nextDir.x < 0)){
                current->sprite = (Rectangle){100, 0, 20, 20};
            } else if ((prevDir.x < 0 && nextDir.y < 0) || (prevDir.y > 0 && nextDir.x > 0)){
                current->sprite = (Rectangle){120, 0, 20, 20};
            }

            // Badan lurus horizontal
            else if (prevDir.x != 0 && nextDir.x != 0) {
                current->sprite = (Rectangle){140, 0, 20, 20};
            }
            // Badan lurus vertikal
            else if (prevDir.y != 0 && nextDir.y != 0) {
                current->sprite = (Rectangle){20, 0, 20, 20};
            }
        }
        DrawTexturePro(texture, current->sprite, ukuran, tikpus, rotation, WHITE);

        current = current->next;
    }
}

//IS: Snake ada dan bergerak di layar
//FS: Mengembalikan nilai true ketika kepala snake bertabrakan dengan dirinya sendiri
bool cekTabrakan(Snake *snake){
    SnakeNode* current;
    current = snake->head->next;
    while(current != NULL){
        if(snake->head->position.x == current->position.x && snake->head->position.y == current->position.y){
            return true;
        }
        current = current->next;
    }
    return false;
}

//IS: Snake ada dan sudah digambar
//FS: Snake berpindah sesuai arah yang ditentukan dari kepala hingga buntut
void UpdateSnake(Snake *snake) {
    if(snake->direction.x !=0){
        if(IsKeyPressed(KEY_UP)){
            snake->direction = (Vector2){0, -UKURAN_BLOCK};
        }
        else if(IsKeyPressed(KEY_DOWN)){
            snake->direction = (Vector2){0, UKURAN_BLOCK};
        }
    }
    else if(snake->direction.y != 0){
        if(IsKeyPressed(KEY_RIGHT)){
            snake->direction = (Vector2){UKURAN_BLOCK, 0};
        }
        else if(IsKeyPressed(KEY_LEFT)){
            snake->direction = (Vector2){-UKURAN_BLOCK, 0};
        }
    }

    // Geser posisi tiap segmen ke posisi segmen sebelumnya, dari ekor ke kepala
    SnakeNode* current = snake->tail;
    while (current != snake->head){
        current->position = current->prev->position;
        current = current->prev;
    } 
        // Perbarui posisi kepala dengan menambahkan kecepatan
    snake->head->position.x += snake->direction.x;
    snake->head->position.y += snake->direction.y;

    cekTabrakan(snake);
} 

//IS: Snake sudah ada 
//FS: Node Snake bertambah
void tambahNode(Snake *snake){
    SnakeNode* newbody = (SnakeNode*)malloc(sizeof(SnakeNode));
    newbody->position = snake->direction;
    newbody->next = NULL;
    newbody->prev = NULL;
    newbody->prev = snake->tail;
    snake->tail->next = newbody;
    snake->tail = newbody;
}

//IS: Snake sudah ada
//FS: Seluruh node snake di-dealokasi
void freeSnake(Snake *snake){
    if (snake->head != NULL){
        while (snake->tail != NULL){
            SnakeNode* current = snake->tail;
            snake->tail = snake->tail->prev;
            free(current); 
        }
        snake->head = NULL;
        snake->tail = NULL;
    }
}

//IS: Snake sudah ada bergerak di layar
//FS: Mengambalikan nilai true ketika posisi kepala snake sama dengan posisi makanan
bool CheckMakanan(Snake *snake, Makanan *food) {
    if (snake->head->position.x == food->position.x && snake->head->position.y == food->position.y){
        return true;
    }
    return false;
}