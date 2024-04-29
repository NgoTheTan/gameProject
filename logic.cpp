#include "logic.h"

Character::Character(SDL_Texture* texture)
{
    posX=BASE, posY=GROUND;
    status=RUN;
    reload=100;
    gun=false;
    energy=BASE_ENERGY; power=0;
    run.init(texture, RUN_FRAMES, RUN_CLIPS);
    jump.init(texture, JUMP_FRAMES, JUMP_CLIPS);
    fall.init(texture, FALL_FRAMES, FALL_CLIPS);
    dead.init(texture, DEAD_FRAMES, DEAD_CLIPS);
    headbutt.init(texture, HEADBUTT_FRAMES, HEADBUTT_CLIPS);
    getGun.init(texture, GETGUN_FRAMES, GETGUN_CLIPS);
    runWithGun.init(texture, RUN_FRAMES, RUN_W_GUN_CLIPS);
    jumpWithGun.init(texture, JUMP_FRAMES, JUMP_W_GUN_CLIPS);
    fallWithGun.init(texture, FALL_FRAMES, FALL_W_GUN_CLIPS);
}
bool Character::running()
{
    if(status==RUN) return true;
    return false;
}
bool Character::jumping()
{
    if (status==JUMP) return true;
    return false;
}
bool Character::falling()
{
    if (status==FALL) return true;
    return false;
}
bool Character::damaged()
{
    if (status==DEAD) return true;
    return false;
}
bool Character::attacking()
{
    if (status==ATTACK) return true;
    return false;
}
void Character::Move()
{
	if (status==JUMP && posY>=MAX_HEIGHT)
	{
		posY+=-JUMP_SPEED;
	}
	if (posY<=MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status==FALL && posY<GROUND)
	{
		posY += FALL_SPEED;
	}
	if (posY==GROUND) status=RUN;
	if (energy<BASE_ENERGY) energy+=ENERGY_GAIN;
	if (power==MAX_POWER){
        gun=true;
        runWithGun.currentFrame=run.currentFrame;
        jumpWithGun.currentFrame=jump.currentFrame;
        fallWithGun.currentFrame=fall.currentFrame;
	}
	if (power>0 && gun){
        power-=POWER_LOST;
        if (power==0){
            gun=false;
            run.currentFrame=runWithGun.currentFrame;
            jump.currentFrame=jumpWithGun.currentFrame;
            fall.currentFrame=fallWithGun.currentFrame;
        }
	}
	if (reload<100) reload+=10;
}
void Character::playDead()
{
    if (posY<GROUND){
        posY+=FALL_SPEED;
    }
    if (posY>GROUND){
        posY=GROUND;
    }
    posX+=DEAD_SPEED;
}
void Character::attack()
{
    energy-=ENERGY_LOST;
    if (energy<=0){
        status=RUN;
    }
}

Obstacle::Obstacle(SDL_Texture* enemy, SDL_Texture* effect, int _type)
{
    posX=-200; posY=-200;
    type=_type;
    dead=false;
    vanish.init(effect, VANISH_FRAMES, VANISH_CLIPS);
    if (type==BIRD){
        foe.init(enemy, BIRD_FRAMES, BIRD_CLIPS);
    }
    else if (type==CRAB){
        foe.init(enemy, CRAB_FRAMES, CRAB_CLIPS);
    }
    else if (type==CASTLE){
        foe.init(enemy, CASTLES, CASTLE_TYPES);
    }
}
Obstacle::Obstacle(SDL_Texture* collectable)
{
    dead=false;
    collect.init(collectable, BALL_FRAMES, BALL_CLIPS);
    posX=-100; posY=250;
}
void Obstacle::Move(const int accel, const int types)
{
    posX-=(GROUND_SPEED+accel);
    if (posX+foe.getCurrentClip()->w <0){
        dead=false;
        vanish.currentFrame=0;
        if (type==BIRD){
            posX=rand()%(SCREEN_WIDTH+BIRD_POS_RANGE+1)+SCREEN_WIDTH;
            posY=rand()%(MIN_HEIGHT-MAX_HEIGHT+1)+MAX_HEIGHT;
        }
        else if (type==CRAB){
            posX=rand()%(SCREEN_WIDTH+CRAB_POS_RANGE)+SCREEN_WIDTH;
        }
        else if (type==CASTLE){
            posX=rand()%(SCREEN_WIDTH+CASTLE_POS_RANGE)+SCREEN_WIDTH;
            foe.currentFrame=(rand()%types)*FRAME_RATE;
            posY=GROUND+(CHAR_HEIGHT-foe.getCurrentClip()->h)+5;
        }
    }
}
void Obstacle::spawn(const int accel)
{
    posX-=(GROUND_SPEED+accel);
    if (posX+collect.getCurrentClip()->w<0){
        dead=false;
        posX=rand()%(SCREEN_WIDTH+COLLECT_POS_RANGE)+SCREEN_WIDTH;
    }
}

