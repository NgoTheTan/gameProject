#include "game.h"
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true){
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void handleBackButton(Graphics &graphics, SDL_Event *event, Button &backButton,Sound &sound)
{
    if (!backButton.on){
        backButton.texX=196; backButton.texY=0;
        return;
    }
    if (backButton.inside(event, SMALL_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            backButton.texX=260; backButton.texY=0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            backButton.clicked=true;
            graphics.playSound(sound.clickSound);
            backButton.texX=324; backButton.texY=0;
            break;
        }
    }
    else{
        backButton.texX=196; backButton.texY=0;
    }
}
void handlePlayButton (Graphics &graphics, SDL_Event *event, Button &playButton,Sound &sound)
{
    if (!playButton.on){
        playButton.texX=0; playButton.texY=64;
        return;
    }
    if (playButton.inside(event, MED_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            playButton.texX=128; playButton.texY=64;
            break;
        case SDL_MOUSEBUTTONDOWN:
            playButton.clicked=true;
            graphics.playSound(sound.clickSound);
            playButton.texX=256; playButton.texY=64;
            break;
        }
    }
    else{
        playButton.texX=0; playButton.texY=64;
    }
}
void handleInfoButton (Graphics &graphics, SDL_Event *event, Button &infoButton,Sound &sound)
{
    if (!infoButton.on){
        infoButton.texX=0; infoButton.texY=262;
        return;
    }
    if (infoButton.inside(event, MED_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            infoButton.texX=128; infoButton.texY=262;
            break;
        case SDL_MOUSEBUTTONDOWN:
            infoButton.clicked=true;
            graphics.playSound(sound.clickSound);
            infoButton.texX=256; infoButton.texY=262;
            break;
        }
    }
    else{
        infoButton.texX=0; infoButton.texY=262;
    }
}
void handleCreditButton (Graphics &graphics, SDL_Event *event, Button &creditButton,Sound &sound)
{
    if (!creditButton.on) {
        creditButton.texX=0; creditButton.texY=196;
        return;
    }
    if (creditButton.inside(event, BIG_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            creditButton.texX=160; creditButton.texY=196;
            break;
        case SDL_MOUSEBUTTONDOWN:
            creditButton.clicked=true;
            graphics.playSound(sound.clickSound);
            creditButton.texX=320; creditButton.texY=196;
            break;
        }
    }
    else{
        creditButton.texX=0; creditButton.texY=196;
    }
}
void handleQuitButton (Graphics& graphics, SDL_Event *event, Button &quitButton, Sound &sound)
{
    if (!quitButton.on){
        quitButton.texX=0; quitButton.texY=130;
        return;
    }
    if (quitButton.inside(event,MED_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            quitButton.texX=128; quitButton.texY=130;
            break;
        case SDL_MOUSEBUTTONDOWN:
            quitButton.clicked=true;
            graphics.playSound(sound.clickSound);
            quitButton.texX=256; quitButton.texY=130;
            break;
        }
    }
    else{
        quitButton.texX=0; quitButton.texY=130;
    }
}

void action(Graphics& graphics, ParallaxBackground& background, Sound &sound, Character &berie, Obstacle &castle, Obstacle &bird, Obstacle &crab,
            Obstacle &water, vector<Bullet*> &bullets, const int speedUp, const int types, const int level, int& score, bool &quit)
{
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
        if (berie.status!=DEAD && !bird.dead) graphics.playSound(sound.deadSound);
        if (!bird.dead) berie.status=DEAD;
    }
    if (checkObstacleCollision(berie, crab, crab.foe.getCurrentClip())){
        if (berie.status!=DEAD) graphics.playSound(sound.deadSound);
        berie.status=DEAD;
    }
    if (checkObstacleCollision(berie, castle, castle.foe.getCurrentClip())){
        if (!berie.attacking() && !castle.dead){
            if (berie.status!=DEAD) graphics.playSound(sound.deadSound);
            berie.status=DEAD;
        }
        else {
            if (!castle.dead) score+=20;
            castle.dead=true;
        }
    }
    if (checkObstacleCollision(berie, water, water.collect.getCurrentClip())){
        if (!water.dead){
            berie.power+=POWER_GAIN;
            graphics.playSound(sound.gCollect);
        }
        water.dead=true;
    }
    if (!berie.damaged()){
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
    }
    else{
        if (!(berie.dead.currentFrame==DEAD_FRAMES*FRAME_RATE-1)){
            berie.playDead();
            berie.dead.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.dead);
        }
        else{
            SDL_Delay(1000);
            quit=true;
        }
    }
    if (bullets.size()>0){
        shooting(bullets,graphics,castle, bird, speedUp, score, sound, level);
    }
}
void HUD(Graphics& graphics, const Character berie, SDL_Texture* barTexture, Text &text, const int score, const int highScore)
{
    graphics.renderUI(barTexture, BAR_X, BAR_Y, 0, 0,271,145);
    if (berie.gun && berie.power/POWER_GAIN>=0 && berie.power/POWER_GAIN <=1) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[0],54);
    else if (berie.power/POWER_GAIN > 0 && berie.power/POWER_GAIN <=1) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[0],54);
    else if (berie.power/POWER_GAIN >= 1 && berie.power/POWER_GAIN <=2) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[1],54);
    else if (berie.power/POWER_GAIN >= 2 && berie.power/POWER_GAIN <=3) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[2],54);
    else if (berie.power/POWER_GAIN >= 3 && berie.power/POWER_GAIN <=4) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[3],54);
    else if (berie.power/POWER_GAIN >= 4 && berie.power/POWER_GAIN <=5) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[4],54);
    else if (berie.power/POWER_GAIN >= 5 && berie.power/POWER_GAIN <=6) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[5],54);
    else if (berie.power/POWER_GAIN >= 6 && berie.power/POWER_GAIN <=7) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[6],54);
    else if (berie.power/POWER_GAIN >= 7 && berie.power/POWER_GAIN <=8) graphics.renderUI(barTexture, POW_POS_X, POW_POS_Y, 286,10,POW_WIDTH[7],54);
    switch(berie.energy/117)
    {
    case 1:
        graphics.renderUI(barTexture, ENERGY_POS_X[0], ENERGY_POS_Y,287,98,27,22);
        break;
    case 2:
        graphics.renderUI(barTexture, ENERGY_POS_X[0], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[1], ENERGY_POS_Y,287,98,27,22);
        break;
    case 3:
        graphics.renderUI(barTexture, ENERGY_POS_X[0], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[1], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[2], ENERGY_POS_Y,287,98,27,22);
        break;
    case 4:
        graphics.renderUI(barTexture, ENERGY_POS_X[0], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[1], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[2], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[3], ENERGY_POS_Y,287,98,27,22);
        break;
    case 5:
        graphics.renderUI(barTexture, ENERGY_POS_X[0], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[1], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[2], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[3], ENERGY_POS_Y,287,98,27,22);
        graphics.renderUI(barTexture, ENERGY_POS_X[4], ENERGY_POS_Y,287,98,27,22);
        break;
    default: break;
    }
    text.renderScore(graphics, score, highScore);
    graphics.renderTexture(text.yourScoreText,YS_TEXT_POS_X, YS_TEXT_POS_Y);
    graphics.renderTexture(text.scoreText, S_TEXT_POS_X, YS_TEXT_POS_Y);
    graphics.renderTexture(text.highText, HI_TEXT_POS_X, HI_TEXT_POS_Y);
    if (score<=highScore) graphics.renderTexture(text.highScoreText, HS_TEXT_POS_X, HI_TEXT_POS_Y);
    else graphics.renderTexture(text.scoreText, HS_TEXT_POS_X, HI_TEXT_POS_Y);
}
void update(int &time, int &speedUp,int &level, int &types, int& score)
{
    time++;
    if (time%10==0) score+=(1+level*SCORE_MULTIPLIER);
    if (time%500==0 && time!=0) speedUp++;
    if (time>TIME_UP){
        time=0;
        if (level<MAX_LEVEL) level++;
        if (types<MAX_TYPE) types++;
    }
}
void destroyBackground(ParallaxBackground& background)
{
    SDL_DestroyTexture(background.layer_1.texture); background.layer_1.texture=NULL;
    SDL_DestroyTexture(background.layer_2.texture); background.layer_2.texture=NULL;
    SDL_DestroyTexture(background.layer_3.texture); background.layer_3.texture=NULL;
    SDL_DestroyTexture(background.layer_4.texture); background.layer_4.texture=NULL;
}
void destroyChar(Character& character)
{
    SDL_DestroyTexture(character.run.texture); character.run.texture=NULL;
    SDL_DestroyTexture(character.jump.texture); character.jump.texture=NULL;
    SDL_DestroyTexture(character.fall.texture); character.fall.texture=NULL;
    SDL_DestroyTexture(character.headbutt.texture); character.headbutt.texture=NULL;
    SDL_DestroyTexture(character.dead.texture); character.dead.texture=NULL;
    SDL_DestroyTexture(character.runWithGun.texture); character.runWithGun.texture=NULL;
    SDL_DestroyTexture(character.jumpWithGun.texture); character.jumpWithGun.texture=NULL;
    SDL_DestroyTexture(character.fallWithGun.texture); character.fallWithGun.texture=NULL;
}
void destroyObs(Obstacle& castle, Obstacle& bird, Obstacle& crab, Obstacle& water)
{
    SDL_DestroyTexture(castle.foe.texture); castle.foe.texture=NULL;
    SDL_DestroyTexture(castle.vanish.texture); castle.vanish.texture=NULL;
    SDL_DestroyTexture(bird.foe.texture); bird.foe.texture=NULL;
    SDL_DestroyTexture(bird.vanish.texture); bird.vanish.texture=NULL;
    SDL_DestroyTexture(crab.foe.texture); crab.foe.texture=NULL;
    SDL_DestroyTexture(crab.vanish.texture); crab.vanish.texture=NULL;

    SDL_DestroyTexture(water.collect.texture); water.collect.texture=NULL;
}
void destroySoundAndText(Sound &sound, Text &text)
{
    if (sound.gMusic!=nullptr) Mix_FreeMusic(sound.gMusic);
    if (sound.mMusic!=nullptr) Mix_FreeMusic(sound.mMusic);
    if (sound.clickSound!=nullptr) Mix_FreeChunk(sound.clickSound);
    if (sound.birdSound!=nullptr) Mix_FreeChunk(sound.birdSound);
    if (sound.deadSound!=nullptr) Mix_FreeChunk(sound.deadSound);
    if (sound.gAttack!=nullptr) Mix_FreeChunk(sound.gAttack);
    if (sound.gCollect!=nullptr) Mix_FreeChunk(sound.gCollect);
    if (sound.gJump!=nullptr) Mix_FreeChunk(sound.gJump);
    if (sound.shootWater!=nullptr) Mix_FreeChunk(sound.shootWater);
    if (sound.waterSplash!=nullptr) Mix_FreeChunk(sound.waterSplash);
    TTF_CloseFont(text.font);
}
