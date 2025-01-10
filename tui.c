#include "tui.h"

#include <ncurses.h>

WINDOW * init_tui(const int width, const int height) {
    initscr();
    WINDOW * win = newwin(height + 2, width * 2 + 3, 1, 1);
    curs_set(0);
    refresh();
    return win;
}

void end_tui() {
    endwin();
}

void draw(WINDOW * win, board_t * board) {
    // initialize row
    wclear(win);
    box(win, 0, 0);
    char row[board->width * 2];
    for (int x = 0; x < board->width * 2 - 1; x++) 
        row[x] = ' ';
    row[board->width * 2 - 1] = '\0';

    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            row[x * 2] = get_board(board, x, y) == ALIVE ? 'X' : ' ';
        }
        mvwprintw(win, y + 1, 2, "%s", row);
    }
    wrefresh(win);
}
