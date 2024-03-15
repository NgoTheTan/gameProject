#ifndef _LOGIC__H
#define _LOGIC__H

#define BOARD_WIDTH 30
#define BOARD_HEIGHT 20
#define BLANK_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'

struct Tictactoe {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    char movePlayed=X_CELL;
    void init();
    void move(int row, int col);
};

#endif
