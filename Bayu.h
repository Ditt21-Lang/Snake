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

typedef enum {
    MENU,
    MODE_SELECTION,
    HOW_TO_PLAY,
    ENDLESS,
    STAGE
} GameScreen;

typedef struct ButtonNode {
    Rectangle border;
    char* text;
    bool hover;
    struct ButtonNode* next;
} ButtonNode;

typedef struct TextureNode {
    Texture2D texture;
    int page;
    Vector2 position;
    struct TextureNode *next;
} TextureNode;

ButtonNode* InitButtons(int startY);
void AppendButton(ButtonNode** head, const char* text, int yPos);
void UpdateButtons(ButtonNode *head, GameScreen *screen);
void DrawButtons(ButtonNode *head);
void FreeButtons(ButtonNode *head);
void DrawScaledTexture(Texture2D texture, int x, int y, int maxWidth);
void AddTexture(TextureNode **head, const char *path, int page, Vector2 position);
void FreeTextures(TextureNode *head);
int snakeSpritesheet(Position prevDirection, Position nextDirection);

#endif
