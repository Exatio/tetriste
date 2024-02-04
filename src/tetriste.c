#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tetriste.h"


// Initialize a new game and adds the first piece
Game* initGame(int colorCount, int shapeCount) {
    Piece* newPiece = generatePiece(colorCount, shapeCount);
    newPiece->next = newPiece;
    newPiece->shapePrev = newPiece;
    newPiece->shapeNext = newPiece;
    newPiece->colorPrev = newPiece;
    newPiece->colorNext = newPiece;



    Game* newGame = (Game*)malloc(sizeof(Game));
    newGame->head = newPiece;
    newGame->score = 0;
    newGame->piecesCount = 1;
    newGame->colorCount = colorCount;
    newGame->shapeCount = shapeCount;
    return newGame;
}

// Generate a new piece with random color and shape
Piece* generatePiece(int colorCount, int shapeCount) {
    PColor color = rand() % colorCount;
    PShape shape = rand() % shapeCount;

    Piece* newPiece = (Piece*) malloc(sizeof(Piece));
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

// Returns the string displayed in terminal for a given color/shape
char* getDisplayStr(PColor color, PShape shape) {

    char* shapes[] = {"■", "◊", "●", "▲", "★", "✚"};
    char* colors[] = {"\033[34m", "\033[33m", "\033[31m", "\033[32m", "\033[35m", "\033[37m"};
    char* resetColor = "\033[0m";

    char* displayStr = (char*)malloc(15);
    displayStr[0] = '\0';

    // Found snprintf on internet as a great alternative to multiple strcat
    snprintf(displayStr, 15, "%s%s%s", colors[color], shapes[shape], resetColor);

    return displayStr;
}

// Inserts a piece on the left side of the board
void leftInsert(Game* game, Piece* toInsert) {
    rightInsert(game, toInsert);
    game->head = toInsert;
}

// Inserts a piece on the right side of the board
void rightInsert(Game* game, Piece* toInsert) {
    Piece* tail = getTail(game);

    tail->next = toInsert;
    toInsert->next = game->head;

    updateShapes(toInsert);
    updateColors(toInsert);
    game->piecesCount++;
}

// Shifts all pieces of a specified color to the left
void shiftByColor(Game* game, PColor color) {
    Piece *firstColor = game->head;
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
    Piece *lastColor = firstColor->colorPrev;


    // Circularly shift the colors by swapping shapes and displayStr by pairs
    if (firstColor != lastColor) {

        Piece *current = firstColor;
        while (current != lastColor) {
            int tmp = current->shape;
            current->shape = current->colorNext->shape;
            current->colorNext->shape = tmp;

            char *tmp2 = current->displayStr;
            current->displayStr = current->colorNext->displayStr;
            current->colorNext->displayStr = tmp2;

            current = current->colorNext;
        }

        Piece *heads[6] = {NULL};
        Piece *tails[6] = {NULL};

        current = game->head;
        do {
            int i = current->shape;
            if(heads[i] == NULL) {
                heads[i] = current;
                tails[i] = current;
            } else {
                tails[i]->shapeNext = current;
                current->shapePrev = tails[i];
                tails[i] = current;
            }
            current = current->next;
        } while (current != game->head);

        for(int i = 0 ; i < game->shapeCount ; i++) {
            if(heads[i] != NULL) {
                tails[i]->shapeNext = heads[i];
                heads[i]->shapePrev = tails[i];
            }
        }

    }
}
// Shifts all pieces of a specified shape to the left
void shiftByShape(Game* game, PShape shape) {
    Piece *firstShape = game->head;
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
    Piece *lastShape = firstShape->shapePrev;


    // Circularly shift the shapes by swapping color and displayStr by pairs
    if (firstShape != lastShape) {

        Piece *current = firstShape;
        while (current != lastShape) {
            int tmp = current->color;
            current->color = current->shapeNext->color;
            current->shapeNext->color = tmp;
            char *tmp2 = current->displayStr;
            current->displayStr = current->shapeNext->displayStr;
            current->shapeNext->displayStr = tmp2;

            current = current->shapeNext;
        }

        Piece *heads[6] = {NULL};
        Piece *tails[6] = {NULL};

        current = game->head;
        do {
            int i = current->color;
            if(heads[i] == NULL) {
                heads[i] = current;
                tails[i] = current;
            } else {
                tails[i]->colorNext = current;
                current->colorPrev = tails[i];
                tails[i] = current;
            }
            current = current->next;
        } while (current != game->head);

        for(int i = 0 ; i < game->colorCount ; i++) {
            if(heads[i] != NULL) {
                tails[i]->colorNext = heads[i];
                heads[i]->colorPrev = tails[i];
            }
        }

    }
}


// Updates the doubly circular linked list of shapes for a given piece
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

// Updates the doubly circular linked list of colors for a given piece
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

// Returns the length of the longest sequence of shape or color starting from piece
int getPieceSequenceSize(Game *game, Piece *piece) {
    int colorSequence = 1, shapeSequence = 1;
    Piece *current = piece->next;
    // It has been decided that the maximum length of a sequence is 5
    for (int i = 1; i < 5; i++) {
        if (current == game->head)
            break;
        if (colorSequence == i && current->color == piece->color) colorSequence++;
        if (shapeSequence == i && current->shape == piece->shape) shapeSequence++;
        current = current->next;
    }
    if (colorSequence > shapeSequence) return colorSequence;
    return shapeSequence;
}

/* Checks if some pieces need to be deleted (3 pieces or more of the same color/shape)
 * Returns: O if nothing changed -1 if the game is won the score added otherwise
*/
int updateBoard(Game *game, int isByShift) {

    int initialScore = game->score;
    // No need to check if there is less than 3 pieces
    if (game->piecesCount < 3) {
        return 0;
    }

    Piece *currentPiece = game->head;
    Piece *beforeCurrent = NULL;
    int combinationSize;
    Piece *toDelete[5];
    Piece *tail = getTail(game);

    int combo = 0;
    while (currentPiece->next != game->head) {

        combinationSize = getPieceSequenceSize(game, currentPiece);
#ifdef DEBUG
        printf("Combination found : %d\n", combinationSize);
#endif
        // If there are at least 3 pieces of the same color or shape, delete them
        if (combinationSize >= 3) {

            // If there are combos, the score will augment exponentially (3^x or 4^x etc)
            combo++;
            game->score += pow(combinationSize, combo) * (isByShift ? 2 : 1);

            // If all the pieces on the board are deleted, it's a win, the game will end so everything will be correctly freed
            if (game->piecesCount == combinationSize) {
                return -1;
            }

            game->piecesCount -= combinationSize;

            // Updating the linking for the shapes and colors
            for (int i = 0; i < combinationSize; i++) {
                currentPiece->shapePrev->shapeNext = currentPiece->shapeNext;
                currentPiece->shapeNext->shapePrev = currentPiece->shapePrev;
                currentPiece->colorPrev->colorNext = currentPiece->colorNext;
                currentPiece->colorNext->colorPrev = currentPiece->colorPrev;
                toDelete[i] = currentPiece;
                currentPiece = currentPiece->next;
            }

            // Removing the pieces from the board
            for (int i = 0; i < combinationSize; i++) {
                freePiece(toDelete[i]);
            }

            // Removing the pieces from the single circular linked list
            if (beforeCurrent == NULL) { // In this case the head go removed
                game->head = currentPiece;
                tail->next = game->head;
            } else {
                beforeCurrent->next = currentPiece;
                if (currentPiece == game->head) tail = beforeCurrent; // Checking whether or not the tail got removed
            }

            // We need to check again since the beginning to see if a new combinaison was created from this deletion
            beforeCurrent = NULL;
            currentPiece = game->head;
        } else {
            beforeCurrent = currentPiece;
            currentPiece = currentPiece->next;
        }
    }

    return game->score - initialScore;
}

// Returns the last displayed piece "tail"
Piece* getTail(Game* game) {
    Piece* tail = game->head;
    while (tail->next != game->head) {
        tail = tail->next;
    }
    return tail;
}

void saveGame(Game *game, Piece **nextPieces, char *name){
    char* magic = "TETRISTE";
    FILE *file = fopen(strcat(name, ".txt"), "w");
    fprintf(file, "%s\n", magic); // the magic string is used to check if the file is a valid save
    fprintf(file, "%d %d\n", game->colorCount, game->shapeCount);
    fprintf(file, "%d\n%d\n", game->score, game->piecesCount);

    for(int i = 0 ; i < 5 ; i++){
        fprintf(file, "%d %d\n", nextPieces[i]->color, nextPieces[i]->shape);
    }

    Piece *toSave = game->head;
    for(int i = 0 ; i < game->piecesCount ; i++){
        fprintf(file, "%d %d\n", toSave->color, toSave->shape);
        toSave = toSave->next;
    }

    fclose(file);
}

// Returns the game if it was successfully loaded, NULL otherwise (file doesn't exist or corrupted/invalid)
Game* loadGame(Piece** nextPieces, char* name) {

    char magic[] = "        ";
    strcat(name, ".txt");
    FILE* file = fopen(name, "r");;

    if (file == NULL) {
        printf("This save doesn't exist!\n");
        return NULL;
    }

    fgets(magic, 9, file);

    if (strcmp(magic, "TETRISTE") != 0) {
        printf("This save is invalid or corrupted!\n");
        fclose(file);
        return NULL;
    }

    Game* newGame = (Game*)malloc(sizeof(Game));
    fscanf(file, "%d %d\n", &newGame->colorCount, &newGame->shapeCount);
    fscanf(file, "%d\n%d\n", &newGame->score, &newGame->piecesCount);
#ifdef DEBUG
    printf("Score: %d\nPieces count: %d\n", newGame->score, newGame->piecesCount);
#endif
    for (int i = 0; i < 5; i++) {
        int color, shape;
        fscanf(file, "%d %d\n", &color, &shape);
        nextPieces[i] = (Piece*)malloc(sizeof(Piece));
        nextPieces[i]->color = color;
        nextPieces[i]->shape = shape;
        nextPieces[i]->displayStr = getDisplayStr(color, shape);
#ifdef DEBUG
        printf("Next piece %d: %s\n", i, nextPieces[i]->displayStr);
#endif
    }

    Piece* current = NULL;
    for (int i = 0; i < newGame->piecesCount; i++) {
        int color, shape;
        fscanf(file, "%d %d\n", &color, &shape);
        Piece* newPiece = (Piece*)malloc(sizeof(Piece));
        newPiece->color = color;
        newPiece->shape = shape;
        newPiece->displayStr = getDisplayStr(color, shape);
#ifdef DEBUG
        printf("Piece %d: %s\n", i, newPiece->displayStr);
#endif
        if (i == 0) {
            newGame->head = newPiece;
            newPiece->next = newPiece;
            newPiece->shapePrev = newPiece;
            newPiece->shapeNext = newPiece;
            newPiece->colorPrev = newPiece;
            newPiece->colorNext = newPiece;
            current = newPiece;
        } else {
            rightInsert(newGame, newPiece);
            newGame->piecesCount--; // Because rightInsert increments it
            current = newPiece;
        }
    }

    current->next = newGame->head;
    fclose(file);
    return newGame;
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
