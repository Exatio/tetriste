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

Texture2D square;
Texture2D circle;
Texture2D diamond;
Texture2D plus;
Texture2D star;
Texture2D triangle;

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

    square = LoadTexture("assets/square.png");
    circle = LoadTexture("assets/circle.png");
    diamond = LoadTexture("assets/diamond.png");
    plus = LoadTexture("assets/plus.png");
    star = LoadTexture("assets/star.png");
    triangle = LoadTexture("assets/triangle.png");

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

    // Free memory
    for (int i = 0; i < 5; i++) {
        if(next_pieces[i] != NULL) {
            freePiece(next_pieces[i]);
        }
    }

    free(next_pieces);

    if(current_game != NULL) {
        freeGame(current_game);
    }

    // Unloading the textures
    UnloadTexture(title);
    UnloadTexture(main);
    UnloadTexture(pause);
    UnloadTexture(win);
    UnloadTexture(loss);
    UnloadTexture(input);

    UnloadTexture(square);
    UnloadTexture(circle);
    UnloadTexture(diamond);
    UnloadTexture(plus);
    UnloadTexture(star);
    UnloadTexture(triangle);

    CloseAudio();
    CloseWindow();
}

void switchScreen(Screen screen) {
    currentScreen = screen;
}
