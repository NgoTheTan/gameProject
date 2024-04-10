#ifndef _DEFS__H
#define _DEFS__H
#define WINDOW_TITLE "GameProject"
#define STEP 10
const int SCREEN_WIDTH = 1536;
const int SCREEN_HEIGHT = 795;

#define MAN_SPRITE_FILE "assets//image//character.png"
const int FRONT_CLIPS[][4] = {
    {  0, 0, 64, 64},
    { 64, 0, 64, 64},
    {128, 0, 64, 64},
    {192, 0, 64, 64}
};
const int LEFT_CLIPS[][4] = {
    {  0, 64, 64, 64},
    { 64, 64, 64, 64},
    {128, 64, 64, 64},
    {192, 64, 64, 64}
};
const int RIGHT_CLIPS[][4] = {
    {  0, 128, 64, 64},
    { 64, 128, 64, 64},
    {128, 128, 64, 64},
    {192, 128, 64, 64}
};
const int BACK_CLIPS[][4] = {
    {  0, 192, 64, 64},
    { 64, 192, 64, 64},
    {128, 192, 64, 64},
    {192, 192, 64, 64}
};
const int STAND_STILL[4][4] = {
    {0, 0, 64, 64},
    {0, 64, 64, 64},
    {0, 128, 64, 64},
    {0, 192, 64, 64}
};
const int FRONT_FRAMES = sizeof(FRONT_CLIPS)/sizeof(int)/4;
const int BACK_FRAMES = sizeof(BACK_CLIPS)/sizeof(int)/4;
const int RIGHT_FRAMES = sizeof(RIGHT_CLIPS)/sizeof(int)/4;
const int LEFT_FRAMES = sizeof(LEFT_CLIPS)/sizeof(int)/4;
const int STAND_FRAMES = sizeof(STAND_STILL)/sizeof(int)/4;
#endif // _DEFS__H
