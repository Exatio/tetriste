#include "../../tetriste.h"
#ifndef SCREENS_H
#define SCREENS_H

// The title screen
void UpdateTitleScreen(Vector2 mousePoint);
// The game itself
void UpdateGameplayScreen(Vector2 mousePoint);
// Pause menu
void UpdatePauseScreen(Vector2 mousePoint);
// End of the game
void UpdateWinLossScreen(Vector2 mousePoint);
// Save & load input screens
void UpdateSaveScreen(Vector2 mousePoint);
void UpdateLoadScreen(Vector2 mousePoint);
void InputBoxCollisionCheck(Vector2 mousePoint);

#endif // SCREENS_H