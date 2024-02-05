#include "raylib.h"
#include "screens.h"
#include "../tetriste_gui.h"
#include "../../tetriste.h"

int resumeMenuButtonState = 0;
Rectangle resumeMenuButtonBounds = {462, 216, 352, 48};

int saveButtonState = 0;
Rectangle saveButtonBounds = {462, 306, 352, 48};

int exitButtonState = 0;
Rectangle exitButtonBounds = {462, 404, 352, 48};

void UpdatePauseScreen(Vector2 mousePoint) {

    // Resume Menu Button
    if(CheckCollisionPointRec(mousePoint, resumeMenuButtonBounds)) {

        DrawRectangle(resumeMenuButtonBounds.x, resumeMenuButtonBounds.y, resumeMenuButtonBounds.width, resumeMenuButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) resumeMenuButtonState = 2;
        else resumeMenuButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(MAIN_SCREEN);

    } else {
        resumeMenuButtonState = 0;
    }

    // Save Button
    if(CheckCollisionPointRec(mousePoint, saveButtonBounds)) {

        DrawRectangle(saveButtonBounds.x, saveButtonBounds.y, saveButtonBounds.width, saveButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) saveButtonState = 2;
        else saveButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            nextScreen = END_SCREEN;
            switchScreen(SAVE_SCREEN);
        }


    } else {
        saveButtonState = 0;
    }

    // Exit Button
    if(CheckCollisionPointRec(mousePoint, exitButtonBounds)) {

        DrawRectangle(exitButtonBounds.x, exitButtonBounds.y, exitButtonBounds.width, exitButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) exitButtonState = 2;
        else exitButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(END_SCREEN);

    } else {
        exitButtonState = 0;
    }

}