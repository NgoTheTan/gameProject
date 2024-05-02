#include "game.h"
using namespace std;
int main(int argc, char* argv[])
{
    string high=getHighScore("highScore.txt");
    stringstream convertToInt(high);
    int highScore=0;
    convertToInt >> highScore;

    Graphics graphics;
    graphics.initSDL();

    SDL_Texture* menu=graphics.loadTexture(MENU_FILE);
    SDL_Texture* info=graphics.loadTexture(INFO_FILE);
    SDL_Texture* credit=graphics.loadTexture(CREDIT_FILE);

    ParallaxBackground background;
    graphics.initBackground(background);

    SDL_Texture* berieTexture=graphics.loadTexture(BERIE_FILE);
    Character berie(berieTexture);
    SDL_Texture* barTexture=graphics.loadTexture(BAR_FILE);

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

    Button playButton(graphics, PLAY_BUTTON_POS_X, PLAY_BUTTON_POS_Y, 0,64);
    Button infoButton(graphics, INFO_BUTTON_POS_X, INFO_BUTTON_POS_Y,0,262);
    Button creditButton(graphics, CREDIT_BUTTON_POS_X, CREDIT_BUTTON_POS_Y,0,196);
    Button quitButton(graphics, QUIT_BUTTON_POS_X, QUIT_BUTTON_POS_Y,0,130);
    Button backButton(graphics, BACK_BUTTON_POS_X, BACK_BUTTON_POS_Y,196,0);

    Sound sound(graphics);
    Text text(graphics);
    bool quit=false;
    SDL_Event event;

    bool Menu=true, Play=false;
    while (!quit){
        if (Menu){
            graphics.playMusic(sound.mMusic);
            bool inMenu=true, inInfo=false, inCredit=false;
            bool quitMenu=false;
            while (!quitMenu){
                graphics.prepareScene();
                if (inMenu){
                    graphics.renderTexture(menu, 0, 0);
                    playButton.on=true; infoButton.on=true; creditButton.on=true; quitButton.on=true; backButton.on=false;
                    graphics.renderUI(playButton.buttonTexture, playButton.posX, playButton.posY, playButton.texX, playButton.texY, MED_BUTTON_W, BUTTON_H);
                    graphics.renderUI(infoButton.buttonTexture, infoButton.posX, infoButton.posY, infoButton.texX, infoButton.texY, MED_BUTTON_W, BUTTON_H);
                    graphics.renderUI(creditButton.buttonTexture, creditButton.posX, creditButton.posY, creditButton.texX, creditButton.texY, BIG_BUTTON_W, BUTTON_H);
                    graphics.renderUI(quitButton.buttonTexture, quitButton.posX, quitButton.posY, quitButton.texX, quitButton.texY, MED_BUTTON_W, BUTTON_H);
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
                    Menu=false;
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
                while (SDL_PollEvent(&event)){
                    if (event.type==SDL_QUIT){
                        quit=true;
                        quitMenu=true;
                    }
                    handlePlayButton(graphics, &event, playButton, sound);
                    handleInfoButton(graphics, &event, infoButton, sound);
                    handleCreditButton(graphics, &event, creditButton, sound);
                    handleQuitButton(graphics, &event, quitButton, sound);
                    handleBackButton(graphics, &event, backButton, sound);
                }
                graphics.present();
                SDL_Delay(100);
            }
        }
        if (Play){
            Mix_HaltMusic();
            Uint32 frameStart;
            int frameTime;
            srand(time(0));
            int time=0, level=0, speedUp=0, types=BASE_TYPES, score=0;
            vector<Bullet*> bullets;
            graphics.playMusic(sound.gMusic);
            bool quitPlay=false;
            while (!quitPlay){
                frameStart=SDL_GetTicks();
                graphics.prepareScene();
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) quitPlay = true;
                }
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (!berie.damaged()){
                    if (currentKeyStates[SDL_SCANCODE_S] && !berie.attacking() && berie.reload==150 && berie.gun){
                        berie.reload=0;
                        Bullet* waterBullet=new Bullet(waterBulletTexture, waterSplash, berie.posY+40);
                        bullets.push_back(waterBullet);
                        graphics.playSound(sound.shootWater);
                    }
                }
                if (berie.running()){
                    if (currentKeyStates[SDL_SCANCODE_SPACE] && !berie.attacking()){
                        berie.status=JUMP;
                        graphics.playSound(sound.gJump);
                    }
                    if (currentKeyStates[SDL_SCANCODE_A] && !berie.attacking() && berie.energy==BASE_ENERGY){
                        berie.status=ATTACK;
                        graphics.playSound(sound.gAttack);
                    }
                }

                action(graphics, background, sound, berie, castle, bird, crab, water, bullets, speedUp, types, level, score, quitPlay);
                HUD(graphics, berie, barTexture, text, score, highScore);
                graphics.present();
                if(berie.power==MAX_POWER && !berie.damaged()){
                    graphics.playSound(sound.yaySound);
                    SDL_Delay(1000);
                }
                frameTime=SDL_GetTicks()-frameStart;
                if (FRAME_DELAY>frameTime) SDL_Delay(FRAME_DELAY-frameTime);
                update(time, speedUp, level, types, score);
            }
            updateHighScore("highScore.txt", score, high);
            if (quitPlay){
                quit=true;
                Play=false;
            }
        }
    }

    destroyBackground(background);
    destroyChar(berie);
    destroyObs(castle,bird,crab,water);
    destroySoundAndText(sound, text);
    graphics.quit();
    return 0;
}
