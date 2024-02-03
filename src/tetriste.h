#ifndef TETRISTE_H
#define TETRISTE_H

// #define DEBUG

typedef enum {
    P_BLUE,
    P_YELLOW,
    P_RED,
    P_GREEN
} PColor;

typedef enum {
    P_SQUARE,
    P_DIAMOND,
    P_CIRCLE,
    P_TRIANGLE
} PShape;

typedef struct Piece Piece;
struct Piece {
    PColor color;                 // The piece's color
    PShape shape;                 // The piece's shape

    Piece* next;                 // Circular linked list for pieces
    Piece* shapePrev;            // Double linked list for shapes
    Piece* shapeNext;
    Piece* colorPrev;            // Double linked list for colors
    Piece* colorNext;

    char* displayStr;            // How the piece must be displayed in the terminal
};

typedef struct {
    Piece* head;
    int score;
    int piecesCount;
} Game;

Game* initGame();
// Pieces
Piece* generatePiece();
char* getDisplayStr(PColor color, PShape shape);
int getPieceSequenceSize(Game *game, Piece *piece);
// Game actions
void leftInsert(Game* game, Piece* toInsert);
void rightInsert(Game* game, Piece* toInsert);
void shiftByColor(Game* game, PColor color);
void shiftByShape(Game* game, PShape shape);
// Logic
void updateShapes(Piece* piece);
void updateColors(Piece* piece);
int updateBoard(Game* game, int isByShift);
Piece* getTail(Game* game);
// Files
void saveGame(Game* game, Piece** nextPieces, char* name);
Game* loadGame(Piece** nextPieces, char* name);
// Memory
void freePiece(Piece* piece);
void freeGame(Game* game);

#endif // TETRISTE_H
