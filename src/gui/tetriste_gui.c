#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "screens/screens.h"
#include "audio/audio.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

void startGUI() {

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Initialisation de la fenêtre
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetriste - Tavalidé");

    // Initialisation de l'audio
    InitAudio();


    int isOnGameplay = 0;

    PlayMusicStream(theme);
    SetTargetFPS(60);
    InitTitleScreen();

    // Boucle principale du jeu (tick)
    while (!WindowShouldClose()) {

        if(currentMusic != NULL) {
            UpdateMusicStream(*currentMusic);
        }

        if(!isOnGameplay) {
            UpdateDrawTitleScreen();
            if(FinishTitleScreen()) {
                UnloadTitleScreen();
                isOnGameplay = 1;
                InitGameplayScreen();
            }
        } else {
            UpdateDrawGameplayScreen();
        }

        if(IsKeyPressed(KEY_ONE)) {
            if (currentMusic != &theme) {
                SwitchMusic(&theme);
            }
        } else if(IsKeyPressed(KEY_TWO)) {
            if(currentMusic != &theme2) {
                SwitchMusic(&theme2);
            }
        } else if(IsKeyPressed(KEY_THREE)) {
            if(currentMusic != &themeRemix) {
                SwitchMusic(&themeRemix);
            }
        } else if(IsKeyPressed(KEY_FOUR)) {
            StopMusicStream(*currentMusic);
            currentMusic = NULL;
        }


    }

    if(isOnGameplay) {
        UnloadFinishGameplayScreen();
    } else {
        UnloadTitleScreen();
    }

    CloseAudio();
    CloseWindow();
}
