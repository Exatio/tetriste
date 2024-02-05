#ifndef TETRISTE_GUI_H
#define TETRISTE_GUI_H

extern Game* current_game;
extern Piece** next_pieces;

typedef enum {
    TITLE_SCREEN,
    MAIN_SCREEN,
    PAUSE_SCREEN,
    WIN_SCREEN,
    LOSS_SCREEN,
    SAVE_SCREEN,
    LOAD_SCREEN,
    END_SCREEN
} Screen;

void startGUI();
void switchScreen(Screen screen);

#endif //TETRISTE_GUI_H
