#ifndef _GAME__H
#define _GAME__H
#include "logic.h"
void waitUntilKeyPressed();
//void handleBackButton( SDL_Event* event, Button &backButton, bool &inMenu,bool &current, Sound &sound);
//void handlePlayButton(SDL_Event* event, Button &playButton, bool &Menu, bool &Play,bool &quitMenu, Sound &sound);
//void handleInfoButton( SDL_Event *event, Button &infoButton, bool &inInfo, bool &inMenu, Sound &sound);
//void handleCreditButton( SDL_Event *event, Button &creditButton, bool &inCredit, bool &inMenu, Sound &sound);
//void handleQuitButton( SDL_Event* event, Button &quitButton, bool &quit, Sound &sound);
void action(Graphics& graphics, ParallaxBackground& background, Sound &sound, Character &berie, Obstacle &castle, Obstacle &bird, Obstacle &crab,
            Obstacle &water, vector<Bullet*> &bullets, const int speedUp, const int types, const int level, int& score, bool &quit);
void HUD(Graphics& graphics, const Character berie, SDL_Texture* barTexture, Text& text, const int score, const int highScore);
void update(int &time, int &speedUp,int &level, int &types, int &score);
void destroyBackground(ParallaxBackground& background);
void destroyChar(Character& character);
void destroyObs(Obstacle& castle, Obstacle& bird, Obstacle& crab, Obstacle& water);
void destroySoundAndText(Sound &sound, Text &text);
#endif // _GAME__H
