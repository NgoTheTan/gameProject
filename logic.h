#ifndef _LOGIC__H
#define _LOGIC__H

#include "graphics.h"

#define JUMP 1
#define FALL 2
#define RUN 0

struct Character
{
    int posX, posY;
    int h, w;
    int status;
    Sprite run;
    Sprite jump, fall;
    Sprite getGun;
    Sprite runWithGun;
    Sprite jumpWithGun, fallWithGun;
    Sprite damaged;
    void init(SDL_Texture* texture);
    bool running();
    bool jumping();
    bool falling();
    void Move();
};

#endif // _LOGIC__H
