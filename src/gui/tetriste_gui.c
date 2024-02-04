#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "screens/screens.h"
#include "audio/audio.h"
#include "tetriste_gui.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void startGUI() {

    // Initialization of the random number generator
    srand(time(NULL));

    // Initialization of the audio
    InitAudio();

    int isOnGameplay = 0;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetriste");
    SetExitKey(KEY_NULL); // Pressing ESC doesn't close the window
    PlayMusicStream(theme);
    SetTargetFPS(60);


    // Textures (background images) loading to memory
    Texture2D title = LoadTexture("assets/title.png");
    Texture2D main = LoadTexture("assets/main.png");
    Texture2D pause = LoadTexture("assets/pause.png");
    Texture2D win = LoadTexture("assets/win.png");
    Texture2D loss = LoadTexture("assets/loss.png");

    Screen currentScreen = TITLE_SCREEN;

    // Main game loop (executed each tick)
    while (!WindowShouldClose()) {

        if(currentMusic != NULL) {
            UpdateMusicStream(*currentMusic);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case TITLE_SCREEN:
                DrawTexture(title, 0, 0, WHITE);
                UpdateTitleScreen();
                break;
            case MAIN_SCREEN:
                DrawTexture(main, 0, 0, WHITE);
                UpdateGameplayScreen();
                break;
            case PAUSE_SCREEN:
                DrawTexture(pause, 0, 0, WHITE);
                UpdatePauseScreen();
                break;
            case WIN_SCREEN:
                DrawTexture(win, 0, 0, WHITE);
                UpdateWinScreen();
                break;
            case LOSS_SCREEN:
                DrawTexture(loss, 0, 0, WHITE);
                UpdateLossScreen();
                break;
        }

        EndDrawing();

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
