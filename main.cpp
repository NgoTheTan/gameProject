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

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("image//r.jpg"));

    Character man;
    SDL_Texture* manTexture=graphics.loadTexture(MAN_SPRITE_FILE);
    man.frontView.init(manTexture, FRONT_FRAMES, FRONT_CLIPS);
    man.backView.init(manTexture, BACK_FRAMES, BACK_CLIPS);
    man.rightView.init(manTexture, RIGHT_FRAMES, RIGHT_CLIPS);
    man.leftView.init(manTexture, LEFT_FRAMES, LEFT_CLIPS);
    man.standStill.init(manTexture, STAND_FRAMES, STAND_STILL);

    Mouse mouse;
    mouse.x=SCREEN_WIDTH/2; mouse.y=SCREEN_HEIGHT/2;

    bool quit = false;
    SDL_Event event;
    while (!quit && !gameOver(mouse)){
        graphics.prepareScene();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        graphics.renderBackground(background);
        if (currentKeyStates[SDL_SCANCODE_W]){
            mouse.up();
            man.backView.tick();
            graphics.renderSprite(mouse.x, mouse.y, man.backView);
            man.standStill.currentFrame=3;
        }
        else if (currentKeyStates[SDL_SCANCODE_S]) {
            mouse.down();
            man.frontView.tick();
            graphics.renderSprite(mouse.x, mouse.y, man.frontView);
            man.standStill.currentFrame=0;
        }
        else if (currentKeyStates[SDL_SCANCODE_A]) {
            mouse.left();
            man.leftView.tick();
            graphics.renderSprite(mouse.x, mouse.y, man.leftView);
            man.standStill.currentFrame=1;
        }
        else if (currentKeyStates[SDL_SCANCODE_D]){
            mouse.right();
            man.rightView.tick();
            graphics.renderSprite(mouse.x, mouse.y, man.rightView);
            man.standStill.currentFrame=2;
        }
        else graphics.renderSprite(mouse.x, mouse.y, man.standStill);
        graphics.present();
        SDL_Delay(90);
    }
    SDL_DestroyTexture( manTexture ); manTexture = NULL;
    SDL_DestroyTexture(background.texture);
    graphics.quit();
    return 0;
}
