#include "audio.h"
#include "raylib.h"
#include <stdio.h>

Music *currentMusic;
Music theme;
Music theme2;
Music themeRemix;
Sound successSound;

void InitAudio() {
    InitAudioDevice();

    theme = LoadMusicStream("assets/theme.mp3");
    theme2 = LoadMusicStream("assets/theme-2.mp3");
    themeRemix = LoadMusicStream("assets/theme-trap-remix.mp3");
    successSound = LoadSound("assets/success.mp3");

    SetSoundVolume(successSound, 0.8f);
    SetMusicVolume(theme, 0.3f);
    SetMusicVolume(theme2, 0.3f);
    SetMusicVolume(themeRemix, 0.3f);

    currentMusic = &theme;
}

void SwitchMusic() {
    if(currentMusic == NULL) {
        currentMusic = &theme;
    } else if(currentMusic == &theme) {
        currentMusic = &theme2;
    } else if(currentMusic == &theme2) {
        currentMusic = &themeRemix;
    } else {
        currentMusic = &theme;
    }
    PlayMusicStream(*currentMusic);
}

void StopMusic() {
    if(currentMusic != NULL) {
        StopMusicStream(*currentMusic);
        currentMusic = NULL;
    }
}

void CloseAudio() {
    UnloadMusicStream(theme);
    UnloadMusicStream(theme2);
    UnloadMusicStream(themeRemix);
    UnloadSound(successSound);
    CloseAudioDevice();
}
