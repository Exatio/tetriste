#ifndef AUDIO_H
#define AUDIO_H
#include "raylib.h"

extern Music *currentMusic;
extern Music theme;
extern Music theme2;
extern Music themeRemix;
extern Sound successSound;

void InitAudio();
void SwitchMusic(Music *newMusic);
void CloseAudio();

#endif // AUDIO_H
