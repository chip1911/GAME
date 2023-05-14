#ifndef FUN_H_
#define FUN_H_

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<sstream>
#include<fstream>
#include<iostream>
#include<string>
#include<ctime>



//screen dimension
const int SCREEN_WIDTH = 756 ;
const int SCREEN_HEIGHT = 425 ;

static const int charGround = 321;
const int RUN_FRAMES = 6;
const int FLY_FRAMES = 2;
const int JUMP_MAX_HEIGHT = 155;

const int buttonPosX1 = 561;
const int buttonPosY1 = 154;

const int buttonPosX2 = 561;
const int buttonPosY2 = 236;

#define ENEMY_SPEED 5
#define GROUND_SPEED 5
#define BACKGROUND_SPEED 1
#define GROUND_POSY 368

//cactus
#define ENEMY_1_WIDTH 45
#define ENEMY_1_HEIGHT 57

//fly
#define ENEMY_2_WIDTH 30
#define ENEMY_2_HEIGHT 25

#define TIME_LIMIT 900
#define SPEED_INCREASEMENT 1
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1

#define BUTTON_WIDTH 164
#define BUTTON_HEIGHT 58


#endif