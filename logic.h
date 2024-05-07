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

#define SMALL_BUTTON 0
#define MED_BUTTON 1
#define BIG_BUTTON 2
#define HUGE_BUTTON 3

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
    void Move();
    void playDead();
    void attack();
    void revive();
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
    void reset();
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

struct Sound
{
    Mix_Music *gMusic;
    Mix_Music *mMusic;
    Mix_Music *lMusic;
    Mix_Chunk *earthquake;
    Mix_Chunk *tsunami;
    Mix_Chunk *terrify;
    Mix_Chunk *run;
    Mix_Chunk *gJump;
    Mix_Chunk *gCollect;
    Mix_Chunk *gAttack;
    Mix_Chunk *waterSplash;
    Mix_Chunk *shootWater;
    Mix_Chunk *birdSound;
    Mix_Chunk *deadSound;
    Mix_Chunk *yaySound;
    Mix_Chunk *clickSound;
    Mix_Chunk *drowning;
    Sound(Graphics& graphics);
};
struct Text
{
    TTF_Font* font;
    SDL_Color color={0,0,0,255};
    SDL_Texture* yourScoreText;
    SDL_Texture* bestText;
    SDL_Texture* scoreText;
    SDL_Texture* highScoreText;
    SDL_Texture* loseText;
    SDL_Texture* newHighScoreText;
    Text(Graphics &graphics);
    void renderScore(Graphics &graphics, const int score, const int highScore);
};
struct Button
{
    bool clicked, on;
    SDL_Texture* buttonTexture;
    int posX, posY, texX, texY;
    Button(SDL_Texture* texture, int _posX, int _posY, int _texX, int _texY);
    bool underMouse(SDL_Event *event, const int buttonSize);
};

bool checkCollision(int leftA, int rightA, int topA, int botA, int leftB, int rightB, int topB, int botB);
bool checkHitObstacle(const Bullet* bullet,const SDL_Rect* bullet_clip, const Obstacle obstacle, const SDL_Rect* obstacle_clip);
void shooting(vector<Bullet*> &bullets, Graphics &graphics, Obstacle& castle, Obstacle& bird, const int accel, int& score, Sound& sound, const int level);


bool checkObstacleCollision(const Character character, const Obstacle obstacle, const SDL_Rect* obstacle_clip);
void checkOveride(Obstacle &castle, Obstacle &bird, Obstacle &crab, Obstacle& water);

#endif // _LOGIC__H
