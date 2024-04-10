#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include <bits/stdc++.h>
using namespace std;

struct Sprite
{
    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]);
    void tick();
    const SDL_Rect* getCurrentClip() const;
};

struct Character
{
    Sprite backView, frontView, leftView, rightView, standStill;
};

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

    void renderBackground(const ScrollingBackground &background);

    void renderSprite(int x, int y, const Sprite& sprite);

    void present();

    SDL_Texture* loadTexture(const char *filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    Mix_Music *loadMusic(const char* path);

    Mix_Chunk* loadSound(const char* path);

    void playMusic(Mix_Music *gMusic);

    void playSound(Mix_Chunk* gChunk);

    void quit();
};


#endif // _GRAPHICS__H
