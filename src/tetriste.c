#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tetriste.h"

// Initialize a new game and adding the first piece
Game* initGame() {
    Piece* newPiece = generatePiece();
    newPiece->next = newPiece;
    newPiece->shapePrev = newPiece;
    newPiece->shapeNext = newPiece;
    newPiece->colorPrev = newPiece;
    newPiece->colorNext = newPiece;

    Game* newGame = (Game*)malloc(sizeof(Game));
    newGame->head = newPiece;
    newGame->score = 0;
    newGame->piecesCount = 1;

    return newGame;
}

// Generate a new piece with a random color and shape
Piece* generatePiece() {
    int color = rand() % 4 + 1;
    int shape = rand() % 4 + 1;

    Piece* newPiece = (Piece*)malloc(sizeof(Piece));
    newPiece->color = color;
    newPiece->shape = shape;

    newPiece->next = NULL;
    newPiece->shapePrev = NULL;
    newPiece->shapeNext = NULL;
    newPiece->colorPrev = NULL;
    newPiece->colorNext = NULL;

    newPiece->displayStr = getDisplayStr(color, shape);

    return newPiece;
}

// Get the string displayed for a given color/shape in the terminal
char* getDisplayStr(int color, int shape) {
    char* colors[] = {"\033[34m", "\033[33m", "\033[31m", "\033[32m"};
    char* shapes[] = {"■", "◊", "●", "▲"}; // {"C", "L", "R", "T"};
    char* resetColor = "\033[0m";

    char* displayStr = (char*)malloc(15);
    displayStr[0] = '\0';

    // Found snprintf on internet as a great alternative to multiple strcat
    snprintf(displayStr, 15, "%s%s%s", colors[color - 1], shapes[shape - 1], resetColor);

    return displayStr;
}

// Get the Xth piece after the given piece in the linked list
Piece* getXPiecesAfter(Piece* piece, int n) {
    Piece* current = piece;
    for (int i = 0; i < n; i++) {
        current = current->next;
    }
    return current;
}

// Insert a piece on the left side of the board
void leftInsert(Game* game, Piece* toInsert) {
    rightInsert(game, toInsert);
    game->head = toInsert;
}

// Insert a piece on the right side of the board
void rightInsert(Game* game, Piece* toInsert) {
    Piece* tail = getTail(game);

    tail->next = toInsert;
    toInsert->next = game->head;

    updateShapes(toInsert);
    updateColors(toInsert);
    game->piecesCount++;
}

// Shift all pieces of a specified color to the left  TODO: make it work
void shiftByColor(Game* game, int color) {
    Piece* firstColor = game->head;
    while (firstColor->next != game->head) {
        if (firstColor->color == color) {
            break;
        }
        firstColor = firstColor->next;
    }

    if (firstColor->color != color) {
        printf("No piece of this color is present on the board!\n");
        return;
    }

    Piece* lastColor = firstColor->colorPrev;

    if (firstColor != lastColor) {
        Piece* current = firstColor;
        do {
            // Swap shape and displayStr
            int tmp = current->shape;
            current->shape = current->colorNext->shape;
            current->colorNext->shape = tmp;
            char* tmp2 = current->displayStr;
            current->displayStr = current->colorNext->displayStr;
            current->colorNext->displayStr = tmp2;

            // Update linking for shapes
            Piece* tmp3 = current->next;
            while (tmp3->shape != current->shape && tmp3 != current->colorNext) {
                tmp3 = tmp3->next;
            }
            if (tmp3 != current->colorNext && tmp3 != current->colorNext->shapeNext) {
                current->shapePrev = tmp3->shapePrev;
                current->shapePrev->shapeNext = current;
                current->shapeNext = tmp3;
                tmp3->shapePrev = current;
                current->colorNext->shapeNext->shapePrev = current->colorNext->shapePrev;
                current->colorNext->shapePrev->shapeNext = current->colorNext->shapeNext;
            }

            current = current->colorNext;
        } while (current != lastColor);
        updateShapes(lastColor);
    }
}

