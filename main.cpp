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

    SDL_Texture* waterBulletTexture=graphics.loadTexture(SHOOT_FILE);
    SDL_Texture* waterSplash=graphics.loadTexture(SPLASH_FILE);
    SDL_Texture* waterTexture=graphics.loadTexture(BALL_FILE);
    Obstacle water(waterTexture);
    SDL_Texture* vanishTexture=graphics.loadTexture(VANISH_FILE);
    SDL_Texture* birdTexture=graphics.loadTexture(BIRD_FILE);
    Obstacle bird(birdTexture, vanishTexture, BIRD);
    SDL_Texture* crabTexture=graphics.loadTexture(CRAB_FILE);
    Obstacle crab(crabTexture, vanishTexture, CRAB);
    SDL_Texture* castleTexture=graphics.loadTexture(CASTLES_FILE);
    Obstacle castle(castleTexture,vanishTexture, CASTLE);
    vector<Bullet*> bullets;

    bool quit=false;
    SDL_Event event;
    while (!quit){
        frameStart=SDL_GetTicks();
        graphics.prepareScene();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (!berie.damaged()){
            if (currentKeyStates[SDL_SCANCODE_S] && !berie.attacking() && berie.reload==100 && berie.gun){
                    berie.reload=0;
                    Bullet* waterBullet=new Bullet(waterBulletTexture, waterSplash, berie.posY+40);
                    bullets.push_back(waterBullet);
                }
            if (berie.running()){
                if (currentKeyStates[SDL_SCANCODE_SPACE] && !berie.attacking()){
                    berie.status=JUMP;
                }
                if (currentKeyStates[SDL_SCANCODE_A] && !berie.attacking() && berie.energy==BASE_ENERGY){
                    berie.status=ATTACK;
                }
            }
        }

        graphics.renderBackground(background, speedUp);

        if(!berie.damaged() && !berie.attacking()) berie.Move();
        if (level>=0){
            castle.Move(speedUp, types);
            if (castle.dead){
                if (castle.vanish.currentFrame!=VANISH_FRAMES*FRAME_RATE-1) {
                    graphics.renderSprite(castle.posX+(castle.foe.getCurrentClip()->w/80)*30, castle.posY+(castle.foe.getCurrentClip()->h/80)*40, castle.vanish);
                    castle.vanish.tick();
                }
            }
            else graphics.renderSprite(castle.posX, castle.posY, castle.foe);
            bird.Move(speedUp, types);
            if (bird.dead){
                if (bird.vanish.currentFrame!=VANISH_FRAMES*FRAME_RATE-1) {
                    graphics.renderSprite(bird.posX, bird.posY, bird.vanish);
                    bird.vanish.tick();
                }
            }
            else{
                bird.foe.tick();
                graphics.renderSprite(bird.posX, bird.posY, bird.foe);
            }
        }
        if (level>=2){
            crab.Move(speedUp,types);
            if (crab.dead){
                if (crab.vanish.currentFrame!=VANISH_FRAMES*FRAME_RATE-1) {
                    graphics.renderSprite(crab.posX, crab.posY, crab.vanish);
                    crab.vanish.tick();
                }
            }
            else{
                crab.foe.tick();
                graphics.renderSprite(crab.posX, crab.posY, crab.foe);
            }
        }
        checkOveride(castle, bird, crab, water);

        if (!berie.gun){
            water.spawn(speedUp);
            if (!water.dead){
                water.collect.tick();
                graphics.renderSprite(water.posX, water.posY, water.collect);
            }
        }
        if (checkObstacleCollision(berie, bird, bird.foe.getCurrentClip())){
            if (!berie.attacking() && !bird.dead) berie.status=DEAD;
            else bird.dead=true;
        }
        if (checkObstacleCollision(berie, crab, crab.foe.getCurrentClip())){
            if (!berie.attacking()) berie.status=DEAD;
        }
        if (checkObstacleCollision(berie, castle, castle.foe.getCurrentClip())){
            if (!berie.attacking() && !castle.dead) berie.status=DEAD;
            else castle.dead=true;
        }
        if (checkObstacleCollision(berie, water, water.collect.getCurrentClip())){
            if (!water.dead){
                berie.power+=POWER_GAIN;
            }
            water.dead=true;
        }
        if (berie.power==MAX_POWER){
            berie.getGun.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.getGun);
        }
        else if (berie.running()){
            if (berie.gun){
                berie.runWithGun.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.runWithGun);
            }
            else{
                berie.run.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.run);
            }

        }
        else if (berie.jumping()){
            if (berie.gun){
                berie.jumpWithGun.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.jumpWithGun);
            }
            else{
                berie.jump.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.jump);
            }
        }
        else if (berie.falling()){
            if (berie.gun){
                berie.fallWithGun.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.fallWithGun);
            }
            else{
                berie.fall.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.fall);
            }

        }
        else if (berie.attacking()){
            berie.headbutt.tick();
            berie.attack();
            graphics.renderSprite(berie.posX, berie.posY, berie.headbutt);
        }
        else if (berie.damaged()){
            berie.playDead();
            berie.dead.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.dead);
            if (berie.dead.currentFrame==DEAD_FRAMES*FRAME_RATE-1) {
                SDL_Delay(1000);
                quit=true;
            }
        }
        if (bullets.size()>0){
            shooting(bullets,graphics,castle, bird, speedUp);
            cerr << bullets.size() << endl;
        }

        graphics.present();
        if(berie.power==MAX_POWER) SDL_Delay(1000);
        frameTime=SDL_GetTicks()-frameStart;
        if (FRAME_DELAY>frameTime) SDL_Delay(FRAME_DELAY-frameTime);
        time++;
        if (time>TIME_UP){
            time=0;
            speedUp++;
            if (level<MAX_LEVEL) level++;
            if (types<MAX_TYPE) types++;
        }
    }
    destroyBackground(background);
    destroyChar(berie);
    destroyObs(castle,bird,crab,water);
    graphics.quit();
    return 0;
}
