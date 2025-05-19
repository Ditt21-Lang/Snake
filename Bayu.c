#include "Bayu.h"


ButtonNode* InitButtons(int startY) {
    return NULL;
}

void AppendButton(ButtonNode** head, const char* text, int yPos) {
    ButtonNode* newButton = CreateButton(text, yPos);
    
    if (*head == NULL) {
        *head = newButton;
    } else {
        ButtonNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newButton;
    }
}

ButtonNode* CreateButton(const char* text, int yPos) {
    ButtonNode* node = (ButtonNode*)malloc(sizeof(ButtonNode));
    node->border = (Rectangle){200, yPos, 200, 50};
    node->text = (char*)malloc(strlen(text) + 1);
    strcpy(node->text, text);
    node->hover = false;
    node->next = NULL;
    return node;
}

ButtonNode* TextNode(const char* text, int yPos) {
    ButtonNode* node = (ButtonNode*)malloc(sizeof(ButtonNode));
    node->border = (Rectangle){200, yPos, 200, 50};
    node->text = (char*)malloc(strlen(text) + 1);
    strcpy(node->text, text);
    node->hover = false;
    node->next = NULL;
    return node;
}

void UpdateButtons(ButtonNode *head, GameScreen *screen) {
    Vector2 mousePoint = GetMousePosition();
    int i = 0;
    for (ButtonNode *node = head; node; node = node->next, i++) {
        node->hover = CheckCollisionPointRec(mousePoint, node->border);
        if (node->hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (*screen == MENU) {
                if (i == 0) *screen = MODE_SELECTION;
                else if (i == 1) *screen = HOW_TO_PLAY;
                else if (i == 2) {
                    CloseWindow();
                    exit(0);
                }
            } else if (*screen == MODE_SELECTION) {
                if (i == 0) *screen = ENDLESS;
                else if (i == 1) *screen = STAGE;
                else if (i == 2) *screen = MENU;
            }
        }
    }
}

void DrawButtons(ButtonNode *head) {
    for (ButtonNode *node = head; node; node = node->next) {
        DrawRectangleRec(node->border, node->hover ? LIGHTGRAY : GRAY);
        DrawText(node->text, node->border.x + 35, node->border.y + 15, 20, WHITE);
    }
}

void FreeButtons(ButtonNode* head) {
    ButtonNode* current = head;
    while (current != NULL) {
        ButtonNode* next = current->next;
        free(current->text);
        free(current);
        current = next;
    }
}

void DrawScaledTexture(Texture2D texture, int x, int y, int maxWidth) {
    float scale = (texture.width > maxWidth) ? (float)maxWidth / texture.width : 1.0f;
    int newWidth = texture.width * scale;
    int newHeight = texture.height * scale;
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, (Rectangle){x - newWidth / 2, y, newWidth, newHeight}, (Vector2){0, 0}, 0.0f, WHITE);
}

void AddTexture(TextureNode **head, const char *path, int page, Vector2 position) {
    TextureNode *newNode = (TextureNode *)malloc(sizeof(TextureNode));
    newNode->texture = LoadTexture(path);
    newNode->page = page;
    newNode->position = position;
    newNode->next = *head;
    *head = newNode;
}

void FreeTextures(TextureNode *head) {
    TextureNode *current = head;
    while (current != NULL) {
        TextureNode *next = current->next;
        UnloadTexture(current->texture);
        free(current);
        current = next;
    }
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