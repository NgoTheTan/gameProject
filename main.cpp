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
    Uint32 frameStart;
    int frameTime;

    Graphics graphics;
    graphics.initSDL();

    ParallaxBackground background;
    graphics.initBackground(background);

    Character berie;
    SDL_Texture* berieTexture=graphics.loadTexture(BERIE_FILE);
    berie.init(berieTexture);

    bool quit=false;
    SDL_Event event;
    while (!quit){
        frameStart=SDL_GetTicks();

        graphics.prepareScene();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_SPACE] && berie.running()){
            berie.status=JUMP;
        }
        berie.Move();
        graphics.renderBackground(background, LEVEL[0]);

        if (berie.running()){
            berie.run.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.run);
        }
        else if (berie.jumping()){
            berie.jump.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.jump);
        }
        else if (berie.falling()){
            berie.fall.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.fall);
        }
        graphics.present();
        frameTime=SDL_GetTicks()-frameStart;
        if (FRAME_DELAY>frameTime) SDL_Delay(FRAME_DELAY-frameTime);
    }
    destroyBackground(background);
    SDL_DestroyTexture(berieTexture);
    graphics.quit();
    return 0;
}
