#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
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
    GAMEPLAY
} GameScreen;

typedef struct {
    Rectangle border;
    const char *text;
    bool hover;
} Button;

void InitButtons(Button buttons[], const char *texts[], int count, int startY);
void UpdateButtons(Button buttons[], int count, GameScreen *screen);
void DrawButtons(Button buttons[], int count);
void DrawScaledTexture(Texture2D texture, int x, int y, int maxWidth);
int snakeSpritesheet(Position prevDirection, Position nextDirection);

#endif