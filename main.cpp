#include "game.h"
using namespace std;
int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.initSDL();

    SDL_Texture* menu=graphics.loadTexture("assets//image//menu.jpg");
    SDL_Texture* info=graphics.loadTexture("assets//image//instruction.png");
    SDL_Texture* credit=graphics.loadTexture("assets//image//credit.png");
    SDL_Texture* intro1=graphics.loadTexture("assets//image//intro1.jpg");
    SDL_Texture* intro2=graphics.loadTexture("assets//image//intro2.jpg");
    SDL_Texture* intro3=graphics.loadTexture("assets//image//intro3.jpg");
    SDL_Texture* intro4=graphics.loadTexture("assets//image//intro4.jpg");

    ParallaxBackground background;
    graphics.initBackground(background);

    SDL_Texture* berieTexture=graphics.loadTexture("assets//image//berie.png");
    Character berie(berieTexture);
    SDL_Texture* barTexture=graphics.loadTexture("assets//image//bars.png");

    SDL_Texture* waterBulletTexture=graphics.loadTexture("assets//image//shooting.png");
    SDL_Texture* waterSplash=graphics.loadTexture("assets//image//hit.png");
    SDL_Texture* waterTexture=graphics.loadTexture("assets//image//water.png");
    Obstacle water(waterTexture);

    SDL_Texture* vanishTexture=graphics.loadTexture("assets//image//smoke.png");
    SDL_Texture* birdTexture=graphics.loadTexture("assets//image//bird.png");
    Obstacle bird(birdTexture, vanishTexture, BIRD);
    SDL_Texture* crabTexture=graphics.loadTexture("assets//image//crab.png");
    Obstacle crab(crabTexture, vanishTexture, CRAB);
    SDL_Texture* castleTexture=graphics.loadTexture("assets//image//castles.png");
    Obstacle castle(castleTexture,vanishTexture, CASTLE);

    Button playButton(graphics, PLAY_BUTTON_POS_X, PLAY_BUTTON_POS_Y, 0,64);
    Button infoButton(graphics, INFO_BUTTON_POS_X, INFO_BUTTON_POS_Y,0,262);
    Button creditButton(graphics, CREDIT_BUTTON_POS_X, CREDIT_BUTTON_POS_Y,0,196);
    Button quitButton(graphics, QUIT_BUTTON_POS_X, QUIT_BUTTON_POS_Y,0,130);
    Button backButton(graphics, BACK_BUTTON_POS_X, BACK_BUTTON_POS_Y,196,0);
    Button mainMenuButton(graphics, MAIN_MENU_BUTTON_POS_X, L_BUTTON_POS_Y, 0, 458);
    Button restartButton(graphics, RESTART_BUTTON_POS_X, L_BUTTON_POS_Y, 0,326);
    Button gameOverButton(graphics, GAME_OVER_BUTTON_POS_X, L_BUTTON_POS_Y,0,392);
    Button pauseButton(graphics, PAUSE_CONTINUE_BUTTON_POS_X, PAUSE_CONTINUE_BUTTON_POS_Y, 392,0);
    Button continueButton(graphics, PAUSE_CONTINUE_BUTTON_POS_X, PAUSE_CONTINUE_BUTTON_POS_Y, 0, 0);

    Sound sound(graphics);
    Text text(graphics);

    bool quit=false;
    SDL_Event event;
    bool Menu=true, Play=false, Lose=false;
    int highScore=0, score=0;
    highScore=getHighScore("highScore.txt");
    while (!quit){
        if (Menu){
            graphics.playMusic(sound.mMusic);
            bool inMenu=true, inInfo=false, inCredit=false;
            bool quitMenu=false;
            text.renderScore(graphics, score, highScore);
            while (!quitMenu){
                workOnMenu(graphics,menu, info, credit, text, playButton, infoButton, creditButton,quitButton, backButton, inMenu, inInfo, inCredit,quitMenu, Play, quit);
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
            SDL_DestroyTexture(text.highScoreText); text.highScoreText=nullptr;
            SDL_DestroyTexture(text.scoreText); text.scoreText=nullptr;
            Mix_HaltMusic();
            if (Play){
                intro(graphics, intro1, intro2, intro3, intro4, sound);
            }
            Menu=false;
        }
        if (Play){
            Uint32 frameStart;
            int frameTime;
            srand(time(0));
            int time=0, level=0, speedUp=0, types=BASE_TYPES;
            score=0;
            vector<Bullet*> bullets;
            graphics.playMusic(sound.gMusic);
            bool quitPlay=false;
            while (!quitPlay){
                frameStart=SDL_GetTicks();
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quitPlay = true;
                        quit=true;
                    }
                    handlePauseButton(graphics, &event, pauseButton, sound);
                    handleContinueButton(graphics, &event, continueButton, sound);
                }
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (!pauseButton.clicked){
                    pauseButton.on=true;
                    continueButton.on=false;
                    if (currentKeyStates[SDL_SCANCODE_ESCAPE]) pauseButton.clicked=true;
                    if (berie.status!=DEAD){
                        if (currentKeyStates[SDL_SCANCODE_S] && berie.status!=ATTACK && berie.reload==150 && berie.gun){
                            berie.reload=0;
                            Bullet* waterBullet=new Bullet(waterBulletTexture, waterSplash, berie.posY+40);
                            bullets.push_back(waterBullet);
                            graphics.playSound(sound.shootWater);
                        }
                    }
                    if (berie.status==RUN){
                        if (currentKeyStates[SDL_SCANCODE_SPACE] && berie.status!=ATTACK){
                            berie.status=JUMP;
                            graphics.playSound(sound.gJump);
                        }
                        if (currentKeyStates[SDL_SCANCODE_A] && berie.status!=ATTACK && berie.energy==BASE_ENERGY){
                            berie.status=ATTACK;
                            graphics.playSound(sound.gAttack);
                        }
                    }
                    graphics.renderBackground(background, speedUp);
                    graphics.renderUI(pauseButton.buttonTexture, pauseButton.posX, pauseButton.posY, pauseButton.texX, pauseButton.texY, SMALL_BUTTON_W, BUTTON_H);
                    if(berie.status!=DEAD && berie.status!=ATTACK) berie.Move();
                    generateObstacles(berie, graphics, castle, bird, crab, water, speedUp, types, level);
                    obstacleCollision(graphics, sound, berie, castle, bird, crab, water, score);
                    characterAction(graphics, berie, quitPlay, Lose);
                    UI(graphics, berie, barTexture, text, score, highScore);
                    if (bullets.size()>0){
                        shooting(bullets,graphics,castle, bird, speedUp, score, sound, level);
                    }
                    graphics.present();
                    if(berie.power==MAX_POWER && berie.status!=DEAD){
                        graphics.playSound(sound.yaySound);
                        SDL_Delay(500);
                    }
                    update(berie, time, speedUp, level, types, score);
                }
                else{
                    pauseButton.on=false;
                    continueButton.on=true;
                    if (currentKeyStates[SDL_SCANCODE_C]) continueButton.clicked=true;
                    if (continueButton.clicked){
                        pauseButton.clicked=false;
                        continueButton.clicked=false;
                    }
                    graphics.renderUI(continueButton.buttonTexture, continueButton.posX, continueButton.posY, continueButton.texX, continueButton.texY, SMALL_BUTTON_W, BUTTON_H);
                    graphics.present();
                }
                frameTime=SDL_GetTicks()-frameStart;
                if (FRAME_DELAY>frameTime) SDL_Delay(FRAME_DELAY-frameTime);
            }
            Play=false;
        }
        if (Lose){
            graphics.renderSprite(berie.posX, berie.posY, berie.dead);
            text.renderScore(graphics, score, highScore);
            graphics.renderTexture(text.loseText, LOSE_TEXT_POS_X, LOSE_TEXT_POS_Y);
            graphics.renderTexture(text.scoreText, L_SCORE_TEXT_POS_X, L_SCORE_TEXT_POS_Y);
            if (score>highScore){
                updateHighScore("highScore.txt", score, highScore);
                graphics.renderTexture(text.newHighScoreText, NEW_HS_TEXT_POS_X, L_SCORE_TEXT_POS_Y);
            }
            else{
                graphics.renderTexture(text.yourScoreText, L_YS_TEXT_POS_X, L_SCORE_TEXT_POS_Y);
            }
            bool selectOption=true;
            while (selectOption){
                workOnLoseSelection(graphics, mainMenuButton, restartButton, gameOverButton, berie, castle, bird, crab, water, selectOption, Menu, Play, quit);
                while (SDL_PollEvent(&event)){
                    if (event.type==SDL_QUIT){
                        quit=true;
                        selectOption=false;
                    }
                    handleMainMenuButton(graphics, &event, mainMenuButton, sound);
                    handleRestartButton(graphics, &event, restartButton, sound);
                    handleGameOverButton(graphics, &event, gameOverButton, sound);
                }
                graphics.present();
                SDL_Delay(100);
            }
            SDL_DestroyTexture(text.scoreText); text.scoreText=nullptr;
            SDL_DestroyTexture(text.highScoreText); text.highScoreText=nullptr;
            Lose=false;
        }
    }
    graphics.quit();
    return 0;
}
