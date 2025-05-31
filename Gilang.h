#include <stdio.h>
#include "raylib.h"
#include "Marrely.h"
#ifndef GILANG_H
#define GILANG_H

//Elemen untuk tiap node "Snake"
typedef struct SnakeNode{
    Vector2 position;
    Rectangle sprite;
    struct SnakeNode* next;
    struct SnakeNode* prev;
}SnakeNode;

typedef struct{
    SnakeNode* head;
    SnakeNode* tail;  
    Vector2 direction;
    Texture2D tekstur;
} Snake;

void InitSnake(Snake *snake); // Menginisialisasi Snake di awal Permainan dan mengalokasi memori untuk tiap node
void DrawSnake(Snake *snake, Texture2D texture); // Menggambar Snake dan
void UpdateSnake(Snake *snake); // Mengatur kemana arah snake akan bergerak selama looping
bool cekTabrakan(Snake *snake); //Mengecek apakah Snake terkena dirinya sendiri
Vector2 getDir(Vector2 A, Vector2 B); // Mengembalikan nilai selisih dari dua buah node snake


//Tambahan untuk Double Linked List
void tambahNode(Snake *snake); // Menambah Node Snake
void freeSnake(Snake *snake); // Mengahapus Node Snake dan dealokasi memorinya

//Dibutuhkan header Marrely
bool CheckMakanan(Snake *snake, Makanan *food); // Mengecek apakah kepala dari snake posisinya sama dengan makanan

#endif