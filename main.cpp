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
    int time=0, level=0, speedUp=0, types=BASE_TYPES;

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
    SDL_Texture* castleTexture=graphics.loadTexture(CASTLES_FILE);
    Obstacle castle(castleTexture, CASTLE);

    bool quit=false;
    SDL_Event event;
    while (!quit){
        frameStart=SDL_GetTicks();

        graphics.prepareScene();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_SPACE] && berie.running() && !berie.damaged()){
            berie.status=JUMP;
        }
        SDL_Rect* currentClip_Character = nullptr;
        graphics.renderBackground(background, speedUp);
        if(!berie.damaged()) berie.Move();
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
        if (level>=0){
            castle.Move(speedUp, types);
            graphics.renderSprite(castle.posX, castle.posY, castle.foe);
            bird.Move(speedUp, types);
            bird.foe.tick();
            graphics.renderSprite(bird.posX, bird.posY, bird.foe);
        }
        if (level>=2){
            crab.Move(speedUp,types);
            crab.foe.tick();
            graphics.renderSprite(crab.posX, crab.posY, crab.foe);
        }
        if (checkEnemyCollision(berie, currentClip_Character, bird, bird.foe.getCurrentClip())){
            berie.status=DEAD;
        }
        if (checkEnemyCollision(berie, currentClip_Character, crab, crab.foe.getCurrentClip())){
                berie.status=DEAD;
            }
            if (checkEnemyCollision(berie, currentClip_Character, castle, castle.foe.getCurrentClip())){
                berie.status=DEAD;
            }
        if (berie.damaged()){
            berie.playDead();
            berie.dead.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.dead);
            if (berie.dead.currentFrame==DEAD_FRAMES*FRAME_RATE-1) {
                SDL_Delay(1000);
                quit=true;
            }
        }
        graphics.present();
        frameTime=SDL_GetTicks()-frameStart;
        if (FRAME_DELAY>frameTime) SDL_Delay(FRAME_DELAY-frameTime);
        time++;
        if (time>TIME_UP){
            time=0;
            if (level<MAX_LEVEL) level++;
            if (types<MAX_TYPE) types++;
        }
        if (time%(TIME_UP/ACCEL_PACE)==0 && time!=0){
            speedUp++;
        }
    }
    destroyBackground(background);
    SDL_DestroyTexture(berieTexture);
    graphics.quit();
    return 0;
}
