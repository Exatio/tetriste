#include <stdio.h>
#include <string.h>
#include "src/cli/tetriste_cli.h"
#include "src/gui/tetriste_gui.h"

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Must have 1 argument!\n");
        printf("Usage: %s <cli | gui>\n", argv[0]);
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

