#ifndef ENEMY_H_
#define ENEMY_H_

#include"fun.h"
#include"LTexture.h"

#define RANDOM_POSX_FLY 700
#define RANDOM_POSX_CACTUS 50
#define FLY_MAX_HEIGHT 235  
#define RANGE_FLY_Y 75 //pham vi bay y

class enemy
{
public:
	enemy();

	~enemy();

	void renderE1(LTexture enemy1Texture, SDL_Renderer* gRenderer);

	void renderE2(LTexture enemy2Texture, SDL_Renderer* gRenderer, SDL_Rect* currentClip);

	void renderE3(LTexture enemy3Texture, SDL_Renderer* gRenderer);

	void move(const int &speedPlus);

	void moveE3(const int &speedPlus);

	void resetEnemy1();

	void resetEnemy2();

	void resetEnemy3();

	int getPosX1() {return posX1;}

	int getPosY1() {return posY1;}

	int getPosX2() {return posX2;}

	int getPosY2() {return posY2;}

	int getPosX3() {return posX3;}

	int getPosY3() {return posY3;}


	
private:

	//catus
	int posX1, posY1;
	

	//fly
	int posX2, posY2;

	//ufo
	double posX3;
	int posY3;
	

};
#endif
