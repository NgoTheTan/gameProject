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
    background.setTexture(graphics.loadTexture("image//bikiniBottom.jpg"));

    Mouse mouse;
    mouse.x = SCREEN_WIDTH/2;
    mouse.y = SCREEN_HEIGHT/2;

    bool quit = false;
    SDL_Event event;
    while (!quit && !gameOver(mouse)) {
        graphics.prepareScene();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_SPACE]){
            mouse.jump();
        }
        background.moveForward();
        mouse.fall();
        graphics.render(background);
        render(mouse, graphics);
        graphics.present();
        SDL_Delay(10);
    }
    SDL_DestroyTexture(background.texture);
    graphics.quit();
    return 0;
}
