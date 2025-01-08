#include <stdio.h>

#include "board.h"
#include "tui.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Please input a filename.\n");
        return 1;
    }
    board_t * board = board_from_file(argv[1]);
    debug_print(board);
    printf("\n");

    for (int i = 0; i < 6; i++) {
        step_board(board);
        debug_print(board);
        printf("\n");
    }

    free_board(board);
    return 0;
}
