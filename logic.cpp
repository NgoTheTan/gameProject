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
bool gameOver(const Mouse& mouse) {
    return mouse.x < 0 || mouse.x >= SCREEN_WIDTH ||
           mouse.y < 0 || mouse.y >= SCREEN_HEIGHT;
}

