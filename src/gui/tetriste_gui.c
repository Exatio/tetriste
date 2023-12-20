#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "screens/screens.h"
#include "audio/audio.h"

void startGUI() {
    // Initialisation des constantes
    const int screenWidth = 1200;
    const int screenHeight = 700;

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    InitWindow(screenWidth, screenHeight, "Tetriste - Tavalidé");     // Initialisation de la fenêtre
    InitAudio(); // Initialisation de l'audio, décrit dans audio.c


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