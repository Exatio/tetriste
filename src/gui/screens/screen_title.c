#include <stdlib.h>
#include "raylib.h"
#include "screens.h"
#include "../tetriste_gui.h"

int startButtonState = 0;
Rectangle startButtonBounds = {78, 305, 294, 70};

int loadButtonState = 0;
Rectangle loadButtonBounds = {78, 405, 294, 70};

void UpdateTitleScreen(Vector2 mousePoint) {
    // Check if the mouse clicks on the buttons

    // Start Button
    if(CheckCollisionPointRec(mousePoint, startButtonBounds)) {

        DrawRectangle(startButtonBounds.x, startButtonBounds.y, startButtonBounds.width, startButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) startButtonState = 2;
        else startButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            switchScreen(DIFFICULTY_SCREEN);
        }

    } else {
        startButtonState = 0;
    }

    // Load Button
    if(CheckCollisionPointRec(mousePoint, loadButtonBounds)) {

        DrawRectangle(loadButtonBounds.x, loadButtonBounds.y, loadButtonBounds.width, loadButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) loadButtonState = 2;
        else loadButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(LOAD_SCREEN);

    } else {
        loadButtonState = 0;
    }
}
