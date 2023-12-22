#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../tetriste.h"
#include "tetriste_cli.h"

void showDebug(Game* currentGame);
Piece* debugGetNextShape(Piece* piece);
Piece* debugGetNextColor(Piece* piece);

void startCLI() {

    // Initialization of the random number generator
    srand(time(NULL));
    Game *currentGame;

    int continueGame = 1;
    Piece **nextPieces = (Piece **)malloc(5 * sizeof(Piece *));

    int keepNextPieces;
    int combo = 0;

    printf("Do you want to load a game (y/n) ? ");
    char loadChoice;
    scanf(" %c", &loadChoice);
    printf("\n");
    if(loadChoice == 'y') {
        char name[21] = "";
        printf("Name of the save file (max 20): ");
        scanf("%s", name);
        currentGame = loadGame(nextPieces, name);
        if(currentGame == NULL) {
            printf("Impossible to load the game. Exiting...\n");
            free(nextPieces);
            return;
        }
    } else {
        currentGame = initGame();
        for (int i = 0; i < 5; i++) {
            nextPieces[i] = generatePiece();
        }
    }

    while (continueGame) {

        Piece *current = nextPieces[4];

        keepNextPieces = 1; // By default, we keep nextPieces as is for the next execution of the loop (shifting by color/shape, quit or wrong action)

        printf("%s\033[0;0H\033[2J", "\033[0m");

        displayGameInfo(currentGame, nextPieces, combo);
        showDebug(currentGame);
        displayMainMenu();

        printf("Your choice: ");
        char choice;
        scanf(" %c", &choice); // Found on internet: to solve an infinite loop, space before %c to make it work (scanf will take the \n from the previous input, and the space tells it not to)
        printf("\n");

        switch (choice) {
            case 'j':
                leftInsert(currentGame, current);
                keepNextPieces = 0;
                break;
            case 'k':
                rightInsert(currentGame, current);
                keepNextPieces = 0;
                break;
            case 'c':
                displayColorMenu();
                char colorChoice;
                scanf(" %c", &colorChoice);
                printf("\n");

                switch (colorChoice) {
                    case 'b':
                        shiftByColor(currentGame, 1);
                        break;
                    case 'y':
                        shiftByColor(currentGame, 2);
                        break;
                    case 'r':
                        shiftByColor(currentGame, 3);
                        break;
                    case 'g':
                        shiftByColor(currentGame, 4);
                        break;
                    default: // '0' or invalid choice
                        break;
                }
                break;
            case 's':
                displayShapeMenu();
                char shapeChoice;
                scanf(" %c", &shapeChoice);
                printf("\n");

                switch (shapeChoice) {
                    case 's':
                        shiftByShape(currentGame, 1);
                        break;
                    case 'd':
                        shiftByShape(currentGame, 2);
                        break;
                    case 'c':
                        shiftByShape(currentGame, 3);
                        break;
                    case 't':
                        shiftByShape(currentGame, 4);
                        break;
                    default: // '0' or invalid choice
                        break;
                }
                break;
            case 'q':
                continueGame = 0;

                printf("Do you want to save your progression (y/n) ? ");
                char saveChoice;
                scanf(" %c", &saveChoice);
                if (saveChoice == 'y') {
                    char name[21] = "";
                    printf("Name of the save (max of 20): ");
                    scanf("%s", name);
                    saveGame(currentGame, nextPieces, name);
                }

                break;
            default:
                // Useless to say that the choice is invalid because the next execution of the loop will clear the terminal
                break;
        }


        // If our action was an insertion, a piece from nextPieces was used, so we need to generate a new one
        if (!keepNextPieces) {
            for (int i = 4; i > 0; i--) {
                nextPieces[i] = nextPieces[i - 1];
            }
            nextPieces[0] = generatePiece();
        }

        combo = updateBoard(currentGame);
        if (combo == -1) {
            printf("YOU WIN !\n");
            continueGame = 0;
        }
    }

    // Free memory
    for (int i = 0; i < 5; i++) {
        freePiece(nextPieces[i]);
    }
    free(nextPieces);

    freeGame(currentGame);
}

