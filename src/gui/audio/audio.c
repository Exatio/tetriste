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

    SetSoundVolume(successSound, 1.0f);
    SetMusicVolume(theme, 0.4f);
    SetMusicVolume(theme2, 0.4f);
    SetMusicVolume(themeRemix, 0.4f);

    currentMusic = &theme;
}

void SwitchMusic(Music *newMusic) {
    if(currentMusic != NULL) {
        StopMusicStream(*currentMusic);
    }
    currentMusic = newMusic;
    PlayMusicStream(*currentMusic);
}


void CloseAudio() {
    UnloadMusicStream(theme);
    UnloadMusicStream(theme2);
    UnloadMusicStream(themeRemix);
    UnloadSound(successSound);
    CloseAudioDevice();
}
