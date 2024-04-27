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

#define CASTLES_FILE "assets//image//castles.png"
#define BIRD_FILE "assets//image//bird.png"
#define CRAB_FILE "assets//image//crab.png"

#define SPPED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

const int BASE_SPEED=0;
const int GROUND_SPEED=8;
const int LAYER_1_SPEED=0;
const int LAYER_2_SPEED=1;
const int LAYER_3_SPEED=2;
const int LAYER_4_SPEED=3;
const int TIME_UP=800;
const int MAX_LEVEL=5;
const int ACCEL_PACE=2;
const int SPEED_ACCEL=1;

const int GROUND=415;
const int MAX_HEIGHT=175;
const int BASE=80;
const int JUMP_SPEED=8;
const int FALL_SPEED=8;
const int DEAD_SPEED=2;
const int MIN_HEIGHT=200;
const int CHAR_HEIGHT=76;
const int CHAR_WIDTH=65;
const int BIRD_POS_RANGE=250;
const int CASTLE_POS_RANGE=0;
const int CRAB_POS_RANGE=250;
const int BASE_TYPES=2;
const int MAX_TYPE=5;

const int FPS=50;
const int FRAME_DELAY=1000/FPS;
const int FRAME_RATE=5;
const int FRAME_LOST=2;
const int RUN_CLIPS[][4]={{95,0,65,76},{190, 0, 65, 76},{285,0,65,76},{383,0,65,76},{480,0,65,76},{575,0,65,76}};
const int JUMP_CLIPS[][4]={{672,0,65,76},{767,0,65,76},{864,0,65,76},{864,0,65,76},{864,0,65,76},{960,0,65,76}};
const int FALL_CLIPS[][4]={{1054,0,65,76},{1054,0,65,76},{1151,0,65,76},{1151,0,65,76},{1241,0,65,76},{1342,0,65,76}};
const int DEAD_CLIPS[][4]={{1440,0,65,76},{1530,0,65,76},{1631,0,65,76},{1727,0,65,76},{1828,0,65,76},{1913,0,80,76}};

const int BIRD_CLIPS[][4]={{197,0,61,49},{130,0,62,49},{67,0,60,49},{3,0,62,49}};
const int CASTLE_TYPES[][4]={{1,75,70,75},{74,43,120,107},{198,0,70,150},{273,43,169,107},{447,0,120,150}};
const int CRAB_CLIPS[][4]={{13,109,37,19},{137,109,42,19},{203,109,39,19}};

const int RUN_FRAMES=sizeof(RUN_CLIPS)/sizeof(int)/4;
const int JUMP_FRAMES=sizeof(JUMP_CLIPS)/sizeof(int)/4;
const int FALL_FRAMES=sizeof(FALL_CLIPS)/sizeof(int)/4;
const int DEAD_FRAMES=sizeof(DEAD_CLIPS)/sizeof(int)/4;

const int BIRD_FRAMES=sizeof(BIRD_CLIPS)/sizeof(int)/4;
const int CRAB_FRAMES=sizeof(CRAB_CLIPS)/sizeof(int)/4;
const int CASTLES=sizeof(CASTLE_TYPES)/sizeof(int)/4;
#endif // _DEFS__H
