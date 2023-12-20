#include "../tetriste.h"

#ifndef TETRISTE_CLI_H
#define TETRISTE_CLI_H

void displayGameInfo(Game *currentGame, Piece **nextPieces, int combo);
void displayMainMenu();
void displayColorMenu();
void displayShapeMenu();
void startCLI();

#endif //TETRISTE_CLI_H