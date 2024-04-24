#ifndef _DEFS__H
#define _DEFS__H
#define WINDOW_TITLE "Chaotic Beach!"
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

#define GROUND_FILE "assets//image//sand.png"
#define LAYER_1_FILE "assets//image//sky.png"
#define LAYER_2_FILE "assets//image//small_clouds.png"
#define LAYER_3_FILE "assets//image//med_clouds.png"
#define LAYER_4_FILE "assets//image//big_clouds.png"

#define BERIE_FILE "assets//image//berie.png"

#define SPPED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

const float BASE_SPEED=0;
const float GROUND_SPEED=5.0;
const float LAYER_1_SPEED=0;
const float LAYER_2_SPEED=1.0;
const float LAYER_3_SPEED=1.5;
const float LAYER_4_SPEED=2.0;
const float LEVEL[]={0.0,1.5,3.0,4.5,6.0,8.0};

const int GROUND=415;
const int MAX_HEIGHT=175;
const int BASE=80;
const int CHAR_HEIGHT=76;
const int CHAR_WIDTH=65;
const int JUMP_SPEED=6;
const int FALL_SPEED=6;

const int FPS=40;
const int FRAME_DELAY=1000/FPS;
const int FRAME_RATE=5;
const int RUN_CLIPS[][4]={{95,0,65,76},{190, 0, 65, 76},{285,0,65,76},{384,0,65,76},{480,0,65,76},{577,0,65,76}};
const int JUMP_CLIPS[][4]={{673,0,65,76},{767,0,65,76},{767,0,65,76},{865,0,65,76},{865,0,65,76},{865,0,65,76},{961,0,65,76},{961,0,65,76}};
const int FALL_CLIPS[][4]={{1055,0,65,76},{1055,0,65,76},{1152,0,65,76},{1152,0,65,76},{1152,0,65,76},{1152,0,65,76},{1242,0,65,76},{1343,0,65,76}};

const int RUN_FRAMES=sizeof(RUN_CLIPS)/sizeof(int)/4;
const int JUMP_FRAMES=sizeof(JUMP_CLIPS)/sizeof(int)/4;
const int FALL_FRAMES=sizeof(FALL_CLIPS)/sizeof(int)/4;
#endif // _DEFS__H
