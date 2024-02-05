#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"
#include "screens.h"
#include "../tetriste_gui.h"

#include "../../tetriste.h"
#include "rlgl.h"
#include "../audio/audio.h"

int pauseMenuButtonState = 0;
Rectangle pauseMenuButtonBounds = {32, 32, 205, 32};

int changeTrackButtonState = 0;
Rectangle changeTrackButtonBounds = {1020, 25, 205, 32};

int stopMusicButtonState = 0;
Rectangle stopMusicButtonBounds = {1020, 75, 205, 32};

int nextUpdateBoard = 0;
int isByShift = 1;

void DrawPiece(int posX, int posY, PColor color, PShape shape) {

    Color drawColor;
    switch(color) {
        case P_BLUE:
            drawColor = BLUE;
            break;
        case P_RED:
            drawColor = RED;
            break;
        case P_YELLOW:
            drawColor = YELLOW;
            break;
        case P_GREEN:
            drawColor = GREEN;
            break;
        case P_PURPLE:
            drawColor = PURPLE;
            break;
        case P_WHITE:
            drawColor = WHITE;
            break;
        default:
            drawColor = DARKGRAY;
            break;
    }

    Texture2D texture;
    switch(shape) {
        case P_SQUARE:
            texture = square;
            break;
        case P_CIRCLE:
            texture = circle;
            break;
        case P_DIAMOND:
            texture = diamond;
            break;
        case P_PLUS:
            texture = plus;
            break;
        case P_STAR:
            texture = star;
            break;
        case P_TRIANGLE:
            texture = triangle;
            break;
        default:
            texture = square;
            printf("Shouldnt happen\n");
            break;
    }

    DrawTexture(texture, posX, posY, drawColor);
}


void KeybindsCheck() {

    nextUpdateBoard = 1;
    isByShift = 1;

    // Insertions
    if(IsKeyPressed(KEY_LEFT)) {
        leftInsert(current_game, next_pieces[4]);
        for (int i = 4; i > 0; i--) {
            next_pieces[i] = next_pieces[i - 1];
        }
        next_pieces[0] = generatePiece(4, 4);
        isByShift = 0;
    } else if(IsKeyPressed(KEY_RIGHT)) {
        rightInsert(current_game, next_pieces[4]);
        for (int i = 4; i > 0; i--) {
            next_pieces[i] = next_pieces[i - 1];
        }
        next_pieces[0] = generatePiece(4, 4);
        isByShift = 0;
    }

    // Color shifts
    else if(IsKeyPressed(KEY_R)) {
        shiftByColor(current_game, P_RED);
    } else if(IsKeyPressed(KEY_B)) {
        shiftByColor(current_game, P_BLUE);
    } else if(IsKeyPressed(KEY_Y)) {
        shiftByColor(current_game, P_YELLOW);
    } else if(IsKeyPressed(KEY_G)) {
        shiftByColor(current_game, P_GREEN);
    } else if(IsKeyPressed(KEY_P)) {
        shiftByColor(current_game, P_PURPLE);
    } else if(IsKeyPressed(KEY_W)) {
        shiftByColor(current_game, P_WHITE);
    }

    // Shape shifts
    else if(IsKeyPressed(KEY_S)) {
        shiftByShape(current_game, P_SQUARE);
    } else if(IsKeyPressed(KEY_D)) {
        shiftByShape(current_game, P_DIAMOND);
    } else if(IsKeyPressed(KEY_C)) {
        shiftByShape(current_game, P_CIRCLE);
    } else if(IsKeyPressed(KEY_T)) {
        shiftByShape(current_game, P_TRIANGLE);
    } else if(IsKeyPressed(KEY_A)) {
        shiftByShape(current_game, P_STAR);
    } else if(IsKeyPressed(KEY_M)) {
        shiftByShape(current_game, P_PLUS);
    } else {
        nextUpdateBoard = 0;
    }



}

int scoreAdded = 0;
int savedScore;
void UpdateGameplayScreen(Vector2 mousePoint) {


    /* Draw the score */
    if(scoreAdded == 0) {
        DrawText(TextFormat("%d", current_game->score), 220, 140, 50, BLUE);
    } else if(scoreAdded <= 5) {
        DrawText(TextFormat("%d (+%d)", current_game->score, scoreAdded), 220, 140, 50, BLUE);
    } else {
        DrawText(TextFormat("%d (Incredible! +%d)", current_game->score, scoreAdded), 220, 140, 50, BLUE);
    }

    ButtonsCheck(mousePoint);
    KeybindsCheck();

    /* Draw the next pieces */
    for(int i = 0; i < 5; i++) {
        DrawPiece(220 + 83 * i, 225, next_pieces[i]->color, next_pieces[i]->shape);
    }

    /* Draw the game board */
    Piece* current = current_game->head;
    for(int i = 0; i < current_game->piecesCount; i++) {
        DrawPiece(15 + 75*i + 8*i, 350, current->color, current->shape);
        current = current->next;
    }

    if(nextUpdateBoard) {
        scoreAdded = updateBoard(current_game, isByShift);
        if(scoreAdded > 0) PlaySound(successSound);
        if(current_game->piecesCount >= 15) {
            savedScore = current_game->score;
            scoreAdded = 0;

            for (int i = 0; i < 5; i++) {
                freePiece(next_pieces[i]);
            }

            free(next_pieces);
            freeGame(current_game);

            next_pieces = NULL;
            current_game = NULL;

            switchScreen(LOSS_SCREEN);
        }
        if(scoreAdded == -1) {
            savedScore = current_game->score;
            scoreAdded = 0;

            for (int i = 0; i < 5; i++) {
                freePiece(next_pieces[i]);
            }

            free(next_pieces);
            freeGame(current_game);

            next_pieces = NULL;
            current_game = NULL;

            switchScreen(WIN_SCREEN);

        }
        nextUpdateBoard = 0;
    }

}

void ButtonsCheck(Vector2 mousePoint) {
    // Pause Menu Button
    if(CheckCollisionPointRec(mousePoint, pauseMenuButtonBounds)) {

        DrawRectangle(pauseMenuButtonBounds.x, pauseMenuButtonBounds.y, pauseMenuButtonBounds.width, pauseMenuButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) pauseMenuButtonState = 2;
        else pauseMenuButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) switchScreen(PAUSE_SCREEN);

    } else {
        pauseMenuButtonState = 0;
    }

    if(IsKeyPressed(KEY_ESCAPE)) {
        switchScreen(PAUSE_SCREEN);
    }


    // Change Track Button
    if(CheckCollisionPointRec(mousePoint, changeTrackButtonBounds)) {



        DrawRectangle(changeTrackButtonBounds.x, changeTrackButtonBounds.y, changeTrackButtonBounds.width, changeTrackButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) changeTrackButtonState = 2;
        else changeTrackButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) SwitchMusic();

    } else {
        changeTrackButtonState = 0;
    }

    // Stop Music Button
    if(CheckCollisionPointRec(mousePoint, stopMusicButtonBounds)) {

        DrawRectangle(stopMusicButtonBounds.x, stopMusicButtonBounds.y, stopMusicButtonBounds.width, stopMusicButtonBounds.height, Fade(WHITE, 0.3f));
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) stopMusicButtonState = 2;
        else stopMusicButtonState = 1;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) StopMusic();

    } else {
        stopMusicButtonState = 0;
    }
}
