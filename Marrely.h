#ifndef MARRELY_H
#define MARRELY_H

#include "raylib.h"

#define CELL_SIZE 20
#define GRID_WIDTH  (520 / CELL_SIZE)
#define GRID_HEIGHT (520 / CELL_SIZE)
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 800

    typedef struct {
        int x, y;
    } Position;

    typedef struct {
        Position position;
    } Makanan;

    typedef struct Enemy {
        Position position;
        int direction;
        int isVertical;
        struct Enemy *next;
    } Enemy;

    typedef struct {
        Enemy *head;
        int count;
    } EnemyList;

    typedef struct RintanganNode {
        Position posisi;
        struct RintanganNode *next;
    } RintanganNode;

// Fungsi utama
void GenerateMakanan(Makanan *makanan, RintanganNode *rintanganHead);
void GenerateRintangan(RintanganNode **, int level);
void DrawGame(Makanan *makanan, RintanganNode *rintanganHead, EnemyList *enemy, int enemyCount,
              int score, int level,
              Texture2D background, Texture2D borderTexture,
              Texture2D makananTexture, Texture2D enemyTexture, Texture2D rintanganTexture);
void FreeRintangan(RintanganNode **head);


#endif