void displayGameInfo(Game *currentGame, Piece **nextPieces, int combo) {

    printf("------   TETRISTE   ------\n");

    if(combo == 1){
        printf("Current score : %d (+3)\n", currentGame->score);
    } else if (combo > 1){
        printf("Current score : %d (COMBO! +%d)\n", currentGame->score, (int) pow(3, combo));
    } else {
        printf("Current score : %d\n", currentGame->score);
    }
   printf("Next pieces: ");

    for (int i = 0; i < 5; i++) {
        printf("%s ", nextPieces[i]->displayStr);
    }
    printf(" \033[31m<-- Next element\033[0m\n");

    Piece *currentPiece = currentGame->head;
    for (int i = 0; i < currentGame->piecesCount; i++) {
        printf("%s ", currentPiece->displayStr);
        currentPiece = currentPiece->next;
    }

    printf("\n\n");
}

void displayMainMenu() {
    printf("What do you want to do?\n");
    printf("j. Insert on the left\n");
    printf("k. Insert on the right\n");
    printf("c. Shift by color\n");
    printf("s. Shift by shape\n");
    printf("q. Quit\n");

}

void displayColorMenu() {
    printf("Which color do you want to shift?\n");
    printf("b. Blue\n");
    printf("y. Yellow\n");
    printf("r. Red\n");
    printf("g. Green\n");
    printf("0. Back\n");
}

void displayShapeMenu() {
    printf("Which shape do you want to shift?\n");
    printf("s. Square\n");
    printf("d. Diamond\n");
    printf("c. Circle\n");
    printf("t. Triangle\n");
    printf("0. Back\n");
}

/* DEBUG : Display all the pieces adresses, and, with tabulations, the adresses of the pieces they point to for colorNext and shapeNext and the prevs */
void showDebug(Game* currentGame) {
    printf("\n");

    printf("Disp\t");
    Piece* currentPiece = currentGame->head;
    for (int i = 0; i < currentGame->piecesCount; i++) {
        printf("%s           \t", currentPiece->displayStr);
        currentPiece = currentPiece->next;
    }
    printf("\n");
    printf("Address\t");
    currentPiece = currentGame->head;
    for(int i = 0; i < currentGame->piecesCount; i++) {
        printf("%p\t", currentPiece);
        currentPiece = currentPiece->next;
    }
    printf("\n\n");



    printf("ColorP\t");
    currentPiece = currentGame->head;
    for(int i = 0; i < currentGame->piecesCount; i++) {

        Piece* colorPrev = currentPiece->next;

        while(debugGetNextColor(colorPrev) != currentPiece) {
            colorPrev = colorPrev->next;
        }

        if(currentPiece->colorPrev != colorPrev) {
            printf("\033[31m");
        }
        
        printf("%p\033[0m\t", currentPiece->colorPrev);
        currentPiece = currentPiece->next;
    }
    printf("\n");
    
    

    printf("ColorN\t");
    currentPiece = currentGame->head;
    for(int i = 0; i < currentGame->piecesCount; i++) {
        if(currentPiece->colorNext != debugGetNextColor(currentPiece)) {
            printf("\033[31m");
        }

        printf("%p\033[0m\t", currentPiece->colorNext);
        currentPiece = currentPiece->next;
    }
    printf("\n");
    
    
    
    printf("ShapeP\t");
    currentPiece = currentGame->head;
    for(int i = 0; i < currentGame->piecesCount; i++) {

        Piece* shapePrev = currentPiece->next;

        while(debugGetNextShape(shapePrev) != currentPiece) {
            shapePrev = shapePrev->next;
        }

        if(currentPiece->shapePrev != shapePrev) {
            printf("\033[31m");
        }
        
        printf("%p\033[0m\t", currentPiece->shapePrev);
        currentPiece = currentPiece->next;
    }
    printf("\n");

    
    printf("ShapeN\t");
    currentPiece = currentGame->head;
    for(int i = 0; i < currentGame->piecesCount; i++) {

        if(currentPiece->shapeNext != debugGetNextShape(currentPiece)) {
            printf("\033[31m");
        }

        printf("%p\033[0m\t", currentPiece->shapeNext);
        currentPiece = currentPiece->next;
    }
    printf("\n\n");
}

Piece* debugGetNextColor(Piece* piece) {
    Piece* colorNext = piece->next;
    while(colorNext->color != piece->color) {
        colorNext = colorNext->next;
    }
    return colorNext;
}

Piece* debugGetNextShape(Piece* piece) {
    Piece* shapeNext = piece->next;
    while(shapeNext->shape != piece->shape) {
        shapeNext = shapeNext->next;
    }
    return shapeNext;
}