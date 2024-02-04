#include "../tetriste.h"

#ifndef TETRISTE_CLI_H
#define TETRISTE_CLI_H

// Main
void startCLI();
// Utilities
void askUpdateRankings(Game* currentGame);
// Game menus
void displayGameInfo(Game *currentGame, Piece **nextPieces, int scoreAdded);
void displayMainMenu();
void displayColorMenu(int purple, int white);
void displayShapeMenu(int star, int plus);
// Debug
void showDebug(Game* currentGame);
Piece* debugGetNextShape(Piece* piece);
Piece* debugGetNextColor(Piece* piece);


#endif //TETRISTE_CLI_H