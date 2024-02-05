#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../tetriste.h"
#include "tetriste_cli.h"

void startCLI() {

    // Initialization of the random number generator
    srand(time(NULL));
    Game *currentGame;

    int continueGame = 1;
    Piece **nextPieces = (Piece **)malloc(5 * sizeof(Piece *));

    int keepNextPieces; // Is used to know if we have to generate a new piece (only if we did an insertion in the previous iteration)
    int scoreAdded = 0; // Is used to keep track of the score added by the last action and display it in the next iteration of the loop

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
        printf("Choose the difficulty of the game:\n");
        printf("1. Easy (4 colors, 4 shapes)\n");
        printf("2. Medium (5 colors, 5 shapes)\n");
        printf("3. Hard (6 colors, 6 shapes)\n");
        printf("4. Custom\n");
        printf("Your choice: ");
        int difficulty, colorCount, shapeCount;
        scanf("%d", &difficulty);
        printf("\n");

        switch (difficulty) {
            case 1:
                colorCount = 4;
                shapeCount = 4;
                break;
            case 2:
                colorCount = 5;
                shapeCount = 5;
                break;
            case 3:
                colorCount = 6;
                shapeCount = 6;
                break;
            case 4:
                do {
                    printf("Number of colors (4-6): ");
                    scanf("%d", &colorCount);
                    printf("Number of shapes (4-6): ");
                    scanf("%d", &shapeCount);
                    printf("\n");
                } while (colorCount < 4 || colorCount > 6 || shapeCount < 4 || shapeCount > 6);
                break;
            default:
                printf("Invalid choice. Exiting...\n");
                free(nextPieces);
                return;
        }

        currentGame = initGame(colorCount, shapeCount);
        for (int i = 0; i < 5; i++) {
            nextPieces[i] = generatePiece(currentGame->colorCount, currentGame->shapeCount);
        }
    }

    while (continueGame) {

         // By default, we keep nextPieces as is for the next execution of the loop (shifting by color/shape, quit or wrong action)
        keepNextPieces = 1;

        printf("%s\033[0;0H\033[2J", "\033[0m"); // Reset and Clear the terminal

        displayGameInfo(currentGame, nextPieces, scoreAdded);
#ifdef DEBUG
        showDebug(currentGame);
#endif
        displayMainMenu();

        printf("Your choice: ");
        char choice;
        scanf(" %c", &choice); // Found on internet: to solve an infinite loop, space before %c to make it work (scanf will take the \n from the previous input, and the space tells it not to)
        printf("\n");
        int isByShift = 1;           // Is used to know if the updateBoard function has to do a *2 multiplier if the action was a shift

        switch (choice) {
            case 'j':
                leftInsert(currentGame, nextPieces[4]);
                isByShift = keepNextPieces = 0;
                break;
            case 'k':
                rightInsert(currentGame, nextPieces[4]);
                isByShift = keepNextPieces = 0;
                break;
            case 'c':
                displayColorMenu(currentGame->colorCount > 4, currentGame->colorCount == 6);
                char colorChoice;
                scanf(" %c", &colorChoice);
                printf("\n");

                switch (colorChoice) {
                    case 'b':
                        shiftByColor(currentGame, 0);
                        break;
                    case 'y':
                        shiftByColor(currentGame, 1);
                        break;
                    case 'r':
                        shiftByColor(currentGame, 2);
                        break;
                    case 'g':
                        shiftByColor(currentGame, 3);
                        break;
                    case 'p':
                        if(currentGame->colorCount > 4) { // If the game has less than 5 colors, we can't shift by purple (because it doesn't exist)
                            shiftByColor(currentGame, 4);
                        } else {
                            isByShift = 0;
                        }
                        break;
                    case 'w':
                        if(currentGame->colorCount == 6) { // If the game has not 6 colors, we can't shift by white (because it doesn't exist)
                            shiftByColor(currentGame, 5);
                        } else {
                            isByShift = 0;
                        }
                        break;
                    default: // Invalid choice
                        isByShift = 0;
                        break;
                }
                break;
            case 's':
                displayShapeMenu(currentGame->shapeCount > 4, currentGame->shapeCount == 6);
                char shapeChoice;
                scanf(" %c", &shapeChoice);
                printf("\n");

                switch (shapeChoice) {
                    case 's':
                        shiftByShape(currentGame, 0);
                        break;
                    case 'd':
                        shiftByShape(currentGame, 1);
                        break;
                    case 'c':
                        shiftByShape(currentGame, 2);
                        break;
                    case 't':
                        shiftByShape(currentGame, 3);
                        break;
                    case 'a':
                        if(currentGame->shapeCount > 4) { // If the game has less than 5 shapes, we can't shift by star (because it doesn't exist)
                            shiftByShape(currentGame, 4);
                        } else {
                            isByShift = 0;
                        }
                        break;
                    case 'p':
                        if(currentGame->shapeCount == 6) { // If the game has not 6 shapes, we can't shift by plus (because it doesn't exist)
                            shiftByShape(currentGame, 5);
                        } else {
                            isByShift = 0;
                        }
                        break;
                    default: // '0' or invalid choice
                        isByShift = 0;
                        break;
                }
                break;
            case 'q':
                isByShift = continueGame = 0;

                printf("Do you want to save your progression (y/n) ? ");
                char saveChoice;
                scanf(" %c", &saveChoice);
                if (saveChoice == 'y') {
                    char name[21] = "";
                    printf("Name of the save (max of 20): ");
                    scanf("%s", name);
                    updateRankings(currentGame->score, name);
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
            nextPieces[0] = generatePiece(currentGame->colorCount, currentGame->shapeCount);
        }

        scoreAdded = updateBoard(currentGame, isByShift);
        if (scoreAdded == -1) {
            printf("YOU WIN !\nFinal score : %d\n", currentGame->score);
            askUpdateRankings(currentGame);
            continueGame = 0;
        }
        if (currentGame->piecesCount >= 15) {
            printf("YOU LOST !\nFinal score: %d!\n", currentGame->score);
            askUpdateRankings(currentGame);
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

void askUpdateRankings(Game* currentGame) {
    printf("Do you want to update the rankings (y/n) ? ");
    char updateChoice;
    scanf(" %c", &updateChoice);
    if (updateChoice == 'y') {
        char name[21] = "";
        printf("Name of the player (max of 20): ");
        scanf("%s", name);
        updateRankings(currentGame->score, name);
    }
}

void displayGameInfo(Game *currentGame, Piece **nextPieces, int scoreAdded) {

    printf("------   TETRISTE   ------\n");

    if(scoreAdded == 0) {
        printf("Current score : %d\n", currentGame->score);
    } else if(scoreAdded <= 5){ // Insertions
        printf("Current score : %d (+%d)\n", currentGame->score, scoreAdded);
    } else {                    // Combos and/or shifts
        printf("Current score : %d (Incredible! +%d)\n", currentGame->score, scoreAdded);
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

void displayColorMenu(int purple, int white) {
    printf("Which color do you want to shift?\n");
    printf("b. Blue\n");
    printf("y. Yellow\n");
    printf("r. Red\n");
    printf("g. Green\n");
    if(purple) {
        printf("p. Purple\n");
    }
    if(white) {
        printf("w. White\n");
    }
    printf("0. Back\n");
}

void displayShapeMenu(int star, int plus) {
    printf("Which shape do you want to shift?\n");
    printf("s. Square\n");
    printf("d. Diamond\n");
    printf("c. Circle\n");
    printf("t. Triangle\n");
    if(star) {
        printf("a. Star\n");
    }
    if(plus) {
        printf("p. Plus\n");
    }
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
