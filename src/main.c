#include <stdio.h>
#include <string.h>
#include "cli/tetriste_cli.h"

void startGUI() {
    printf("GUI not implemented yet!\n");
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Must have 1 argument!\n");
        printf("Usage: ./%s <cli | gui>\n", argv[0]);
        return 1;
    } else if(strcmp(argv[1], "cli") == 0) {
        startCLI();
    } else if(strcmp(argv[1], "gui") == 0) {
        startGUI();
    } else {
        printf("Wrong argument!\n");
        printf("Usage: %s <cli | gui>\n", argv[0]);
        return 1;
    }
    return 0;
}

