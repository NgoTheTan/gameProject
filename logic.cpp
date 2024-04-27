#include "logic.h"

Character::Character(SDL_Texture* texture)
{
    posX=BASE, posY=GROUND;
    status=RUN;
    run.init(texture, RUN_FRAMES, RUN_CLIPS);
    jump.init(texture, JUMP_FRAMES, JUMP_CLIPS);
    fall.init(texture, FALL_FRAMES, FALL_CLIPS);
    dead.init(texture, DEAD_FRAMES, DEAD_CLIPS);
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

Obstacle::Obstacle(SDL_Texture* texture, int _type)
{
    posX=-200; posY=-200;
    type=_type;
    if (type==BIRD){
        foe.init(texture, BIRD_FRAMES, BIRD_CLIPS);
        posY=rand()%(MAX_HEIGHT-MIN_HEIGHT+1)+MAX_HEIGHT;
    }
    else if (type==CRAB){
        foe.init(texture, CRAB_FRAMES, CRAB_CLIPS);
        posY=GROUND+(CHAR_HEIGHT-foe.getCurrentClip()->h);
    }
    else if (type==CASTLE){
        foe.init(texture, CASTLES, CASTLE_TYPES);
    }
}
void Obstacle::Move(int accel, int types)
{
    posX-=(GROUND_SPEED+accel);
    if (posX+foe.getCurrentClip()->w <0){
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
bool checkCollision(int leftA, int rightA, int topA, int botA, int leftB, int rightB, int topB, int botB)
{
    if (botA<=topB) return false;
    if (topA>=botB) return false;
    if (rightA<=leftB) return false;
    if (leftA>=rightB) return false;
    return true;
}

bool checkEnemyCollision(Character character, SDL_Rect* char_clip, Obstacle enemy, SDL_Rect* enemy_clip)
{
    int leftA=character.posX, rightA=character.posX+CHAR_WIDTH, topA=character.posY, botA=character.posY+CHAR_HEIGHT;
    int leftB=enemy.posX, rightB=enemy.posX+enemy_clip->w, topB=enemy.posY, botB=enemy.posY+enemy_clip->h;
    return checkCollision(leftA, rightA, topA, botA, leftB, rightB, topB, botB);
}



