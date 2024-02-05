#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "screens/screens.h"
#include "audio/audio.h"
#include "tetriste_gui.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Game* current_game;
Piece** next_pieces;

Screen currentScreen = TITLE_SCREEN;

void startGUI(char* saveName) {

    // Initialization of the random number generator
    srand(time(NULL));

    // Game initialization
    next_pieces = (Piece **)malloc(5 * sizeof(Piece *));

    // Initialization of the audio
    InitAudio();
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
    Texture2D input = LoadTexture("assets/input.png");

    Vector2 mousePoint;

    int continueGame = 1;
    // Main game loop (executed each tick)
    while (!WindowShouldClose() && continueGame) {

        if(currentMusic != NULL) {
            UpdateMusicStream(*currentMusic);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        mousePoint = GetMousePosition();
        switch (currentScreen) {
            case TITLE_SCREEN:
                DrawTexture(title, 0, 0, WHITE);
                UpdateTitleScreen(mousePoint);
                break;
            case MAIN_SCREEN:
                DrawTexture(main, 0, 0, WHITE);
                UpdateGameplayScreen(mousePoint);
                break;
            case PAUSE_SCREEN:
                DrawTexture(pause, 0, 0, WHITE);
                UpdatePauseScreen(mousePoint);
                break;
            case WIN_SCREEN:
                DrawTexture(win, 0, 0, WHITE);
                UpdateWinLossScreen(mousePoint);
                break;
            case LOSS_SCREEN:
                DrawTexture(loss, 0, 0, WHITE);
                UpdateWinLossScreen(mousePoint);
                break;
            case SAVE_SCREEN:
                DrawTexture(input, 0, 0, WHITE);
                UpdateSaveScreen(mousePoint);
                break;
            case LOAD_SCREEN:
                DrawTexture(input, 0, 0, WHITE);
                UpdateLoadScreen(mousePoint);
                break;
            case END_SCREEN:
                continueGame = 0;
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
    UnloadTexture(input);

    CloseAudio();
    CloseWindow();
}

void switchScreen(Screen screen) {
    currentScreen = screen;
}
