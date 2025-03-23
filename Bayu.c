#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "Bayu.h"
#include "Gilang.h"

void InitButtons(Button buttons[], const char *texts[], int count, int startY) {
    for (int i = 0; i < count; i++) {
        buttons[i].border = (Rectangle){200, startY + i * 100, 200, 50};
        buttons[i].text = texts[i];
        buttons[i].hover = false;
    }
}

void UpdateButtons(Button buttons[], int count, GameScreen *screen) {
    Vector2 mousePoint = GetMousePosition();
    for (int i = 0; i < count; i++) {
        buttons[i].hover = CheckCollisionPointRec(mousePoint, buttons[i].border);
        if (buttons[i].hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (*screen == MENU) {
                if (i == 0) *screen = MODE_SELECTION;
                else if (i == 1) *screen = HOW_TO_PLAY;
                else if (i == 2) {
                    CloseWindow();
                    exit(0);
                }
            } else if (*screen == MODE_SELECTION) {
                if (i == 0 || i == 1) *screen = GAMEPLAY;
                else if (i == 2) *screen = MENU;
            }
        }
    }
}

void DrawButtons(Button buttons[], int count) {
    for (int i = 0; i < count; i++) {
        DrawRectangleRec(buttons[i].border, buttons[i].hover ? LIGHTGRAY : GRAY);
        DrawText(buttons[i].text, buttons[i].border.x + 35, buttons[i].border.y + 15, 20, WHITE);
    }
}

void DrawScaledTexture(Texture2D texture, int x, int y, int maxWidth) {
    float scale = (texture.width > maxWidth) ? (float)maxWidth / texture.width : 1.0f;
    int newWidth = texture.width * scale;
    int newHeight = texture.height * scale;
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, 
                   (Rectangle){x - newWidth / 2, y, newWidth, newHeight}, 
                   (Vector2){0, 0}, 0.0f, WHITE);
}

int snakeSpritesheet(Position prevDirection, Position nextDirection) {

    int spriteIndex = 0;
    if (prevDirection.x < 0 && nextDirection.y < 0) { 
        spriteIndex = 4; // kiri ke Atas
    } else if (prevDirection.x > 0 && nextDirection.y < 0) { 
        spriteIndex = 3; // kanan ke Atas
    } else if (prevDirection.x < 0 && nextDirection.y > 0) { 
        spriteIndex = 6; // kiri ke Bawah
    } else if (prevDirection.x > 0 && nextDirection.y > 0) { 
        spriteIndex = 5; // kanan ke Bawah
    } else if (prevDirection.y < 0 && nextDirection.x < 0) { 
        spriteIndex = 4; // atas ke Kiri
    } else if (prevDirection.y < 0 && nextDirection.x > 0) { 
        spriteIndex = 3; // atas ke Kanan
    } else if (prevDirection.y > 0 && nextDirection.x < 0) { 
        spriteIndex = 6; // bawah ke Kiri
    } else if (prevDirection.y > 0 && nextDirection.x > 0) { 
        spriteIndex = 5; // bawah ke Kanan
    } else { 
        spriteIndex = -1; // Default sprite (misal kepala atau badan)
    }
    return spriteIndex;
    
}
