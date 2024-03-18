#ifndef _LOGIC__H
#define _LOGIC__H
#include "graphics.h"
#define STEP 5
struct Mouse {
    int x, y;
    int move=STEP;
    void left();
    void right();
    void up();
    void down();
};

void render(const Mouse& mouse, const Graphics& graphics);
bool gameOver(const Mouse& mouse);

#endif
