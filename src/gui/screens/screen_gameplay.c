#include <stdlib.h>
#include "raylib.h"
#include "../../tetriste.h"
#include "rlgl.h"
#include "../audio/audio.h"


static Texture2D background;
Game* current_game;
Piece** next_pieces;
int lost = 0;
int combo = 0;

void DrawPiece(int posX, int posY, int color, int shape) {

    Color drawColor = // light blue
            {0x04, 0x62, 0xD6, 0xFF};
    if(color == 2) {
        drawColor = YELLOW;
    } else if(color == 3) {
        drawColor = RED;
    } else if(color == 4) {
        drawColor = GREEN;
    }

    if(shape == 1) { // Carr
        DrawRectangle(posX, posY, 65, 65, drawColor);
    } else if(shape == 2) { // Losange
        Rectangle rect = {posX + 32.5, posY, 46, 46}; // sq(65^2 * 2) = 46
        DrawRectanglePro(rect, (Vector2){0, 0}, 45, drawColor);
    } else if(shape == 3) { // Rond
        DrawCircle(posX+32.5, posY+32.5, 32.5, drawColor);
    } else if(shape == 4) { // Triangle
        DrawTriangle(
                (Vector2){posX + 32.5, posY},
                (Vector2){posX, posY + 65},
                (Vector2){posX + 65, posY + 65},
                drawColor
        );
    }
}

void InitGameplayScreen(void) {
    current_game = initGame();
    next_pieces = (Piece**) malloc(sizeof(Piece*) * 5);
    for(int i = 0; i < 5; i++) {
        next_pieces[i] = generatePiece();
    }

    background = LoadTexture("assets/bg.png");
}

void UpdateDrawGameplayScreen(void) {
    DrawFPS(10, 10);

    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE);

    if(!lost && combo != -1) {

        if(combo == 0) {
            DrawText(TextFormat("%d", current_game->score), 200, 390, 50, BLUE);
        } else if(combo == 1) {
            DrawText(TextFormat("%d (+3)", current_game->score), 200, 390, 50, BLUE);
        } else {
            DrawText(TextFormat("%d (combo! +%d)", current_game->score, combo), 200, 390, 50, BLUE);
        }


        if (IsKeyPressed(KEY_LEFT)) {
            leftInsert(current_game, next_pieces[4]);

            for (int i = 4; i > 0; i--) {
                next_pieces[i] = next_pieces[i - 1];
            }
            next_pieces[0] = generatePiece();

            combo = updateBoard(current_game, 0);
            if(combo > 0) PlaySound(successSound);

            if(current_game->piecesCount >= 15) {
                lost = 1;
            }

        } else if (IsKeyPressed(KEY_RIGHT)) {
            rightInsert(current_game, next_pieces[4]);

            for (int i = 4; i > 0; i--) {
                next_pieces[i] = next_pieces[i - 1];
            }
            next_pieces[0] = generatePiece();

            combo = updateBoard(current_game, 0);
            if(combo > 0) PlaySound(successSound);

            if(current_game->piecesCount >= 15) {
                lost = 1;
            }

        } else if (IsKeyPressed(KEY_R)) { // rouge
            shiftByColor(current_game, 3);
        } else if (IsKeyPressed(KEY_B)) { // bleu
            shiftByColor(current_game, 1);
        } else if (IsKeyPressed(KEY_Y)) { // jaune
            shiftByColor(current_game, 2);
        } else if (IsKeyPressed(KEY_G)) { // vert
            shiftByColor(current_game, 4);
        } else if (IsKeyPressed(KEY_S)) { // carré
            shiftByShape(current_game, 1);
        } else if (IsKeyPressed(KEY_D)) { // losange
            shiftByShape(current_game, 2);
        } else if (IsKeyPressed(KEY_C)) { // rond
            shiftByShape(current_game, 3);
        } else if (IsKeyPressed(KEY_T)) { // triangle
            shiftByShape(current_game, 4);
        }


        for (int i = 0; i < 5; i++) {
            DrawPiece(200 + 80 * i, 450, next_pieces[i]->color,
                      next_pieces[i]->shape);
        }

        int piece_count = current_game->piecesCount;
        int sizeOfAllPieces = piece_count * 65 + (piece_count - 1) * 15;
        int startX = (GetScreenWidth() - sizeOfAllPieces) / 2;
        int i = 0;

        Piece *current = current_game->head;
        do {
            DrawPiece(startX + 80 * i, 550, current->color, current->shape);
            current = current->next;
            i++;
        } while (current != current_game->head);

    } else if(combo == -1) {
        DrawText(TextFormat("%d", current_game->score), 200, 390, 50, RED);
        DrawText("YOU WIN!", 200, 450, 50, RED);
    } else if(lost) {
        DrawText("YOU LOST!", 200, 460, 50, RED);
        DrawText(TextFormat("%d", current_game->score), 200, 390, 50, RED);
    }

    EndDrawing();
}

void UnloadFinishGameplayScreen(void) {
    for(int i = 0; i < 5; i++) {
        freePiece(next_pieces[i]);
    }
    free(next_pieces);
    freeGame(current_game);
    UnloadTexture(background);
}
