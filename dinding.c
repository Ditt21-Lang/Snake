#include "dinding.h"
#include "raylib.h"
#define GRID_WIDTH 30
#define GRID_HEIGHT 30

void CekNabrakDinding(Vector2 newHead, bool *alive) {
    if (newHead.x < 2 || newHead.x >= GRID_WIDTH - 2 ||
        newHead.y < 2 || newHead.y >= GRID_HEIGHT - 2) {
        *alive = false;
    }
}
