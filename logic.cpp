#include "logic.h"
#include <bits/stdc++.h>

bool inside(int x, int y, SDL_Rect r) {
    return x > r.x && x < r.x+r.w && y > r.y && y < r.y+r.h;
}

bool overlap(const SDL_Rect& r1, const SDL_Rect& r2) {
    return inside(r1.x, r1.y, r2) || inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}

Cheese::Cheese(int x, int y)
{
    rect.x=x;
    rect.y=y;
    rect.w=CHEESE_SIZE;
    rect.h=CHEESE_SIZE;
}

Mouse::Mouse(int x, int y)
{
    rect.x=x;
    rect.y=y;
    rect.h=SPRITE_HEIGHT;
    rect.w=SPRITE_WIDTH;
}

bool Mouse::canEat(const Cheese& cheese) {
        return overlap(rect, cheese.rect);
}

void Mouse::left()
{
    rect.x-=move;
}
void Mouse::right()
{
    rect.x+=move;
}
void Mouse::up()
{
    rect.y-=move;
}
void Mouse::down()
{
    rect.y+=move;
}

void render(const Cheese& cheese, const Graphics& graphics) {
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(graphics.renderer, &cheese.rect);
}
bool gameOver(const Mouse& mouse) {
    return mouse.rect.x < 0 || mouse.rect.x+mouse.rect.w >= SCREEN_WIDTH ||
           mouse.rect.y < 0 || mouse.rect.y+mouse.rect.h >= SCREEN_HEIGHT;
}

