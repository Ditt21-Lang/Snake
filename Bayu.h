#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gilang.h"
#ifndef BAYU_H
#define BAYU_H

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define BOX_WIDTH 400
#define BOX_HEIGHT 540

// Untuk menentukan layar saat ini dalam game
typedef enum {
    MENU,
    MODE_SELECTION,
    HOW_TO_PLAY,
    ENDLESS,
    STAGE
} GameScreen;

// Struct untuk node tombol berbentuk single linked list
typedef struct ButtonNode {
    Rectangle border;
    char* text;
    bool hover;
    struct ButtonNode* next;
} ButtonNode;

// Struct untuk node tekstur berbentuk single linked list
typedef struct TextureNode {
    Texture2D texture;
    int page;
    Vector2 position;
    struct TextureNode *next;
} TextureNode;

// Menginisialisasi linked list tombol (button) dengan posisi Y awal tertentu
ButtonNode* InitButtons(int startY);

// Menambahkan tombol baru ke linked list tombol dengan teks dan posisi Y tertentu
void AppendButton(ButtonNode** head, const char* text, int yPos);

// Memperbarui status tombol berdasarkan input mouse dan mengubah tampilan layar sesuai tombol yang ditekan
void UpdateButtons(ButtonNode *head, GameScreen *screen);

// Menggambar semua tombol di layar dengan warna berbeda saat di-hover
void DrawButtons(ButtonNode *head);

// Membebaskan semua memori yang digunakan oleh linked list
void FreeButtons(ButtonNode *head);

// Menggambar tekstur dengan ukuran yang disesuaikan agar tidak melebihi lebar maksimum
void DrawScaledTexture(Texture2D texture, int x, int y, int maxWidth);

// Menambahkan node tekstur baru ke linked list tekstur untuk ditampilkan pada halaman tertentu
void AddTexture(TextureNode **head, const char *path, int page, Vector2 position);

// Membebaskan semua memori dan tekstur yang digunakan oleh linked list
void FreeTextures(TextureNode *head);

// Membuat node tombol baru dengan teks dan posisi Y tertentu
ButtonNode* CreateButton(const char* text, int yPos);

// Digunakan untuk memilih sprite tikungan yang sesuai dari spritesheet (tubuh ular yang bengkok)
int snakeSpritesheet(Position prevDirection, Position nextDirection);

#endif
