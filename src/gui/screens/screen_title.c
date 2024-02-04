#include "raylib.h"

void UpdateDrawTitleScreen(Texture2D background) {

    if(IsKeyPressed(KEY_ENTER)) { // We end the title screen
        finishScreen = 1;
    }

    // Show FPS
    DrawFPS(10, 10);

    BeginDrawing();

    ClearBackground(backgroundColor);

    DrawTexture(logo, GetScreenWidth()/2 - 512/2, 40, WHITE);

    EndDrawing();
}
