#include <stdlib.h>
#include "raylib.h"
#include "screens.h"
#include "../tetriste_gui.h"
#include "../../tetriste.h"

int yesButtonState = 0;
Rectangle yesButtonBounds = {462, 278, 293, 67};

int noButtonState = 0;
Rectangle noButtonBounds = {462, 378, 293, 67};

void UpdateRankingScreen(Vector2 mousePoint) {

    // Yes Button
    if(CheckCollisionPointRec(mousePoint, yesButtonBounds)) {

        DrawRectangle(yesButtonBounds.x, yesButtonBounds.y, yesButtonBounds.width, yesButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) yesButtonState = 2;
        else yesButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            switchScreen(SAVE_SCREEN);
        }

    } else {
        yesButtonState = 0;
    }
    // No Button
    if(CheckCollisionPointRec(mousePoint, noButtonBounds)) {

        DrawRectangle(noButtonBounds.x, noButtonBounds.y, noButtonBounds.width, noButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) noButtonState = 2;
        else noButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(nextScreen);

    } else {
        noButtonState = 0;
    }

}