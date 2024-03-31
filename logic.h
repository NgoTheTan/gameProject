#ifndef _LOGIC__H
#define _LOGIC__H
#include "defs.h"
#include "graphics.h"
struct Mouse {
    int x, y;
    int move=STEP;
    void left();
    void right();
    void up();
    void down();
};
bool gameOver(const Mouse& mouse);
#endif // _LOGIC__H
