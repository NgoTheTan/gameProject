#include "logic.h"

Character::Character(SDL_Texture* texture)
{
    posX=BASE, posY=GROUND;
    status=RUN;
    reload=150;
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
void Character::revive()
{
    posX=BASE, posY=GROUND;
    status=RUN;
    reload=150;
    gun=false;
    energy=BASE_ENERGY; power=0;
    run.currentFrame=0;
    jump.currentFrame=0;
    fall.currentFrame=0;
    dead.currentFrame=0;
    headbutt.currentFrame=0;
    getGun.currentFrame=0;
    runWithGun.currentFrame=0;
    jumpWithGun.currentFrame=0;
    fallWithGun.currentFrame=0;
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
	if (reload<150) reload+=10;
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
        posY=GROUND+(CHAR_HEIGHT-foe.getCurrentClip()->h);
    }
    else if (type==CASTLE){
        foe.init(enemy, CASTLES, CASTLE_TYPES);
    }
}
void Obstacle::reset()
{
    posX=-200;
    dead=false;
    vanish.currentFrame=0;
    foe.currentFrame=0;
    collect.currentFrame=0;
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
            posX=rand()%(SCREEN_WIDTH+BIRD_POS_RANGE)+SCREEN_WIDTH;
            posY=rand()%(MIN_HEIGHT-MAX_HEIGHT+1)+MAX_HEIGHT;
        }
        else if (type==CRAB){
            posX=rand()%(SCREEN_WIDTH+CRAB_POS_RANGE)+SCREEN_WIDTH+CRAB_POS_RANGE;
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
    posX=BASE+10; posY=height;
    splash.init(effect, SPLASH_FRAMES, SPLASH_CLIPS);
    shoot.init(bullet, SHOOT_FRAMES, SHOOT_CLIPS);
}
void Bullet::Move()
{
    posX+=10;
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

Sound::Sound(Graphics& graphics)
{
    gMusic=graphics.loadMusic("assets//sound//gameMusic.mp3");
    mMusic=graphics.loadMusic("assets//sound//menuMusic.mp3");

    earthquake=graphics.loadSound("assets//sound//earthquake.wav");
    tsunami=graphics.loadSound("assets//sound//tsunami.wav");
    terrify=graphics.loadSound("assets//sound//terrify.wav");
    run=graphics.loadSound("assets//sound//run.wav");

    clickSound=graphics.loadSound("assets//sound//click.wav");
    gJump=graphics.loadSound("assets//sound//jump.wav");
    gCollect=graphics.loadSound("assets//sound//collect.wav");
    gAttack=graphics.loadSound("assets//sound//attack.wav");
    waterSplash=graphics.loadSound("assets//sound//splash.wav");
    shootWater=graphics.loadSound("assets//sound//shoot.wav");
    birdSound=graphics.loadSound("assets//sound//bird.wav");
    deadSound=graphics.loadSound("assets//sound//dead.wav");
    yaySound=graphics.loadSound("assets//sound//yay.wav");

}
Text::Text(Graphics &graphics)
{
    font=graphics.loadFont("assets//font//Silver.ttf",48);
    yourScoreText=graphics.renderText("YOUR SCORE ", font, color);
    bestText=graphics.renderText("BEST ", font, color);
    newHighScoreText=graphics.renderText("NEW HIGHSCORE", font, color);
    loseText=graphics.renderText("DROWNED!", font, color);
}
void Text::renderScore(Graphics &graphics, const int score, const int highScore)
{
    scoreText=graphics.renderText(to_string(score), font, color);
    highScoreText=graphics.renderText(to_string(highScore), font, color);
}
Button::Button(Graphics &graphics, int _posX, int _posY, int _texX, int _texY)
{
    clicked=false, on=false;
    posX=_posX; posY=_posY; texX=_texX; texY=_texY;
    buttonTexture=graphics.loadTexture("assets//image//button.png");
}
bool Button::underMouse(SDL_Event* event, const int buttonSize)
{
    if (event->type==SDL_MOUSEMOTION || event->type==SDL_MOUSEBUTTONDOWN || event->type==SDL_MOUSEBUTTONUP){
        int x, y;
        int button_h=BUTTON_H, button_w;
        if (buttonSize==SMALL_BUTTON){
            button_w=SMALL_BUTTON_W;
        }
        else if (buttonSize==MED_BUTTON){
            button_w=MED_BUTTON_W;
        }
        else if (buttonSize==BIG_BUTTON){
            button_w=BIG_BUTTON_W;
        }
        else{
            button_w=HUGE_BUTTON_W;
        }
        SDL_GetMouseState(&x, &y);
        bool under=true;
        if (x<posX) under=false;
        else if (x>posX+button_w) under=false;
        else if (y<posY) under=false;
        else if (y>posY+button_h) under=false;
        return under;
    }
    return false;
}
int getHighScore(const string path)
{
    fstream highScoreFile(path);
    string high;
    highScoreFile >> high;
    int highScore;
    stringstream convertToInt(high);
    convertToInt >> highScore;
    return highScore;
}
void updateHighScore(const string path, const int score, int &highScore)
{
    fstream highScoreFile;
    highScoreFile.open(path, ios::out);
    string newHighScore;
    if (score>highScore){
        highScore=score;
    }
    newHighScore=to_string(highScore);
    highScoreFile << newHighScore;
}
void shooting(vector<Bullet*> &bullets, Graphics& graphics, Obstacle &castle, Obstacle& bird, const int accel, int& score, Sound &sound, const int level)
{
    for (int i=0; i<bullets.size(); i++){
        Bullet* bullet=bullets[i];
        if (checkHitObstacle(bullet, bullet->shoot.getCurrentClip(), castle, castle.foe.getCurrentClip()) && !castle.dead && !bullet->hit){
            score+=(20+level*SCORE_MULTIPLIER);
            bullet->hit=true;
            castle.dead=true;
            graphics.playSound(sound.waterSplash);
        }
        if (checkHitObstacle(bullet,bullet->shoot.getCurrentClip(), bird, bird.foe.getCurrentClip()) && !bird.dead && !bullet->hit){
            score+=(50+level*SCORE_MULTIPLIER);
            bullet->hit=true;
            bird.dead=true;
            graphics.playSound(sound.birdSound);
            graphics.playSound(sound.waterSplash);
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
    int leftA=castle.posX-OVERRIDE_RANGE, rightA=castle.posX+castle.foe.getCurrentClip()->w+OVERRIDE_RANGE;
    int leftB=bird.posX-OVERRIDE_RANGE, rightB=bird.posX+bird.foe.getCurrentClip()->w+OVERRIDE_RANGE;
    int leftC=crab.posX-OVERRIDE_RANGE, rightC=crab.posX+crab.foe.getCurrentClip()->w+OVERRIDE_RANGE;
    int leftD=water.posX-OVERRIDE_RANGE, rightD=water.posX+water.collect.getCurrentClip()->w+OVERRIDE_RANGE;
    if (leftC<=leftA && rightC>=leftA) crab.posX-=castle.foe.getCurrentClip()->w;
    else if ((leftC>=leftA && rightC<=rightA) || (leftC<=rightA && rightC>=rightA)) crab.posX+=castle.foe.getCurrentClip()->w;
    if (leftB<=leftA && rightB>=leftA) bird.posX-=castle.foe.getCurrentClip()->w;
    else if ((leftB>=leftA && rightB<=rightA) || (leftB<=rightA && rightB>=rightA)) bird.posX+=castle.foe.getCurrentClip()->w;
    if (leftC<=leftB && rightC>=leftB) crab.posX-=(bird.foe.getCurrentClip()->w);
    else if ((leftC>=leftB && rightC<=rightB) || (leftC<=rightB && rightC>=rightB)) crab.posX+=bird.foe.getCurrentClip()->w;
    if (leftD<=leftB && rightD>=leftB) water.posX-=(bird.foe.getCurrentClip()->w);
    else if ((leftD>=leftB && rightD<=rightB) || (leftD<=rightB && rightD>=rightB)) water.posX+=bird.foe.getCurrentClip()->w;
}
