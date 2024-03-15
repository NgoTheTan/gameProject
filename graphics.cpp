#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
#include "graphics.h"

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0){
        logErrorAndExit("SDL_Init", SDL_GetError());
    }
    window=SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window==nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) logErrorAndExit("SDL_image error:", IMG_GetError());
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer==nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::init()
{
    Graphics::initSDL();
    background=Graphics::loadTexture("image//bikiniBottom.jpg");
    blank=Graphics::loadTexture("image//blank.png");
    cellX=Graphics::loadTexture("image//X.png");
    cellO=Graphics::loadTexture("image//O.png");
}

void Graphics::createBackground(SDL_Texture *background)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
}

void Graphics::present()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture *texture=IMG_LoadTexture(renderer, filename);
    if(texture==NULL) logErrorAndExit("Load texture %s", IMG_GetError());
    return texture;
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;
    dest.x=x; dest.y=y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::render(const Tictactoe& game)
{
    for (int i = 0; i < BOARD_HEIGHT; i++){
        for (int j = 0; j < BOARD_WIDTH; j++){
            int x=BOARD_X+j*CELL_SIZE;
            int y=BOARD_Y+i*CELL_SIZE;
            switch (game.board[i][j]) {
                case BLANK_CELL: Graphics::renderTexture(blank, x, y); break;
                case X_CELL: Graphics::renderTexture(cellX, x, y); break;
                case O_CELL: Graphics::renderTexture(cellO, x, y); break;
            };
        };
    }
    Graphics::present();
}

void Graphics::quit()
{
    SDL_DestroyTexture(blank); blank=nullptr;
    SDL_DestroyTexture(cellO); cellO=nullptr;
    SDL_DestroyTexture(cellX); cellX=nullptr;

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}