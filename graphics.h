#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
struct Graphics
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    void logErrorAndExit(const char* msg, const char* error);

    void initSDL();

    void init();

    void prepareScene();

    void createBackground(SDL_Texture* background);

    void present();

    SDL_Texture* loadTexture(const char *filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    void quit();
};
#endif // _GRAPHICS__H