Bullet::Bullet(SDL_Texture* bullet, SDL_Texture* effect, int height)
{
    hit=false; render=true;
    posX=BASE+CHAR_WIDTH-15; posY=height;
    splash.init(effect, SPLASH_FRAMES, SPLASH_CLIPS);
    shoot.init(bullet, SHOOT_FRAMES, SHOOT_CLIPS);
}
void Bullet::Move()
{
    posX+=BULLET_SPEED;
    if (posX>=SCREEN_WIDTH+30) hit=true;
}
void Bullet::delay(const int accel)
{
    posX-=(GROUND_SPEED+accel);
}
Bullet::~Bullet()
{
    SDL_DestroyTexture(splash.texture); splash.texture=NULL;
    SDL_DestroyTexture(shoot.texture); shoot.texture=NULL;
}
void shooting(vector<Bullet*> &bullets, Graphics& graphics, Obstacle &castle, Obstacle& bird, const int accel)
{
    for (int i=0; i<bullets.size(); i++){
        Bullet* bullet=bullets[i];cerr << bullet->posX << endl;
        if (checkHitObstacle(bullet, bullet->shoot.getCurrentClip(), castle, castle.foe.getCurrentClip()) && !castle.dead && !bullet->hit){
            bullet->hit=true;
            castle.dead=true;
        }
        if (checkHitObstacle(bullet,bullet->shoot.getCurrentClip(), bird, bird.foe.getCurrentClip()) && !bird.dead && !bullet->hit){
            bullet->hit=true;
            bird.dead=true;
        }
        if (!bullet->hit){
            bullet->Move();
            bullet->shoot.tick();
            graphics.renderSprite(bullet->posX+40, bullet->posY, bullet->shoot);
        }
        else if (bullet->hit){
            if (bullet->posX<SCREEN_WIDTH) bullet->delay(accel);
            if (!(bullet->splash.currentFrame==SPLASH_FRAMES*FRAME_RATE-1)){
                bullet->splash.tick();
                graphics.renderSprite(bullet->posX+40, bullet->posY, bullet->splash);
            }
            else{
                bullets.erase(bullets.begin()+i);
                i--;
            }
        }
    }
}

bool checkCollision(int leftA, int rightA, int topA, int botA, int leftB, int rightB, int topB, int botB)
{
    if (botA<=topB) return false;
    if (topA>=botB) return false;
    if (rightA<=leftB) return false;
    if (leftA>=rightB) return false;
    return true;
}

bool checkObstacleCollision(const Character character, const Obstacle obstacle, const SDL_Rect* obstacle_clip)
{
    int leftA=character.posX, rightA=character.posX+CHAR_WIDTH, topA=character.posY+CTRASH_PIXELS, botA=character.posY+CHAR_HEIGHT-CTRASH_PIXELS;
    int leftB=obstacle.posX+OBS_TRASH_PIXELS, rightB=obstacle.posX+obstacle_clip->w-OBS_TRASH_PIXELS, topB=obstacle.posY+OBS_TRASH_PIXELS, botB=obstacle.posY+obstacle_clip->h-OBS_TRASH_PIXELS;
    return checkCollision(leftA, rightA, topA, botA, leftB, rightB, topB, botB);
}

bool checkHitObstacle(const Bullet* bullet, const SDL_Rect* bullet_clip, const Obstacle obstacle, const SDL_Rect* obstacle_clip)
{
    int leftA=bullet->posX;
    int rightA=bullet->posX+bullet_clip->w-OBS_TRASH_PIXELS;
    int topA=bullet->posY+OBS_TRASH_PIXELS;
    int botA=bullet->posY+bullet_clip->h-OBS_TRASH_PIXELS;
    int leftB=obstacle.posX+OBS_TRASH_PIXELS, rightB=obstacle.posX+obstacle_clip->w-OBS_TRASH_PIXELS, topB=obstacle.posY+OBS_TRASH_PIXELS, botB=obstacle.posY+obstacle_clip->h-OBS_TRASH_PIXELS;
    return checkCollision(leftA, rightA, topA, botA, leftB, rightB, topB, botB);
}

void checkOveride(Obstacle &castle, Obstacle &bird, Obstacle &crab, Obstacle &water)
{
    int leftA=castle.posX, rightA=castle.posX+castle.foe.getCurrentClip()->w;
    int leftB=bird.posX, rightB=bird.posX+bird.foe.getCurrentClip()->w;
    int leftC=crab.posX, rightC=crab.posX+crab.foe.getCurrentClip()->w;
    int leftD=water.posX, rightD=water.posX+water.collect.getCurrentClip()->w;
    if (leftC<=leftA && rightC>=leftA) crab.posX-=castle.foe.getCurrentClip()->w;
    else if ((leftC>=leftA && rightC<=rightA) || (leftC<=rightA && rightC>=rightA)) crab.posX+=castle.foe.getCurrentClip()->w;
    if (leftB<=leftA && rightB>=leftA) bird.posX-=castle.foe.getCurrentClip()->w;
    else if ((leftB>=leftA && rightB<=rightA) || (leftB<=rightA && rightB>=rightA)) bird.posX+=castle.foe.getCurrentClip()->w;
    if (leftC<=leftB && rightC>=leftB) crab.posX-=bird.foe.getCurrentClip()->w;
    else if ((leftC>=leftB && rightC<=rightB) || (leftC<=rightB && rightC>=rightB)) crab.posX+=bird.foe.getCurrentClip()->w;
    if (leftD<=leftB && rightD>=leftB) water.posX-=bird.foe.getCurrentClip()->w;
    else if ((leftD>=leftB && rightD<=rightB) || (leftD<=rightB && rightD>=rightB)) water.posX+=bird.foe.getCurrentClip()->w;
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

