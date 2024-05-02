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

#define BALL_FILE "assets//image//water.png"
#define SHOOT_FILE "assets//image//shooting.png"
#define SPLASH_FILE "assets//image//hit.png"

#define CASTLES_FILE "assets//image//castles.png"
#define BIRD_FILE "assets//image//bird.png"
#define CRAB_FILE "assets//image//crab.png"
#define VANISH_FILE "assets//image//smoke.png"

#define BAR_FILE "assets//image//bars.png"
#define BUTTON_FILE "assets//image//button.png"
#define MENU_FILE "assets//image//menu.jpg"
#define INFO_FILE "assets//image//instruction.png"
#define CREDIT_FILE "assets//image//credit.png"

#define JUMP_SOUND "assets//sound//jump.wav"
#define COLLECT_SOUND "assets//sound//collect.wav"
#define ATTACK_SOUND "assets//sound//attack.wav"
#define SPLASH_SOUND "assets//sound//splash.wav"
#define SHOOT_SOUND "assets//sound//shoot.wav"
#define BIRD_SOUND "assets//sound//bird.wav"
#define GAME_MUSIC "assets//sound//gameMusic.mp3"
#define DEAD_SOUND "assets//sound//dead.wav"
#define YAY_SOUND "assets//sound//yay.wav"
#define MENU_MUSIC "assets//sound//menuMusic.mp3"
#define CLICK_SOUND "assets//sound//click.wav"
#define FONT "assets//font//Silver.ttf"

const int BASE_SPEED=0;
const int GROUND_SPEED=8;
const int LAYER_1_SPEED=0;
const int LAYER_2_SPEED=1;
const int LAYER_3_SPEED=2;
const int LAYER_4_SPEED=3;
const int TIME_UP=1000;
const int MAX_LEVEL=10;

const int BASE_ENERGY=585;
const int ENERGY_LOST=15;
const int ENERGY_GAIN=5;
const int MAX_POWER=4000;
const int POWER_GAIN=500;
const int POWER_LOST=5;
const int BULLET_SPEED=10;

const int BAR_X=10;
const int BAR_Y=5;
const int POW_POS_X=88;
const int POW_POS_Y=12;
const int POW_WIDTH[]={14,41,68,95,122,149,176,190};
const int ENERGY_POS_X[]={88,120,151,183,214};
const int ENERGY_POS_Y=105;
const int SCORE_MULTIPLIER=5;
const int HI_TEXT_POS_X=690;
const int HI_TEXT_POS_Y=10;
const int YS_TEXT_POS_X=690;
const int YS_TEXT_POS_Y=50;
const int S_TEXT_POS_X=850;
const int HS_TEXT_POS_X=850;
const int BIG_BUTTON=0;
const int MED_BUTTON=1;
const int SMALL_BUTTON=2;
const int BUTTON_H=59;
const int SMALL_BUTTON_W=59;
const int MED_BUTTON_W=123;
const int BIG_BUTTON_W=155;
const int PLAY_BUTTON_POS_X=747;
const int PLAY_BUTTON_POS_Y=180;
const int INFO_BUTTON_POS_X=747;
const int INFO_BUTTON_POS_Y=260;
const int QUIT_BUTTON_POS_X=747;
const int QUIT_BUTTON_POS_Y=420;
const int CREDIT_BUTTON_POS_X=733;
const int CREDIT_BUTTON_POS_Y=340;
const int BACK_BUTTON_POS_X=40;
const int BACK_BUTTON_POS_Y=20;

const int GROUND=415;
const int MAX_HEIGHT=175;
const int BASE=80;
const int JUMP_SPEED=8;
const int FALL_SPEED=8;
const int DEAD_SPEED=2;
const int MIN_HEIGHT=220;
const int CHAR_HEIGHT=76;
const int CHAR_WIDTH=65;

const int COLLECT_POS_RANGE=100;
const int BIRD_POS_RANGE=300;
const int CASTLE_POS_RANGE=100;
const int CRAB_POS_RANGE=200;
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
const int HEADBUTT_CLIPS[][4]={{2114,0,65,76},{2200,0,65,76},{2320,0,65,76},{2320,0,65,76},{2399,0,65,76},{2399,0,65,76},{2399,0,65,76},{   2494,0,65,76}};
const int GETGUN_CLIPS[][4]={{2590,0,70,76}};
const int RUN_W_GUN_CLIPS[][4]={{2690,0,65,76},{2786,0,65,76},{2882,0,65,76},{2978,0,65,76},{3074,0,65,76},{3170,0,65,76}};
const int JUMP_W_GUN_CLIPS[][4]={{3266,0,70,76},{3360,0,70,76},{3455,0,70,76},{3455,0,70,76},{3455,0,70,76},{3551,0,70,76}};
const int FALL_W_GUN_CLIPS[][4]={{3647,0,70,76},{3647,0,70,76},{3743,0,70,76},{3743,0,70,76},{3838,0,70,76},{3935,0,70,76}};
const int CTRASH_PIXELS=10;

const int SHOOT_CLIPS[][4]={{129,131,53,21},{191,131,53,21},{255,131,53,21},{0,231,53,21},{63,231,53,21},{128,227,53,21},{191,231,53,21}};
const int SPLASH_CLIPS[][4]={{139,15,41,65},{11,111,41,65},{139,111,41,65},{67,223,41,65},{184,223,41,65}};
const int BALL_CLIPS[][4]={{15,35,32,32},{79,35,32,32},{148,35,32,32},{15,131,32,32},{79,131,32,32},{148,131,32,32}};
const int BIRD_CLIPS[][4]={{197,0,61,49},{130,0,62,49},{67,0,60,49},{3,0,62,49}};
const int CASTLE_TYPES[][4]={{1,75,70,75},{74,43,120,107},{198,0,70,150},{273,43,169,107},{447,0,120,150}};
const int CRAB_CLIPS[][4]={{13,109,42,19},{137,109,42,19},{203,109,42,19}};
const int VANISH_CLIPS[][4]={{21,152,85,80},{143,152,85,80},{275,152,85,80},{21,280,85,80},{143,280,85,80}};
const int OBS_TRASH_PIXELS=5;

const int RUN_FRAMES=sizeof(RUN_CLIPS)/sizeof(int)/4;
const int JUMP_FRAMES=sizeof(JUMP_CLIPS)/sizeof(int)/4;
const int FALL_FRAMES=sizeof(FALL_CLIPS)/sizeof(int)/4;
const int DEAD_FRAMES=sizeof(DEAD_CLIPS)/sizeof(int)/4;
const int HEADBUTT_FRAMES=sizeof(HEADBUTT_CLIPS)/sizeof(int)/4;
const int GETGUN_FRAMES=sizeof(GETGUN_CLIPS)/sizeof(int)/4;

const int SPLASH_FRAMES=sizeof(SPLASH_CLIPS)/sizeof(int)/4;
const int SHOOT_FRAMES=sizeof(SHOOT_CLIPS)/sizeof(int)/4;
const int BALL_FRAMES=sizeof(BALL_CLIPS)/sizeof(int)/4;
const int BIRD_FRAMES=sizeof(BIRD_CLIPS)/sizeof(int)/4;
const int CRAB_FRAMES=sizeof(CRAB_CLIPS)/sizeof(int)/4;
const int CASTLES=sizeof(CASTLE_TYPES)/sizeof(int)/4;
const int VANISH_FRAMES=sizeof(VANISH_CLIPS)/sizeof(int)/4;
#endif // _DEFS__H
