#ifndef TETRISTE_H
#define TETRISTE_H

// #define DEBUG

typedef enum {
    P_BLUE,
    P_YELLOW,
    P_RED,
    P_GREEN,
    P_PURPLE,
    P_WHITE
} PColor;

typedef enum {
    P_SQUARE,
    P_DIAMOND,
    P_CIRCLE,
    P_TRIANGLE,
    P_STAR,
    P_PLUS
} PShape;

typedef struct Piece Piece;
struct Piece {
    PColor color;                 // The piece's color
    PShape shape;                 // The piece's shape

    Piece* next;                  // Circular linked list for pieces
    Piece* shapePrev;             // Double circular linked list for shapes
    Piece* shapeNext;
    Piece* colorPrev;             // Double circular linked list for colors
    Piece* colorNext;

    char* displayStr;             // How the piece must be displayed in the terminal
};

typedef struct {
    Piece* head;            // The first piece displayed from the left in the game
    int score;
    int piecesCount;
    int colorCount;         // The (difficulty) number of colors in the game
    int shapeCount;         // The (difficulty) number of shapes in the game
} Game;

Game* initGame(int colorCount, int shapeCount);
// Pieces
Piece* generatePiece(int colorCount, int shapeCount);
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
void updateRankings(int score, char *name);
// Memory
void freePiece(Piece* piece);
void freeGame(Game* game);

#endif // TETRISTE_H
