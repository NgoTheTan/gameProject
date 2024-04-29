#ifndef _LOGIC__H
#define _LOGIC__H

#include "graphics.h"
#include <ctime>
#include <cstdlib>
#define ATTACK 5
#define JUMP 3
#define FALL 2
#define RUN 1
#define DEAD 4


#define CRAB 2
#define BIRD 1
#define CASTLE 0

struct Character
{
    int posX, posY;
    int status;
    bool gun;
    int reload;
    int energy, power;
    Sprite run;
    Sprite jump, fall;
    Sprite headbutt;
    Sprite getGun;
    Sprite runWithGun;
    Sprite jumpWithGun, fallWithGun;
    Sprite dead;
    Character(SDL_Texture* texture);
    bool running();
    bool jumping();
    bool falling();
    bool attacking();
    bool damaged();
    void Move();
    void playDead();
    void attack();
};

struct Obstacle
{
    int posX, posY;
    int type;
    bool dead;
    Sprite foe;
    Sprite vanish;
    Sprite collect;
    Obstacle(SDL_Texture* enemy, SDL_Texture* effect, int _type);
    Obstacle (SDL_Texture* collectable);
    void Move(const int accel, const int types);
    void spawn(const int accel);
};

struct Bullet
{
    int posX, posY;
    bool hit, render;
    Sprite shoot, splash;
    Bullet(SDL_Texture* bullet, SDL_Texture* effect, int height);
    ~Bullet();
    void Move();
    void delay(const int accel);
};

bool checkCollision(int leftA, int rightA, int topA, int botA, int leftB, int rightB, int topB, int botB);
bool checkHitObstacle(const Bullet* bullet,const SDL_Rect* bullet_clip, const Obstacle obstacle, const SDL_Rect* obstacle_clip);
void shooting(vector<Bullet*> &bullets, Graphics &graphics, Obstacle& castle, Obstacle& bird, const int accel);


bool checkObstacleCollision(const Character character, const Obstacle obstacle, const SDL_Rect* obstacle_clip);
void checkOveride(Obstacle &castle, Obstacle &bird, Obstacle &crab, Obstacle& water);
void destroyBackground(ParallaxBackground& background);
void destroyChar(Character& character);
void destroyObs(Obstacle& castle, Obstacle& bird, Obstacle& crab, Obstacle& water);
#endif // _LOGIC__H
