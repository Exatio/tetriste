#ifndef TETRISTE_H
#define TETRISTE_H

typedef struct piece {
    int color; // 1 = Bleu, 2 = Jaune, 3 = Rouge, 4 = Vert
    int shape; // 1 = Carré, 2 = Losange, 3 = Rond, 4 = Triangle

    struct piece* next;

    struct piece* shapePrev;
    struct piece* shapeNext;

    struct piece* colorPrev;
    struct piece* colorNext;

    char* display_str;
} piece;

typedef struct game {
    piece *head;
    int score;
    int pieces_count;
    int keepNextPieces;
} game;


game* init_game();
piece* generatePiece();

char* get_display_str(int color, int shape);



void leftInsert(game* current_game, piece* current);
void rightInsert(game* current_game, piece* current);
void updateShapes(piece* to_update);
void updateColors(piece* to_update);

void shiftByColor(game* current_game, int color);
void shiftByShape(game* current_game, int shape);

int updateBoard(game* current_game);

void free_piece(piece* piece);
void free_game(game* current_game);



#endif //TETRISTE_H