// Shift all pieces of a specified shape to the left  TODO: make it work
void shiftByShape(Game* game, int shape) {
    Piece* firstShape = game->head;
    while (firstShape->next != game->head) {
        if (firstShape->shape == shape) {
            break;
        }
        firstShape = firstShape->next;
    }

    if (firstShape->shape != shape) {
        printf("No piece of this shape is present on the board!\n");
        return;
    }

    Piece* lastShape = firstShape->shapePrev;

    if (firstShape != lastShape) {
        Piece* current = firstShape;
        do {
            // Swap color and displayStr
            int tmp = current->color;
            current->color = current->shapeNext->color;
            current->shapeNext->color = tmp;
            char* tmp2 = current->displayStr;
            current->displayStr = current->shapeNext->displayStr;
            current->shapeNext->displayStr = tmp2;

            // Update linking for colors
            Piece* tmp3 = current->next;
            while (tmp3->color != current->color && tmp3 != current->shapeNext) {
                tmp3 = tmp3->next;
            }
            if (tmp3 != current->shapeNext && tmp3 != current->shapeNext->colorNext) {
                current->colorPrev = tmp3->colorPrev;
                current->colorPrev->colorNext = current;
                current->colorNext = tmp3;
                tmp3->colorPrev = current;
                current->shapeNext->colorNext->colorPrev = current->shapeNext->colorPrev;
                current->shapeNext->colorPrev->colorNext = current->shapeNext->colorNext;
            }

            current = current->shapeNext;
        } while (current != lastShape);
        updateShapes(lastShape);
    }
}

// Update the doubly circular linked list of shapes for a given piece
void updateShapes(Piece* piece) {
    Piece* current = piece->next;
    while (current->shape != piece->shape) {
        current = current->next;
    }

    if (current == piece) {
        piece->shapePrev = piece;
        piece->shapeNext = piece;
    } else {
        piece->shapePrev = current->shapePrev;
        piece->shapePrev->shapeNext = piece;
        piece->shapeNext = current;
        piece->shapeNext->shapePrev = piece;
    }
}

// Update the doubly circular linked list of colors for a given piece
void updateColors(Piece* piece) {
    Piece* current = piece->next;
    while (current->color != piece->color) {
        current = current->next;
    }

    if (current == piece) {
        piece->colorPrev = piece;
        piece->colorNext = piece;
    } else {
        piece->colorPrev = current->colorPrev;
        piece->colorPrev->colorNext = piece;
        piece->colorNext = current;
        piece->colorNext->colorPrev = piece;
    }

}

/* Check if some pieces need to be deleted (3 pieces of the same color/shape)
   Returns one if the game is won, otherwise it will return 0 */
int updateBoard(Game* game) {

    // No need to check if there is less than 3 pieces
    if(game->piecesCount < 3){
        return 0;
    }

    Piece* currentPiece = getTail(game);

    int combo = 3;
    // For all the combinaisons of 3 pieces starting from the head to the tail
    while (getXPiecesAfter(currentPiece, 3) != game->head) {

        Piece* nextPiece = currentPiece->next;
        Piece* nextNextPiece = nextPiece->next;
        Piece* nextNextNextPiece = nextNextPiece->next;

        // If the 3 pieces are of the same color or shape, delete them
        // TODO: Ask & check if we need to delete all the pieces of the same color/shape or only the 3 first
        if ((nextPiece->color == nextNextPiece->color && nextPiece->color == nextNextNextPiece->color) ||
            (nextPiece->shape == nextNextPiece->shape && nextPiece->shape == nextNextNextPiece->shape)) {

            // If there are exactly 3 pieces on the board, its a win, the game will end so everything will be correctly freed
            if (game->piecesCount == 3) {
                return 1;
            }

            // Removing the pieces from the single circular linked list
            currentPiece->next = nextNextNextPiece->next;

            if (nextPiece == game->head) {
                game->head = nextNextNextPiece->next;
            }

            // TODO: Optimize the update of the shapes and colors for all the pieces related to the deleted ones
            // TODO: it doesnt work lol
            Piece* tmp = game->head;
            do {
                updateShapes(tmp);
                updateColors(tmp);
                tmp = tmp->next;
            } while (tmp != game->head);

            // They aren't used anymore by any other pieces thanks to the above update
            freePiece(nextPiece);
            freePiece(nextNextPiece);
            freePiece(nextNextNextPiece);

            game->piecesCount -= 3;
            game->score += combo;
            combo = combo*combo; // If there are combos, the score will augment exponentially (3^x)
            currentPiece = getTail(game); // We need to check again since the beginning to see if a new combinaison was created from this deletion
            // TODO: Optimize this by only checking from two pieces before the current one or from the tail if we are in the 3 first
            // TODO: Show combos + score to user
        } else {
            currentPiece = currentPiece->next; // Only increment if no deletion was done
        }

    }

    return 0;
}

// Returns the last displayed piece "tail"
Piece* getTail(Game* game) {
    Piece* tail = game->head;
    while (tail->next != game->head) {
        tail = tail->next;
    }
    return tail;
}

// Free the memory allocated to a piece
void freePiece(Piece* piece) {
    free(piece->displayStr);
    free(piece);
}

// Free the memory allocated to all the pieces of a game, and the game itself
void freeGame(Game* game) {
    Piece* current = game->head;
    for (int i = 0; i < game->piecesCount; i++) {
        Piece* next = current->next;
        freePiece(current);
        current = next;
    }
    free(game);
}
