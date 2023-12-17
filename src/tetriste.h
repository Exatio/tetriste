#ifndef TETRISTE_H
#define TETRISTE_H

typedef struct Piece {
    int color; // 1 = Blue, 2 = Yellow, 3 = Red, 4 = Green
    int shape; // 1 = Square, 2 = Diamond, 3 = Circle, 4 = Triangle

    struct Piece* next;
    struct Piece* shapePrev;
    struct Piece* shapeNext;
    struct Piece* colorPrev;
    struct Piece* colorNext;

    char* displayStr;
} Piece;

typedef struct Game {
    Piece* head;
    int score;
    int piecesCount;
} Game;

Game* initGame();
// Pieces
Piece* generatePiece();
char* getDisplayStr(int color, int shape);
Piece* getXPiecesAfter(Piece* piece, int n);
// Game actions
void leftInsert(Game* game, Piece* toInsert);
void rightInsert(Game* game, Piece* toInsert);
void shiftByColor(Game* game, int color);
void shiftByShape(Game* game, int shape);
// Logic
void updateShapes(Piece* piece);
void updateColors(Piece* piece);
int updateBoard(Game* game);
Piece* getTail(Game* game);
// Memory
void freePiece(Piece* piece);
void freeGame(Game* game);

#endif // TETRISTE_H
