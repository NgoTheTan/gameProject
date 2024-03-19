#ifndef _LOGIC__H
#define _LOGIC__H
#include "defs.h"
#include "graphics.h"
struct Mouse {
    int x, y;
    void jump();
    void fall();
};

void render(const Mouse& mouse, const Graphics& graphics);
bool gameOver(const Mouse& mouse);

#endif // _LOGIC__H
