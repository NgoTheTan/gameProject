#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

struct ScrollingBackground
{
    SDL_Texture *texture;
    int scrollingOffset=0;
    int width, height;
    void setTexture(SDL_Texture *_texture);
    void moveForward();
    void goBack();
};
struct Graphics
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    void logErrorAndExit(const char* msg, const char* error);

    void initSDL();

    void init();

    void prepareScene();

    void createBackground(SDL_Texture* background);

    void render(const ScrollingBackground &background);

    void present();

    SDL_Texture* loadTexture(const char *filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    void quit();
};
#endif // _GRAPHICS__H
