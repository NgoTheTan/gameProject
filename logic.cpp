#include "logic.h"
#include <bits/stdc++.h>
#include "graphics.h"
void Mouse::left()
{
    y=y; x-=move;
}
void Mouse::right()
{
    y=y; x+=move;
}
void Mouse::up()
{
    y-=move; x=x;
}
void Mouse::down()
{
    y+=move; x=x;
}
void render(const Mouse& mouse, const Graphics& graphics)
{
    SDL_Rect filled_rect;
    filled_rect.x = mouse.x;
    filled_rect.y = mouse.y;
    filled_rect.w = 10;
    filled_rect.h = 10;
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(graphics.renderer, &filled_rect);
}

bool gameOver(const Mouse& mouse) {
    return mouse.x < 0 || mouse.x >= SCREEN_WIDTH ||
           mouse.y < 0 || mouse.y >= SCREEN_HEIGHT;
}

