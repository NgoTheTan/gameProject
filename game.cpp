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
    if (backButton.underMouse(event, SMALL_BUTTON)){
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
    if (playButton.underMouse(event, MED_BUTTON)){
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
    if (infoButton.underMouse(event, MED_BUTTON)){
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
    if (creditButton.underMouse(event, BIG_BUTTON)){
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
    if (quitButton.underMouse(event,MED_BUTTON)){
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
void handleMainMenuButton(Graphics& graphics, SDL_Event *event, Button &mainMenuButton, Sound &sound)
{
    if (mainMenuButton.underMouse(event, HUGE_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            mainMenuButton.texX=192; mainMenuButton.texY=458;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mainMenuButton.clicked=true;
            graphics.playSound(sound.clickSound);
            mainMenuButton.texX=384; mainMenuButton.texY=458;
            break;
        }
    }
    else{
        mainMenuButton.texX=0; mainMenuButton.texY=458;
    }
}
void handleGameOverButton(Graphics& graphics, SDL_Event *event, Button &gameOverButton, Sound &sound)
{
    if (gameOverButton.underMouse(event, HUGE_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            gameOverButton.texX=192; gameOverButton.texY=392;
            break;
        case SDL_MOUSEBUTTONDOWN:
            gameOverButton.clicked=true;
            graphics.playSound(sound.clickSound);
            gameOverButton.texX=384; gameOverButton.texY=392;
            break;
        }
    }
    else{
        gameOverButton.texX=0; gameOverButton.texY=392;
    }
}
void handleRestartButton(Graphics &graphics, SDL_Event *event, Button &restartButton, Sound &sound)
{
    if (restartButton.underMouse(event,BIG_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            restartButton.texX=160; restartButton.texY=326;
            break;
        case SDL_MOUSEBUTTONDOWN:
            restartButton.clicked=true;
            graphics.playSound(sound.clickSound);
            restartButton.texX=320; restartButton.texY=326;
            break;
        }
    }
    else{
        restartButton.texX=0; restartButton.texY=326;
    }
}
void handlePauseButton (Graphics &graphics, SDL_Event *event, Button &pauseButton, Sound &sound)
{
    if (!pauseButton.on){
        pauseButton.texX=392; pauseButton.texY=0;
        return;
    }
    if (pauseButton.underMouse(event, SMALL_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            pauseButton.texX=456; pauseButton.texY=0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            pauseButton.texX=520; pauseButton.texY=0;
            pauseButton.clicked=true;
            graphics.playSound(sound.clickSound);
            break;
        }
    }
    else{
        pauseButton.texX=392; pauseButton.texY=0;
    }
}
void handleContinueButton(Graphics &graphics, SDL_Event *event, Button &continueButton, Sound &sound)
{
    if (!continueButton.on){
        continueButton.texX=0; continueButton.texY=0;
        return;
    }
    if (continueButton.underMouse(event, SMALL_BUTTON)){
        switch(event->type)
        {
        case SDL_MOUSEMOTION:
            continueButton.texX=64; continueButton.texY=0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            continueButton.clicked=true;
            graphics.playSound(sound.clickSound);
            continueButton.texX=128; continueButton.texY=0;
            break;
        }
    }
    else{
        continueButton.texX=0; continueButton.texY=0;
    }
}
void workOnMenu(Graphics &graphics,SDL_Texture* menu, SDL_Texture* info, SDL_Texture* credit, Text &text, Button &playButton, Button &infoButton, Button &creditButton, Button &quitButton,
                Button& backButton, bool &inMenu, bool &inInfo, bool &inCredit, bool &quitMenu, bool &Play, bool &quit)
{
    if (inMenu){
        graphics.renderTexture(menu, 0, 0);
        playButton.on=true; infoButton.on=true; creditButton.on=true; quitButton.on=true; backButton.on=false;
        graphics.renderUI(playButton.buttonTexture, playButton.posX, playButton.posY, playButton.texX, playButton.texY, MED_BUTTON_W, BUTTON_H);
        graphics.renderUI(infoButton.buttonTexture, infoButton.posX, infoButton.posY, infoButton.texX, infoButton.texY, MED_BUTTON_W, BUTTON_H);
        graphics.renderUI(creditButton.buttonTexture, creditButton.posX, creditButton.posY, creditButton.texX, creditButton.texY, BIG_BUTTON_W, BUTTON_H);
        graphics.renderUI(quitButton.buttonTexture, quitButton.posX, quitButton.posY, quitButton.texX, quitButton.texY, MED_BUTTON_W, BUTTON_H);
        graphics.renderTexture(text.bestText, M_BEST_TEXT_POS_X, M_BEST_TEXT_POS_Y);
        graphics.renderTexture(text.highScoreText, M_HS_TEXT_POS_X, M_BEST_TEXT_POS_Y);
    }
    if (inInfo){
        graphics.renderTexture(info, 0,0);
        playButton.on=false; infoButton.on=false; creditButton.on=false; quitButton.on=false; backButton.on=true;
        graphics.renderUI(backButton.buttonTexture, backButton.posX, backButton.posY, backButton.texX, backButton.texY, SMALL_BUTTON_W, BUTTON_H);
    }
    if (inCredit){
        graphics.renderTexture(credit, 0,0);
        playButton.on=false; infoButton.on=false; creditButton.on=false; quitButton.on=false; backButton.on=true;
        graphics.renderUI(backButton.buttonTexture, backButton.posX, backButton.posY, backButton.texX, backButton.texY, SMALL_BUTTON_W, BUTTON_H);
    }
    if (playButton.clicked){
        Play=true;
        quitMenu=true;
        playButton.clicked=false;
        playButton.texX=0; playButton.texY=64;
    }
    if (infoButton.clicked){
        inMenu=false; inInfo=true;
        if (!infoButton.on) infoButton.clicked=false;
    }
    if (creditButton.clicked){
        inMenu=false; inCredit=true;
        if (!creditButton.on) creditButton.clicked=false;
    }
    if (quitButton.clicked){
        quitMenu=true;
        quit=true;
    }
    if (backButton.clicked){
        if (inInfo) inInfo=false;
        if (inCredit) inCredit=false;
        inMenu=true;
        if (!backButton.on) backButton.clicked=false;
    }
}
void intro(Graphics &graphics, SDL_Texture* intro1, SDL_Texture* intro2, SDL_Texture* intro3, SDL_Texture* intro4, Sound &sound)
{
    graphics.renderTexture(intro1, 0, 0);
    graphics.present();
    graphics.playSound(sound.earthquake);
    SDL_Delay(3000);
    graphics.renderTexture(intro2,0,0);
    graphics.present();
    graphics.playSound(sound.tsunami);
    SDL_Delay(1000);
    graphics.playSound(sound.terrify);
    SDL_Delay(2000);
    graphics.renderTexture(intro3,0,0);
    graphics.present();
    SDL_Delay(500);
    graphics.playSound(sound.run);
    SDL_Delay(1000);
    graphics.renderTexture(intro4,0,0);
    graphics.present();
    SDL_Delay(1000);
}
void workOnLoseSelection(Graphics &graphics, Button &mainMenuButton, Button &restartButton, Button &gameOverButton, Character &berie,
                         Obstacle& castle, Obstacle &bird, Obstacle&crab, Obstacle& water, bool &selectOption, bool &Menu, bool &Play, bool &quit)
{
    graphics.renderUI(mainMenuButton.buttonTexture, mainMenuButton.posX, mainMenuButton.posY, mainMenuButton.texX, mainMenuButton.texY, HUGE_BUTTON_W, BUTTON_H);
    graphics.renderUI(restartButton.buttonTexture, restartButton.posX, restartButton.posY, restartButton.texX, restartButton.texY, BIG_BUTTON_W, BUTTON_H);
    graphics.renderUI(gameOverButton.buttonTexture, gameOverButton.posX, gameOverButton.posY, gameOverButton.texX, gameOverButton.texY,HUGE_BUTTON_W, BUTTON_H );
    if (gameOverButton.clicked){
        quit=true;
        selectOption=false;
    }
    if (mainMenuButton.clicked){
        Menu=true;
        berie.revive();
        castle.reset(); bird.reset(); crab.reset(); water.reset();
        selectOption=false;
        mainMenuButton.clicked=false;
        mainMenuButton.texX=0; mainMenuButton.texY=458;
    }
    if (restartButton.clicked){
        Play=true;
        berie.revive();
        castle.reset(); bird.reset(); crab.reset(); water.reset();
        selectOption=false;
        restartButton.clicked=false;
        restartButton.texX=0; restartButton.texY=326;
    }
}
void generateObstacles(const Character berie, Graphics &graphics, Obstacle &castle, Obstacle &bird, Obstacle &crab, Obstacle &water, const int speedUp, const int types, const int level)
{
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
    if (!berie.gun){
        water.spawn(speedUp);
        if (!water.dead){
            water.collect.tick();
            graphics.renderSprite(water.posX, water.posY, water.collect);
        }
    }
    checkOveride(castle, bird, crab, water);
}
void obstacleCollision(Graphics& graphics, Sound &sound, Character &berie, Obstacle &castle, Obstacle &bird, Obstacle &crab, Obstacle &water, int &score)
{
    if (checkObstacleCollision(berie, bird, bird.foe.getCurrentClip())){
        if (berie.status!=DEAD && !bird.dead) graphics.playSound(sound.deadSound);
        if (!bird.dead) berie.status=DEAD;
    }
    if (checkObstacleCollision(berie, crab, crab.foe.getCurrentClip())){
        if (berie.status!=DEAD) graphics.playSound(sound.deadSound);
        berie.status=DEAD;
    }
    if (checkObstacleCollision(berie, castle, castle.foe.getCurrentClip())){
        if (berie.status!=ATTACK && !castle.dead){
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
}
void characterAction(Graphics& graphics, Character &berie, bool &quitPlay, bool &Lose)
{
    if (berie.status!=DEAD){
        if (berie.power==MAX_POWER){
            berie.getGun.tick();
            graphics.renderSprite(berie.posX, berie.posY, berie.getGun);
        }
        else if (berie.status==RUN){
            if (berie.gun){
                berie.runWithGun.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.runWithGun);
            }
            else{
                berie.run.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.run);
                }
        }
        else if (berie.status==JUMP){
            if (berie.gun){
                berie.jumpWithGun.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.jumpWithGun);
            }
            else{
                berie.jump.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.jump);
            }
        }
        else if (berie.status==FALL){
            if (berie.gun){
                berie.fallWithGun.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.fallWithGun);
            }
            else{
                berie.fall.tick();
                graphics.renderSprite(berie.posX, berie.posY, berie.fall);
                }
        }
        else if (berie.status==ATTACK){
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
            Mix_HaltMusic();
            SDL_Delay(500);
            quitPlay=true;
            Lose=true;
        }
    }
}
void UI(Graphics& graphics, const Character berie, SDL_Texture* barTexture, Text &text, const int score, const int highScore)
{
    graphics.renderUI(barTexture, 10, 5, 0, 0,271,145);
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
    graphics.renderTexture(text.bestText, BEST_TEXT_POS_X, BEST_TEXT_POS_Y);
    if (score<=highScore) graphics.renderTexture(text.highScoreText, HS_TEXT_POS_X, BEST_TEXT_POS_Y);
    else graphics.renderTexture(text.scoreText, HS_TEXT_POS_X, BEST_TEXT_POS_Y);
    SDL_DestroyTexture(text.scoreText); text.scoreText=NULL;
    SDL_DestroyTexture(text.highScoreText); text.highScoreText=NULL;
}
void update(const Character berie, int &time, int &speedUp,int &level, int &types, int& score)
{
    time++;
    if (berie.status!=DEAD){
        if (time%10==0) score+=(1+level*SCORE_MULTIPLIER);
    }
    if (time>TIME_UP){
        time=0;
        speedUp++;
        if (level<MAX_LEVEL) level++;
        if (types<MAX_TYPE) types++;
    }
}
