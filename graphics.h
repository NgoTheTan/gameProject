#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
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

struct Layer
{
    SDL_Texture *texture;
    int scrollingOffset=0;
    int width, height;
    void setTexture(SDL_Texture *_texture);
    void scroll(const int speed, const int accel);
};

struct ParallaxBackground
{
    Layer ground;
    Layer layer_1;
    Layer layer_2;
    Layer layer_3;
    Layer layer_4;
};

struct Graphics
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    void logErrorAndExit(const char* msg, const char* error);

    void initSDL();

    void init();

    void prepareScene();

    SDL_Texture* loadTexture(const char *filename);

    void renderTexture(SDL_Texture* texture, int x, int y);

    void initBackground(ParallaxBackground &background);

    void renderLayer(const Layer &layer);

    void renderBackground(ParallaxBackground &background, const int accel);

    void renderSprite(int x, int y, const Sprite& sprite);

    void renderUI(SDL_Texture* texture, int x, int y, int texX, int texY, int w, int h);

    void present();

    Mix_Music *loadMusic(const char* path);

    Mix_Chunk* loadSound(const char* path);

    void playMusic(Mix_Music *gMusic);

    void playSound(Mix_Chunk* gChunk);

    TTF_Font* loadFont(const char* path, int size);

    SDL_Texture* renderText(const string text, TTF_Font* font, SDL_Color textColor);

    void quit();
};

void destroyBackground(ParallaxBackground &background);
#endif // _GRAPHICS__H
