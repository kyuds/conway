#ifndef CONWAY_TUI
#define CONWAY_TUI

#include <ncurses.h>
#include "board.h"

WINDOW * init_tui(const int width, const int height);
void end_tui();
void draw(WINDOW * win, board_t * board);

#endif
