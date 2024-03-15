#include "logic.h"
#include <bits/stdc++.h>
using namespace std;
void Tictactoe::init()
{
    for (int i=0; i<BOARD_HEIGHT; i++){
        for (int j=0; j<BOARD_WIDTH; j++){
            board[i][j]=BLANK_CELL;
        }
    }
}

void Tictactoe::move(int row, int col)
{
    if (row>=0 && row<BOARD_HEIGHT && col>=0 && row<BOARD_WIDTH && board[row][col]==BLANK_CELL){
        board[row][col]=movePlayed;
        if (movePlayed==X_CELL) movePlayed=O_CELL;
        else movePlayed=X_CELL;
    }
}
