#include <iostream>
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

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    TTF_Font* font = graphics.loadFont("assets//font//Purisa-BoldOblique.ttf", 100);
    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* helloText = graphics.renderText("Hello", font, color);

    Mix_Music *gMusic = graphics.loadMusic("assets//music//RunningAway.mp3");
    graphics.playMusic(gMusic);
    Mix_Chunk *gJump = graphics.loadSound("assets//music//jump.wav");

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("assets//image//r.jpg"));

    Character man;
    SDL_Texture* manTexture=graphics.loadTexture(MAN_SPRITE_FILE);
    man.frontView.init(manTexture, FRONT_FRAMES, FRONT_CLIPS);
    man.backView.init(manTexture, BACK_FRAMES, BACK_CLIPS);
    man.rightView.init(manTexture, RIGHT_FRAMES, RIGHT_CLIPS);
    man.leftView.init(manTexture, LEFT_FRAMES, LEFT_CLIPS);
    man.standStill.init(manTexture, STAND_FRAMES, STAND_STILL);

    Mouse mouse(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    Cheese cheese(100, 100);

    bool quit = false;
    SDL_Event event;
    while (!quit && !gameOver(mouse)){
        graphics.prepareScene();

        graphics.renderBackground(background);

        graphics.renderTexture(helloText, 200, 200);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_W]){
            mouse.up();
            man.backView.tick();
            graphics.renderSprite(mouse.rect.x, mouse.rect.y, man.backView);
            man.standStill.currentFrame=3;
        }
        else if (currentKeyStates[SDL_SCANCODE_S]) {
            mouse.down();
            man.frontView.tick();
            graphics.renderSprite(mouse.rect.x, mouse.rect.y, man.frontView);
            man.standStill.currentFrame=0;
        }
        else if (currentKeyStates[SDL_SCANCODE_A]) {
            mouse.left();
            man.leftView.tick();
            graphics.renderSprite(mouse.rect.x, mouse.rect.y, man.leftView);
            man.standStill.currentFrame=1;
        }
        else if (currentKeyStates[SDL_SCANCODE_D]){
            mouse.right();
            man.rightView.tick();
            graphics.renderSprite(mouse.rect.x, mouse.rect.y, man.rightView);
            man.standStill.currentFrame=2;
        }
        else graphics.renderSprite(mouse.rect.x, mouse.rect.y, man.standStill);
        if (mouse.canEat(cheese)){
            cheese.eaten=true;
        }
        if (!cheese.eaten){
            render(cheese, graphics);
        }
        if (currentKeyStates[SDL_SCANCODE_UP]) graphics.playSound(gJump);
        graphics.present();
        SDL_Delay(90);
    }
    SDL_DestroyTexture( manTexture ); manTexture = NULL;
    SDL_DestroyTexture(background.texture);
    if (gMusic != nullptr) Mix_FreeMusic(gMusic);
    if (gJump != nullptr) Mix_FreeChunk(gJump);
    SDL_DestroyTexture( helloText );
    TTF_CloseFont( font );
    helloText = NULL;
    graphics.quit();
    return 0;
}
