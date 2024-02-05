#include "raylib.h"
#include "screens.h"
#include "../tetriste_gui.h"

int restartButtonState = 0;
Rectangle restartButtonBounds = {335, 465, 266, 43};

int quitButtonState = 0;
Rectangle quitButtonBounds = {677, 465, 266, 43};

void UpdateWinLossScreen(Vector2 mousePoint) {

    // Retart Button
    if(CheckCollisionPointRec(mousePoint, restartButtonBounds)) {

        DrawRectangle(restartButtonBounds.x, restartButtonBounds.y, restartButtonBounds.width, restartButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) restartButtonState = 2;
        else restartButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(TITLE_SCREEN);

    } else {
        restartButtonState = 0;
    }

    // Quit Button
    if(CheckCollisionPointRec(mousePoint, quitButtonBounds)) {

        DrawRectangle(quitButtonBounds.x, quitButtonBounds.y, quitButtonBounds.width, quitButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) quitButtonState = 2;
        else quitButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(END_SCREEN);

    } else {
        quitButtonState = 0;
    }
}
