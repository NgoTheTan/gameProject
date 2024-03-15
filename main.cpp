#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void processClick(int x, int y, Tictactoe& game)
{
    if ((x%CELL_SIZE>=0 && x%CELL_SIZE<=3) || (x%CELL_SIZE>=27 && x%CELL_SIZE<=29) ||(y%CELL_SIZE>=0 && y%CELL_SIZE<=3) || (y%CELL_SIZE>=27 && y%CELL_SIZE<=29) ) return;
    int clickedCol=(y-BOARD_X)/CELL_SIZE;
    int clickedRow=(x-BOARD_Y)/CELL_SIZE;
    game.move(clickedCol, clickedRow);
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    Tictactoe game;
    game.init();
    graphics.render(game);
    int x,y;
    SDL_Event event;
    bool quit=false;
    while (!quit){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit=true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode==SDL_SCANCODE_R){
                    game.movePlayed=X_CELL;
                    game.init();
                    graphics.render(game);
                }
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button==SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&x, &y);
                    processClick(x,y,game);
                    graphics.render(game);
                }
                break;
        }
    }
    graphics.quit();

    return 0;
}
