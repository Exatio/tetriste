#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../tetriste.h"
#include "tetriste_cli.h"

void startCLI() {

    // Initialization of the random number generator
    srand(time(NULL));
    Game *currentGame = initGame();

    int continueGame = 1;
    Piece **nextPieces = (Piece **)malloc(5 * sizeof(Piece *));

    for (int i = 0; i < 5; i++) {
        nextPieces[i] = generatePiece();
    }

    int keepNextPieces;

    while (continueGame) {

        Piece *current = nextPieces[4];

        keepNextPieces = 1; // By default, we keep nextPieces as is for the next execution of the loop (shifting by color/shape, quit or wrong action)

        printf("%s\033[0;0H\033[2J", "\033[0m");

        displayGameInfo(currentGame, nextPieces);

        /* DEBUG
        printf("colorPrev : %s\n", current_game->head->colorPrev->display_str);
        printf("colorNext : %s\n", current_game->head->colorNext->display_str);
        printf("shapePrev : %s\n", current_game->head->shapePrev->display_str);
        printf("shapeNext : %s\n", current_game->head->shapeNext->display_str);
        */

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
                scanf("%c", &colorChoice);
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
                scanf("%c", &shapeChoice);
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

        if (updateBoard(currentGame)) {
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

void displayGameInfo(Game *currentGame, Piece **nextPieces) {
    printf("------   TETRISTE   ------\nCurrent score : %d\nNext pieces: ", currentGame->score);
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
