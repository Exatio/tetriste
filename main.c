#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tetriste.h"

// -------------------------------------------
// Entrée du programme principal
// -------------------------------------------
int main() {
    srand(time(NULL));
    game* current_game = init_game();

    int continuer = 1;

    // On génère les 5 prochaines pièces
    piece** next_pieces = (piece**) malloc(sizeof(piece*) * 5);
    for(int i = 0; i < 5; i++) {
        next_pieces[i] = generatePiece();
    }

    while(continuer) {


        piece* current;

        // On génère une nouvelle pièce si on a inséré la dernière
        if(current_game->keepNextPieces) {
            current_game->keepNextPieces = 0;
        } else {
            for(int i = 4; i > 0; i--) {
                next_pieces[i] = next_pieces[i - 1];
            }
            next_pieces[0] = generatePiece();
        }

        current = next_pieces[4];




        // On se place en haut à gauche du terminal et on efface tout puis on réinitialise la couleur du terminal
        printf("%s\033[0;0H\033[2J", "\033[0m");

        if(updateBoard(current_game)) {
            printf("Félicitations, vous avez gagné !\n");
            break;
        }

        printf("------   TETRISTE   ------\nProchains : ");
        for(int i = 0; i < 5; i++) {
            printf("%s ", next_pieces[i]->display_str);
        }
        printf(" \033[31m<-- Prochain élément\033[0m\n");

        // On affiche le jeu
        piece* current_piece = current_game->head;
        for(int i = 0; i < current_game->pieces_count; i++) {
            printf("%s ", current_piece->display_str);
            current_piece = current_piece->next;
        }
        printf("\n\n");

        // On demande à l'utilisateur ce qu'il veut faire
        printf("Que voulez-vous faire ?\n");
        printf("1. Insérer à gauche\n");
        printf("2. Insérer à droite\n");
        printf("3. Décaler par couleur\n");
        printf("4. Décaler par forme\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");


        /* DEBUG
        printf("colorPrev : %s\n", current_game->head->colorPrev->display_str);
        printf("colorNext : %s\n", current_game->head->colorNext->display_str);
        printf("shapePrev : %s\n", current_game->head->shapePrev->display_str);
        printf("shapeNext : %s\n", current_game->head->shapeNext->display_str);
        */

        int choix = 0;
        scanf("%d", &choix);
        printf("\n");

        switch(choix) {
            case 1:
                leftInsert(current_game, current);
                break;
            case 2:
                rightInsert(current_game, current);
                break;
            case 3:
                current_game->keepNextPieces = 1;
                // On demande à l'utilisateur quelle couleur il veut décaler
                printf("Quelle couleur voulez-vous décaler ?\n");
                printf("1. Bleu\n");
                printf("2. Jaune\n");
                printf("3. Rouge\n");
                printf("4. Vert\n");
                printf("5. Retour\n");
                printf("Votre choix : ");
                scanf("%d", &choix);
                printf("\n");

                if(choix < 1 || choix > 4) {
                    printf("Choix invalide !\n");
                    break;
                }

                if(choix != 5) {
                    shiftByColor(current_game, choix);
                }

                break;
            case 4:
                current_game->keepNextPieces = 1;

                // On demande à l'utilisateur quelle forme il veut décaler
                printf("Quelle forme voulez-vous décaler ?\n");
                printf("1. Carré\n");
                printf("2. Losange\n");
                printf("3. Rond\n");
                printf("4. Triangle\n");
                printf("5. Retour\n");
                printf("Votre choix : ");
                scanf("%d", &choix);
                printf("\n");

                if(choix < 1 || choix > 4) {
                    printf("Choix invalide !\n");
                    break;
                }

                if(choix != 5) {
                    shiftByShape(current_game, choix);
                }

                break;
            case 5:
                continuer = 0;
                break;
            default:
                current_game->keepNextPieces = 1;
                printf("Choix invalide !\n"); // ne sera jamais affiché puisqu'on vide le terminal après
                // Vider le buffer d'entrée pour éviter les boucles infinies si l'utilisateur entre autre chose qu'un nombre
                while (getchar() != '\n');
                break;
        }

    }

    for(int i = 0; i < 5; i++) {
        free_piece(next_pieces[i]);
    }
    free(next_pieces);

    free_game(current_game);

    return 0;
}


