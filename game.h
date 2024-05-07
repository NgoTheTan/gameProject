#ifndef _GAME__H
#define _GAME__H
#include "logic.h"
int getHighScore(const string path);
void updateHighScore(const string path, const int score, int &highScore);
void handleBackButton(Graphics &graphics, SDL_Event *event, Button &backButton, Sound &sound);
void handlePlayButton (Graphics &graphics, SDL_Event *event, Button &playButton, Sound &sound);
void handleInfoButton (Graphics &graphics, SDL_Event *event, Button &infoButton, Sound &sound);
void handleCreditButton (Graphics &graphics, SDL_Event *event, Button &creditButton,Sound &sound);
void handleQuitButton (Graphics& graphics, SDL_Event *event, Button &quitButton,Sound &sound);
void handleMainMenuButton(Graphics& graphics, SDL_Event *event, Button &mainMenuButton, Sound &sound);
void handleGameOverButton(Graphics& graphics, SDL_Event *event, Button &gameOverButton, Sound &sound);
void handleRestartButton(Graphics &graphics, SDL_Event *event, Button &restartButton, Sound &sound);
void handlePauseButton (Graphics &graphics, SDL_Event *event, Button &pauseButton, Sound &sound);
void handleContinueButton(Graphics &graphics, SDL_Event *event, Button &continueButton, Sound &sound);
void workOnMenu(Graphics &graphics,SDL_Texture* menu, SDL_Texture* info, SDL_Texture* credit, Text &text, Button &playButton, Button &infoButton, Button &creditButton, Button &quitButton,
                Button &backButton, bool &inMenu, bool &inInfo, bool &inCredit, bool& quitMenu, bool &Play, bool& quit);
void intro(Graphics &graphics, SDL_Texture* intro1, SDL_Texture* intro2, SDL_Texture* intro3, SDL_Texture* intro4, Sound &sound);
void workOnLoseSelection(Graphics &graphics, Button &mainMenuButton, Button &restartButton, Button &gameOverButton, Character &berie,
                         Obstacle& castle, Obstacle &bird, Obstacle&crab, Obstacle& water, bool &selectOption, bool &Menu, bool &Play, bool &quit);
void loseScene(Graphics &graphics, const Character berie, ParallaxBackground &background, SDL_Texture* lose1, SDL_Texture* lose2, SDL_Texture* lose3, SDL_Texture* lose4,SDL_Texture* lose5,
                SDL_Texture* lose6, SDL_Texture* lose7, SDL_Texture* lose8, SDL_Texture* lose9, SDL_Texture* lose10, SDL_Texture* lose11, SDL_Texture* lose12, SDL_Texture* lose13, Sound& sound);
void generateObstacles(const Character berie, Graphics &graphics, Obstacle &castle, Obstacle &bird, Obstacle &crab, Obstacle &water, const int speedUp, const int types, const int level);
void obstacleCollision(Graphics& graphics, Sound &sound, Character &berie, Obstacle &castle, Obstacle &bird, Obstacle &crab, Obstacle &water, int &score, const int level);
void characterAction(Graphics& graphics, Character &berie, bool &quitPlay, bool &Lose);
void UI(Graphics& graphics, const Character berie, SDL_Texture* barTexture, Text& text, const int score, const int highScore);
void update(const Character berie, int &time, int &speedUp,int &level, int &types, int &score);
#endif // _GAME__H
