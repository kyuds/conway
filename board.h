#ifndef CONWAY_BOARD
#define CONWAY_BOARD

typedef struct {
    int* board;
    int width;
    int height;
} board_t;

board_t * create_board(const int width, const int height);
board_t * board_from_file(const char* filename);
void step_board(board_t* board);
int get_board(board_t* board, const int x, const int y);
void set_board(board_t* board, const int x, const int y, const int value);
void free_board(board_t* board);

void debug_print(board_t* board);

#endif
