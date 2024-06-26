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
    currentFrame++;
    if (currentFrame==clips.size()*FRAME_RATE-FRAME_LOST) currentFrame++;
    if ((currentFrame/FRAME_RATE)>=clips.size()) currentFrame=0;
}
const SDL_Rect* Sprite::getCurrentClip() const{
        return &(clips[currentFrame/FRAME_RATE]);
}

void Layer::setTexture(SDL_Texture *_texture)
{
    texture=_texture;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}
void Layer::scroll(const int speed, const int accel)
{
    scrollingOffset-=(speed+accel);
    if (scrollingOffset<0) scrollingOffset=width;
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
    window=SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window==nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) logErrorAndExit("SDL_image error:", IMG_GetError());
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);
    if (renderer==nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    if (TTF_Init() == -1){
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
    }
}

void Graphics::present()
{
    SDL_RenderPresent(renderer);
}

void Graphics::renderLayer(const Layer& layer)
{
    Graphics::renderTexture(layer.texture, layer.scrollingOffset, 0);
    Graphics::renderTexture(layer.texture, layer.scrollingOffset-layer.width,0);
}

void Graphics::initBackground(ParallaxBackground& background)
{
    background.layer_1.setTexture(loadTexture("assets//image//sky.png"));
    background.layer_2.setTexture(loadTexture("assets//image//small_clouds.png"));
    background.layer_3.setTexture(loadTexture("assets//image//med_clouds.png"));
    background.layer_4.setTexture(loadTexture("assets//image//big_clouds.png"));
    background.ground.setTexture(loadTexture("assets//image//sand.png"));
}

void Graphics::renderBackground(ParallaxBackground& background, const int accel)
{
    background.layer_1.scroll(0, 0);
    renderLayer(background.layer_1);
    background.layer_2.scroll(1, accel);
    renderLayer(background.layer_2);
    background.layer_3.scroll(2, accel);
    renderLayer(background.layer_3);
    background.layer_4.scroll(3, accel);
    renderLayer(background.layer_4);
    background.ground.scroll(GROUND_SPEED, accel);
    renderLayer(background.ground);
}
void Graphics::stationaryBackground(ParallaxBackground& background)
{
    background.layer_1.scroll(0, 0);
    renderLayer(background.layer_1);
    background.layer_2.scroll(0, 0);
    renderLayer(background.layer_2);
    background.layer_3.scroll(0,0);
    renderLayer(background.layer_3);
    background.layer_4.scroll(0,0);
    renderLayer(background.layer_4);
    background.ground.scroll(0,0);
    renderLayer(background.ground);
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
void Graphics::renderUI(SDL_Texture* texture, int x, int y, int texX, int texY, int w, int h)
{
    SDL_Rect dest={x,y,w,h};
    SDL_Rect src={texX, texY, w, h};
    SDL_RenderCopy(renderer, texture, &src, &dest);
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
    return gChunk;
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

TTF_Font* Graphics::loadFont(const char* path, int size)
{
    TTF_Font* gFont =TTF_OpenFont( path, size );
    if (gFont == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}

SDL_Texture* Graphics::renderText(const string text, TTF_Font* font, SDL_Color textColor)
{
    const char* pText=&text[0];
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, pText, textColor );
    if( textSurface == nullptr ){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == nullptr ){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface( textSurface );
    return texture;
}

void Graphics::quit()
{
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
