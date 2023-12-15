#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tetriste.h"

// Initialise le jeu
game* init_game() {

    piece* newPiece = generatePiece();
    newPiece->next = newPiece;

    game* newGame = (game*) malloc(sizeof(game));

    newGame->head = newPiece;
    newGame->score = 0;
    newGame->pieces_count = 1;
    newGame->keepNextPieces = 1;

    return newGame;
}

// Créer et initialise une pièce à partir de sa couleur et sa forme
piece* generatePiece() {

    // Randomisation de la couleur et de la forme de la pièce.
    const int color = rand() % 4 + 1;
    const int shape = rand() % 4 + 1;

    piece* newPiece = (piece*) malloc(sizeof(piece));

    newPiece->color = color;
    newPiece->shape = shape;

    newPiece->next = NULL;
    newPiece->shapePrev = newPiece;
    newPiece->shapeNext = newPiece;
    newPiece->colorPrev = newPiece;
    newPiece->colorNext = newPiece;

    newPiece->display_str = get_display_str(color, shape);

    return newPiece;
}

// Retourne la chaîne de caractères à afficher pour une pièce donnée
char* get_display_str(const int color, const int shape) {

    char* display_str = (char*) malloc(100);

    switch (color) {
        case 1:
            sprintf(display_str, "\033[34m");  // Bleu
            break;
        case 2:
            sprintf(display_str, "\033[33m");  // Jaune
            break;
        case 3:
            sprintf(display_str, "\033[31m");  // Rouge
            break;
        case 4:
            sprintf(display_str, "\033[32m");  // Vert
            break;
        default:
            sprintf(display_str, "\033[0m");   // Autre (n'arrivera jamais)
            break;
    }

    // Concatène l'initiale/la forme à la chaîne
    switch (shape) {
        case 1:
            strcat(display_str, "■");  // Carré
            break;
        case 2:
            strcat(display_str, "◊");  // Losange
            break;
        case 3:
            strcat(display_str, "●");  // Rond
            break;
        case 4:
            strcat(display_str, "▲");  // Triangle
            break;
        default:
            strcat(display_str, "");  // Autre (n'arrivera jamais)
            break;
    }

    strcat(display_str, "\033[0m"); // Pour reset la couleur après

    return display_str;
}

// Réarrangement de la liste doublement chaînée des formes
void updateShapes(piece* to_update) {

    piece *current = to_update->next;
    while (current != to_update) {
        if(current->shape == to_update->shape) {
            to_update->shapePrev = current->shapePrev;
            to_update->shapePrev->shapeNext = to_update;
            to_update->shapeNext = current;
            to_update->shapeNext->shapePrev = to_update;
            break;
        }
        current = current->next;
    }

}

// Réarrangement de la liste doublement chaînée des couleurs
void updateColors(piece* to_update) {

    piece *current = to_update->next;
    while (current != to_update) {
        if(current->color == to_update->color) {
            to_update->colorPrev = current->colorPrev;
            to_update->colorPrev->colorNext = to_update;
            to_update->colorNext = current;
            to_update->colorNext->colorPrev = to_update;
            break;
        }
        current = current->next;
    }
}

void leftInsert(game* current_game, piece* to_insert) {
    to_insert->next = current_game->head;

    piece* tail = current_game->head;
    while(tail->next != current_game->head) {
        tail = tail->next;
    }

    tail->next = to_insert;

    current_game->head = to_insert;

    updateShapes(to_insert);
    updateColors(to_insert);
    current_game->pieces_count++;
}

void rightInsert(game* current_game, piece* to_insert) {
    piece* tail = current_game->head;
    while(tail->next != current_game->head) {
        tail = tail->next;
    }

    tail->next = to_insert;
    to_insert->next = current_game->head;

    updateShapes(to_insert);
    updateColors(to_insert);
    current_game->pieces_count++;
}

