#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "screens/screens.h"
#include "audio/audio.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void startGUI() {

    // Initialization of the random number generator
    srand(time(NULL));

    // Initialization of the audio
    InitAudio();

    int isOnGameplay = 0;
    SetExitKey(KEY_NULL); // Pressing ESC doesn't close the window
    PlayMusicStream(theme);
    SetTargetFPS(60);
    InitTitleScreen();

    // Textures (background images) loading to memory
    Texture2D title = LoadTexture("assets/title.png");
    Texture2D main = LoadTexture("assets/main.png");
    Texture2D pause = LoadTexture("assets/pause.png");
    Texture2D win = LoadTexture("assets/win.png");
    Texture2D loss = LoadTexture("assets/loss.png");

    SCREEN currentScreen = TITLE_SCREEN;

    // Main game loop (executed each tick)
    while (!WindowShouldClose()) {

        if(currentMusic != NULL) {
            UpdateMusicStream(*currentMusic);
        }

        switch (currentScreen) {
            case TITLE_SCREEN:
                UpdateTitleScreen();
                break;
            case GAMEPLAY_SCREEN:
                UpdateGameplayScreen();
                break;
            case PAUSE_SCREEN:
                UpdatePauseScreen();
                break;
            case WIN_SCREEN:
                UpdateWinScreen();
                break;
            case LOSS_SCREEN:
                UpdateLossScreen();
                break;
        }

    }

    // Unloading the textures
    UnloadTexture(title);
    UnloadTexture(main);
    UnloadTexture(pause);
    UnloadTexture(win);
    UnloadTexture(loss);


    CloseAudio();
    CloseWindow();
}
