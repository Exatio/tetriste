#include <stdio.h>

#include "raylib.h"
#include "screens.h"
#include "../tetriste_gui.h"

int confirmButtonState = 0;
Rectangle confirmButtonBounds = {462, 458, 352, 51};

int inputBoxState = 0;
Rectangle inputBoxBounds = {376, 291, 520, 82};
int letterCount = 0;
int mouseOnInputBox = 0;
char name[21] = "\0";

void UpdateSaveScreen(Vector2 mousePoint) {

    if(IsKeyPressed(KEY_ESCAPE)) {
        switchScreen(PAUSE_SCREEN);
    }

    // Input Box
    InputBoxCollisionCheck(mousePoint);

    // Confirm Button
    if(CheckCollisionPointRec(mousePoint, confirmButtonBounds)) {

        DrawRectangle(confirmButtonBounds.x, confirmButtonBounds.y, confirmButtonBounds.width, confirmButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) confirmButtonState = 2;
        else confirmButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if(letterCount > 0) {
                saveGame(current_game, next_pieces, name);
                switchScreen(END_SCREEN);
            }
        }

    } else {
        confirmButtonState = 0;
    }


}

int drawError = 0;

void UpdateLoadScreen(Vector2 mousePoint) {

    if(IsKeyPressed(KEY_ESCAPE)) {
        switchScreen(TITLE_SCREEN);
    }

    // Input Box
    InputBoxCollisionCheck(mousePoint);
    // Confirm Button
    if(CheckCollisionPointRec(mousePoint, confirmButtonBounds)) {

        DrawRectangle(confirmButtonBounds.x, confirmButtonBounds.y, confirmButtonBounds.width, confirmButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) confirmButtonState = 2;
        else confirmButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if(letterCount > 0) {
                current_game = loadGame(next_pieces, name);
                if(current_game != NULL) {
                    switchScreen(MAIN_SCREEN);
                } else {
                    drawError = 1;
                }
            }
        }

    } else {
        confirmButtonState = 0;
    }

    if(drawError) {
        DrawText("No such save file exists", 100, 100, 40, RED);
    }
}

void InputBoxCollisionCheck(Vector2 mousePoint) {

    if (CheckCollisionPointRec(mousePoint, inputBoxBounds)) mouseOnInputBox = 1;
    else mouseOnInputBox = 0;

    if (mouseOnInputBox)
    {
        int key = GetCharPressed();

        while (key > 0)
        {
            // only letters and numbers (no spaces) are allowed
            if (letterCount < 20 && ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122)))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }

    }
    if(letterCount > 0) {
        DrawText(name, (int) inputBoxBounds.x + 15, (int) inputBoxBounds.y + 10, 40, RAYWHITE);
    }

}

/*
void UpdateTitleScreen(Vector2 mousePoint) {
    // Check if the mouse clicks on the buttons

    // Start Button
    if(CheckCollisionPointRec(mousePoint, startButtonBounds)) {

        DrawRectangle(startButtonBounds.x, startButtonBounds.y, startButtonBounds.width, startButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) startButtonState = 2;
        else startButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(MAIN_SCREEN);

    } else {
        startButtonState = 0;
    }

    // Load Button
    if(CheckCollisionPointRec(mousePoint, loadButtonBounds)) {

        DrawRectangle(loadButtonBounds.x, loadButtonBounds.y, loadButtonBounds.width, loadButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) loadButtonState = 2;
        else loadButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(WIN_SCREEN);

    } else {
        loadButtonState = 0;
    }
}
*/