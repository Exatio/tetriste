#include "raylib.h"
#include <stdio.h>

static int finishScreen = 0;
static Texture2D logo;
static Color backgroundColor = {0x04, 0x62, 0xD6, 0xFF};



void InitTitleScreen(void) {
    logo = LoadTexture("assets/logo.png");
}

void UpdateDrawTitleScreen(void) {

    if(IsKeyPressed(KEY_ENTER)) { // Entrée est pressé
        finishScreen = 1;
    }
    // Afficher les FPS
    DrawFPS(10, 10);

    BeginDrawing();

    ClearBackground(backgroundColor);

    DrawTexture(logo, GetScreenWidth()/2 - 512/2, 40, WHITE);
    DrawText("APPUYEZ SUR ENTREE POUR COMMENCER LA PARTIE", GetScreenWidth()/2 - MeasureText("APPUYEZ SUR ENTREE POUR COMMENCER LA PARTIE", 40)/2, 40 + 512 + (GetScreenHeight() - 40 - 512)/2 - 20, 40, LIGHTGRAY);

    EndDrawing();
}

void UnloadTitleScreen(void) {
    UnloadTexture(logo);
}

int FinishTitleScreen(void) {
    return finishScreen;
}