void shiftByColor(game* current_game, int color) {

    piece* tail = current_game->head;
    while(tail->next != current_game->head) {
        tail = tail->next;
    }

    piece* firstColor = current_game->head;
    while(firstColor->next != current_game->head) {
        if(firstColor->color == color) {
            break;
        }
        firstColor = firstColor->next;
    }

    if(firstColor->color != color) {
        printf("Aucune pièce de cette couleur n'est présente sur le plateau !\n");
        return;
    }

    piece* lastColor = firstColor->colorPrev;

    if(firstColor != lastColor) {

        piece* current = firstColor;

        do {
            int tmp = current->shape;
            current->shape = current->colorNext->shape;
            current->colorNext->shape = tmp;

            free(current->display_str);
            free(current->colorNext->display_str);


            current->display_str = get_display_str(color, current->shape);
            current->colorNext->display_str = get_display_str(color, current->colorNext->shape);

            current = current->colorNext;
        } while(current != lastColor);

        // TODO: Optimiser cette partie
        current = current_game->head;
        do {
            updateShapes(current);
            current = current->next;
        } while(current != current_game->head);

    }
}

void shiftByShape(game* current_game, int shape) {

    piece* tail = current_game->head;
    while(tail->next != current_game->head) {
        tail = tail->next;
    }

    piece* firstShape = current_game->head;
    while(firstShape->next != current_game->head) {
        if(firstShape->shape == shape) {
            break;
        }
        firstShape = firstShape->next;
    }

    if(firstShape->shape != shape) {
        printf("Aucune pièce de cette forme n'est présente sur le plateau !\n");
        return;
    }

    piece* lastShape = firstShape->shapePrev;

    if(firstShape != lastShape) {

        piece* current = firstShape;

        do {

            int tmp = current->color;
            current->color = current->shapeNext->color;
            current->shapeNext->color = tmp;

            free(current->display_str);
            free(current->shapeNext->display_str);

            current->display_str = get_display_str(current->color, shape);
            current->shapeNext->display_str = get_display_str(current->shapeNext->color, shape);
            

            current = current->shapeNext;
        } while(current != lastShape);

        // TODO: Optimiser cette partie
        current = current_game->head;
        do {
            updateColors(current);
            current = current->next;
        } while(current != current_game->head);

    }

}

int updateBoard(game* current_game) {
    // Au moins 3 pièces sur le plateau
    if(current_game->head->next != current_game->head && current_game->head->next->next != current_game->head) {

        piece* tail = current_game->head;
        while(tail->next != current_game->head) {
            tail = tail->next;
        }

        piece* current_piece = tail;

        while(current_piece->next->next->next != current_game->head) {
            if(current_piece->next->color == current_piece->next->next->color && current_piece->next->color == current_piece->next->next->next->color
            ||current_piece->next->shape == current_piece->next->next->shape && current_piece->next->shape == current_piece->next->next->next->shape
                    ) {
                // S'il y a 3 exactement 3 pièces sur le plateau
                if(current_game->pieces_count == 3) {
                    return 1; // Fin de la partie
                }

                // On supprime les 3 pièces
                piece* to_delete = current_piece->next;
                piece* to_delete2 = current_piece->next->next;
                piece* to_delete3 = current_piece->next->next->next;

                if(to_delete == current_game->head) {
                    current_game->head = to_delete3->next;
                }

                // TODO: Optimiser cette partie
                piece* tmp = current_game->head;
                do {
                    updateShapes(tmp);
                    updateColors(tmp);
                    tmp = tmp->next;
                } while(tmp != current_game->head);

                current_piece->next = current_piece->next->next->next->next;
                free_piece(to_delete);
                free_piece(to_delete2);
                free_piece(to_delete3);

                current_game->pieces_count -= 3;
                current_game->score += 3;
                return 0;
            }


            current_piece = current_piece->next;
        }
    }


    return 0;

}


void free_piece(piece* piece) {
    free(piece->display_str);
    free(piece);
}

void free_game(game* current_game) {
    piece* current = current_game->head;
    for(int i = 0; i < current_game->pieces_count; i++) {
        piece* next = current->next;
        free_piece(current);
        current = next;
    }
    free(current_game);
}
