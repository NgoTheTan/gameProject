#include "logic.h"

void Character::init(SDL_Texture* texture)
{
    posX=BASE, posY=GROUND;
    h=CHAR_HEIGHT, w=CHAR_WIDTH;
    status=RUN;
    run.init(texture, RUN_FRAMES, RUN_CLIPS);
    jump.init(texture, JUMP_FRAMES, JUMP_CLIPS);
    fall.init(texture, FALL_FRAMES, FALL_CLIPS);
}
bool Character::running()
{
    return posY==GROUND;
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
}
