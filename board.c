#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define DEAD 0
#define ALIVE 1
#define REVIVE -1
#define DIE 2
#define MAX_DIM 1024

board_t * create_board(const int width, const int height) {
    board_t * board = (board_t *) malloc(sizeof(board_t));
    board->width = width;
    board->height = height;
    board->board = (int*) calloc(sizeof(int) * width * height, 0);
    return board;
}

board_t * board_from_file(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    int width, height;
    if (fscanf(fp, "%d %d\n", &width, &height) != 2) {
        printf("Error reading dimensions.\n");
        fclose(fp);
        exit(1);
    }
    board_t * board = create_board(width, height);
    char line[MAX_DIM];
    for (int i = 0; i < height; i++) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            printf("Error reading line %d\n.", i);
            free(board);
            fclose(fp);
            exit(1);
        }
        for (int j = 0; j < width; j++) {
            set_board(board, i, j, line[j] == 'X' ? ALIVE : DEAD);
        }
    }
    return board;
}

void step_board(board_t* board) {
    int w = board->width;
    int h = board->height;

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            int alive = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue; // self
                    if (x + i < 0 || x + i >= w || y + j < 0 || y + j >= h) continue; // oob
                    if (get_board(board, x + i, y + j) > 0) alive++;
                }
            }
            if (get_board(board, x, y) == ALIVE) {
                if (alive < 2 || alive > 3) set_board(board, x, y, DIE);
            } else if (get_board(board, x, y) == DEAD) {
                if (alive == 3) set_board(board, x, y, REVIVE);
            }
        }
    }
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            int val = get_board(board, x, y);
            if (val == DIE) set_board(board, x, y, DEAD);
            else if (val == REVIVE) set_board(board, x, y, ALIVE);
        }
    }
}

int get_board(board_t* board, const int x, const int y) {
    return *(board->board + y * board->height + x);
}

void set_board(board_t* board, const int x, const int y, const int value) {
    *(board->board + y * board->height + x) = value;
}

void free_board(board_t* board) {
    free(board->board);
    free(board);
}

void debug_print(board_t* board) {
    for (int x = 0; x < board->width; x++) {
        for (int y = 0; y < board->height; y++) {
            printf(get_board(board, x, y) == ALIVE ? "X" : ".");
        }
        printf("\n");
    }
}
