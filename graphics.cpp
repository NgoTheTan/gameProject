#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
#include "graphics.h"
void Sprite::init(SDL_Texture* _texture, int frames, const int _clips [][4]){
    texture = _texture;
    SDL_Rect clip;
    for (int i = 0; i < frames; i++) {
        clip.x = _clips[i][0];
        clip.y = _clips[i][1];
        clip.w = _clips[i][2];
        clip.h = _clips[i][3];
        clips.push_back(clip);
    }
}
void Sprite::tick(){
    currentFrame = (currentFrame + 1) % clips.size();
}
const SDL_Rect* Sprite::getCurrentClip() const {
        return &(clips[currentFrame]);
}

void ScrollingBackground::setTexture(SDL_Texture *_texture)
{
    texture=_texture;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}
void ScrollingBackground::moveForward()
{
    scrollingOffset-=STEP;
    if (scrollingOffset<0) scrollingOffset=width;
}
void ScrollingBackground::goBack()
{
    scrollingOffset+=STEP;
    if (scrollingOffset>SCREEN_WIDTH) scrollingOffset=0;
}

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
    window=SDL_CreateWindow(WINDOW_TITLE, 0, 24,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window==nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) logErrorAndExit("SDL_image error:", IMG_GetError());
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer==nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void Graphics::init()
{
    Graphics::initSDL();
}

void Graphics::prepareScene()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
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

void Graphics::renderBackground(const ScrollingBackground& background)
{
    Graphics::renderTexture(background.texture, background.scrollingOffset, 0);
    Graphics::renderTexture(background.texture, background.scrollingOffset-background.width,0);
}
void Graphics::renderSprite(int x, int y, const Sprite& sprite){
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect renderQuad = {x, y, clip->w, clip->h};
    SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
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

Mix_Music* Graphics::loadMusic(const char* path)
{
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}

Mix_Chunk* Graphics::loadSound(const char* path) {
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
}

void Graphics::playMusic(Mix_Music *gMusic)
{
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else if( Mix_PausedMusic() == 1 ) {
        Mix_ResumeMusic();
    }
}

void Graphics::playSound(Mix_Chunk* gChunk)
{
    if (gChunk != nullptr) {
        Mix_PlayChannel( -1, gChunk, 0 );
    }
}

void Graphics::quit()
{
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
