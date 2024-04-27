#ifndef _LOGIC__H
#define _LOGIC__H

#include "graphics.h"
#include <ctime>
#include <cstdlib>
#define JUMP 3
#define FALL 2
#define RUN 1
#define DEAD 0


#define CRAB 2
#define BIRD 1
#define CASTLE 0

#define PILL 1
#define WATER 0
struct Character
{
    int posX, posY;
    int status;
    Sprite run;
    Sprite jump, fall;
    Sprite getGun;
    Sprite runWithGun;
    Sprite jumpWithGun, fallWithGun;
    Sprite dead;
    Character(SDL_Texture* texture);
    bool running();
    bool jumping();
    bool falling();
    bool damaged();
    void Move();
    void playDead();
};

struct Obstacle
{
    int posX, posY;
    int type;
    Sprite foe;
    Obstacle(SDL_Texture* texture, int _type);
    void Move(int accel, int types);
};

bool checkCollision(int leftA, int rightA, int topA, int botA, int leftB, int rightB, int topB, int botB);
bool checkEnemyCollision(Character character, SDL_Rect* char_clip, Obstacle enemy, SDL_Rect* enemy_clip);
#endif // _LOGIC__H
