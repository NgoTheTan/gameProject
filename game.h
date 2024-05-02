#ifndef _GAME__H
#define _GAME__H
#include "logic.h"
void waitUntilKeyPressed();
void handleBackButton(Graphics &graphics, SDL_Event *event, Button &backButton, Sound &sound);
void handlePlayButton (Graphics &graphics, SDL_Event *event, Button &playButton, Sound &sound);
void handleInfoButton (Graphics &graphics, SDL_Event *event, Button &infoButton, Sound &sound);
void handleCreditButton (Graphics &graphics, SDL_Event *event, Button &creditButton,Sound &sound);
void handleQuitButton (Graphics& graphics, SDL_Event *event, Button &quitButton,Sound &sound);
void action(Graphics& graphics, ParallaxBackground& background, Sound &sound, Character &berie, Obstacle &castle, Obstacle &bird, Obstacle &crab,
            Obstacle &water, vector<Bullet*> &bullets, const int speedUp, const int types, const int level, int& score, bool &quit);
void HUD(Graphics& graphics, const Character berie, SDL_Texture* barTexture, Text& text, const int score, const int highScore);
void update(int &time, int &speedUp,int &level, int &types, int &score);
void destroyBackground(ParallaxBackground& background);
void destroyChar(Character& character);
void destroyObs(Obstacle& castle, Obstacle& bird, Obstacle& crab, Obstacle& water);
void destroySoundAndText(Sound &sound, Text &text);
#endif // _GAME__H
