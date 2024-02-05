#include <stdlib.h>
#include "raylib.h"
#include "screens.h"
#include "../tetriste_gui.h"
#include "../../tetriste.h"

int easyButtonState = 0;
Rectangle easyButtonBounds = {462, 278, 293, 67};

int mediumButtonState = 0;
Rectangle mediumButtonBounds = {462, 378, 293, 67};

int hardButtonState = 0;
Rectangle hardButtonBounds = {462, 478, 293, 67};

void StartGame(int pieceCount, int shapeCount) {
    current_game = initGame(pieceCount, shapeCount);
    next_pieces = (Piece **)malloc(5 * sizeof(Piece *));
    for (int i = 0; i < 5; i++) {
        next_pieces[i] = generatePiece(current_game->colorCount, current_game->shapeCount);
    }

    switchScreen(MAIN_SCREEN);
}

void UpdateDifficultyScreen(Vector2 mousePoint) {

    // Easy Button
    if(CheckCollisionPointRec(mousePoint, easyButtonBounds)) {

        DrawRectangle(easyButtonBounds.x, easyButtonBounds.y, easyButtonBounds.width, easyButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) easyButtonState = 2;
        else easyButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            StartGame(4, 4);
        }

    } else {
        easyButtonState = 0;
    }

    // Medium Button
    if(CheckCollisionPointRec(mousePoint, mediumButtonBounds)) {

        DrawRectangle(mediumButtonBounds.x, mediumButtonBounds.y, mediumButtonBounds.width, mediumButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) mediumButtonState = 2;
        else mediumButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            StartGame(5, 5);
        }

    } else {
        mediumButtonState = 0;
    }

    // Hard Button
    if(CheckCollisionPointRec(mousePoint, hardButtonBounds)) {

        DrawRectangle(hardButtonBounds.x, hardButtonBounds.y, hardButtonBounds.width, hardButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) hardButtonState = 2;
        else hardButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            StartGame(6, 6);
        }

    } else {
        hardButtonState = 0;
    }

}