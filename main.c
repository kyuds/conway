#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "board.h"
#include "tui.h"

#define DELAY 150000 // 0.15 seconds

int main(int argc, char** argv) {
    // read input file name
    if (argc != 2) {
        printf("Please input a filename.\n");
        return 1;
    }

    // make board out of filename
    board_t * board = board_from_file(argv[1]);

    // init ncurses tui
    WINDOW * win = init_tui(board->width, board->height);

    // generate world until termination
    while (1) {
        draw(win, board);
        step_board(board);
        usleep(DELAY);
    }

    // for completeness sake
    free_board(board);
    end_tui();

    return 0;
}
