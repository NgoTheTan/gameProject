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
    srand(time(0));
    int time=0, level=0;

    Graphics graphics;
    graphics.initSDL();

    ParallaxBackground background;
    graphics.initBackground(background);

    SDL_Texture* berieTexture=graphics.loadTexture(BERIE_FILE);
    Character berie(berieTexture);

    SDL_Texture* birdTexture=graphics.loadTexture(BIRD_FILE);
    Obstacle bird(birdTexture, BIRD);
    SDL_Texture* crabTexture=graphics.loadTexture(CRAB_FILE);
    Obstacle crab(crabTexture, CRAB);

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
        SDL_Rect* currentClip_Character = nullptr;
        graphics.renderBackground(background, LEVEL[level]);

        if (berie.running()){
            berie.run.tick();
            currentClip_Character=berie.run.getCurrentClip();
            graphics.renderSprite(berie.posX, berie.posY, berie.run);
        }
        else if (berie.jumping()){
            berie.jump.tick();
            currentClip_Character=berie.jump.getCurrentClip();
            graphics.renderSprite(berie.posX, berie.posY, berie.jump);
        }
        else if (berie.falling()){
            berie.fall.tick();
            currentClip_Character=berie.fall.getCurrentClip();
            graphics.renderSprite(berie.posX, berie.posY, berie.fall);
        }
        bird.Move(LEVEL[level]);
        bird.foe.tick();
        graphics.renderSprite(bird.posX, bird.posY, bird.foe);
        crab.Move(LEVEL[level]);
        crab.foe.tick();
        graphics.renderSprite(crab.posX, crab.posY, crab.foe);
        if (checkEnemyCollision(berie, currentClip_Character, bird, bird.foe.getCurrentClip())){
            quit=true;
        }
        if (checkEnemyCollision(berie, currentClip_Character, crab, crab.foe.getCurrentClip())){
            quit=true;
        }
        graphics.present();
        frameTime=SDL_GetTicks()-frameStart;
        if (FRAME_DELAY>frameTime) SDL_Delay(FRAME_DELAY-frameTime);
        time++;
        if (time>TIME_UP){
            time=0;
            if (level<MAX_LEVEL) level++;
        }
    }
    destroyBackground(background);
    SDL_DestroyTexture(berieTexture);
    graphics.quit();
    return 0;
}
