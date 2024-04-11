#ifndef _LOGIC__H
#define _LOGIC__H
#include "defs.h"
#include "graphics.h"

bool inside(int x, int y, SDL_Rect r);
bool overlap(const SDL_Rect& r1, const SDL_Rect& r2);

struct Cheese {
    SDL_Rect rect;
    bool eaten=false;
    Cheese(int x, int y);
};

struct Mouse {
    SDL_Rect rect;
    int move=STEP;
    Mouse(int x, int y);
    bool canEat(const Cheese& cheese);
    void left();
    void right();
    void up();
    void down();
};
void render(const Cheese& cheese, const Graphics& graphics);
bool gameOver(const Mouse& mouse);
#endif // _LOGIC__H
